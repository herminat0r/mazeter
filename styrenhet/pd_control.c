﻿/*
 * FILNAMN:       styrenhet.c
 * PROJEKT:       Mazeter
 * PROGRAMMERARE: Mattias Fransson
 *				  Herman Ekwall
 * DATUM:         2013-04-18
 *
 */

#include "pd_control.h"
#include "control_parameters.h"
#include "styrenhet.h"
#include "spi_commands.h"
#include "turn_detection.h"
#include <util/atomic.h>
#include <stdint.h>

typedef struct  
{
	int8_t left_value;
	int8_t right_value;
} RegulatorSignals;

void startTimer()
{
	TCCR1B = (1 << CS10) | (0 << CS11) | (1 << CS12); // Prescaler 1024, ändra i pd_control.c i handleTape om prescalern ändras
}

void resetTimer()
{
	TCCR1B = 0x00;
	TCNT1 = 0x0000;
	TIFR1 |= (1 << TOV1);
}

RegulatorSignals regulatorSignalDeltaLeft(const int16_t* delta_left, const int16_t* delta_left_previous)
{
	RegulatorSignals ret;
	ret.left_value = control_parameters.left_kp * *delta_left + control_parameters.left_kd * (*delta_left - *delta_left_previous);
	ret.right_value = -(control_parameters.right_kp * *delta_left + control_parameters.right_kd * (*delta_left - *delta_left_previous));
	return ret;
}

RegulatorSignals regulatorSignalDeltaRight(const int16_t* delta_right, const int16_t* delta_right_previous)
{
	RegulatorSignals ret;
	ret.left_value = -(control_parameters.left_kp * *delta_right + control_parameters.left_kd * (*delta_right - *delta_right_previous));
	ret.right_value = control_parameters.right_kp * *delta_right + control_parameters.right_kd * (*delta_right - *delta_right_previous);
	return ret;
}

RegulatorSignals regulatorSignalDeltaFront(const int16_t* delta_front, const int16_t* delta_front_previous)
{
	RegulatorSignals ret;
	ret.left_value = -(control_parameters.left_kp * *delta_front + control_parameters.left_kd * (*delta_front - *delta_front_previous));
	ret.right_value = control_parameters.right_kp * *delta_front + control_parameters.right_kd * (*delta_front - *delta_front_previous);
	return ret;
}

RegulatorSignals regulatorSignalDeltaBack(const int16_t* delta_back, const int16_t* delta_back_previous)
{
	RegulatorSignals ret;
	ret.left_value = control_parameters.left_kp * *delta_back + control_parameters.left_kd * (*delta_back - *delta_back_previous);
	ret.right_value = -(control_parameters.right_kp * *delta_back + control_parameters.right_kd * (*delta_back - *delta_back_previous));
	return ret;
}

void sensorDataToControlSignal(const SensorData* current, const SensorData* previous)
{
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		RegulatorSignals regulator_signals;
		
		// switch
		
		int16_t delta_front = current->distance3 - current->distance4;
		int16_t delta_front_previous = previous->distance3 - previous->distance4;
		
		regulator_signals = regulatorSignalDeltaFront(&delta_front, &delta_front_previous);
		
		if (regulator_signals.left_value > control_signals.left_value)
		{
			control_signals.left_value = 0;
		}
		else
		{
			control_signals.left_value += regulator_signals.left_value;
			if (control_signals.left_value > 100)
			{
				control_signals.left_value = 100;
			}
		}
		
		if (regulator_signals.right_value > control_signals.right_value)
		{
			control_signals.left_value = 0;
		}
		else
		{
			control_signals.right_value += regulator_signals.right_value;
			if (control_signals.right_value > 100)
			{
				control_signals.right_value = 100;
			}
		}
	}
}

void makeTurn(uint8_t turn)
{
	uint16_t angle1 = current_sensor_data.angle;
	uint16_t angle2 = current_sensor_data.angle;
	
	switch(turn)
	{
		case LEFT_TURN:
			angle1 += 9000;
			if (angle1 >= 36000)
			angle1 -= 36000;
		
			commandToControlSignal(STEER_ROTATE_LEFT);
			while (current_sensor_data.angle < angle1 || current_sensor_data.angle >= angle2)
			{}
			commandToControlSignal(STEER_STOP); // för test ska vara: commandToControlSignal(STEER_STRAIGHT);
			break;
		
		case RIGHT_TURN:
			angle1 -= 9000;
			if (angle1 >= 36000)
			angle1 = 36000 - (9000 - angle2);
			
			commandToControlSignal(STEER_ROTATE_RIGHT);
			while (current_sensor_data.angle > angle1 || current_sensor_data.angle <= angle2)
			{}
			commandToControlSignal(STEER_STOP); // för test ska vara: commandToControlSignal(STEER_STRAIGHT);
			break;
		
		case STRAIGHT:
			commandToControlSignal(STEER_STRAIGHT);
			break;
		
		default:
			break;
	}
	
	// Ser till att vi inte lämnar svängen för PD-reglering förrän vi har något vettigt att PD-reglera på.
	while (current_sensor_data.distance3 > THRESHOLD_CONTACT && current_sensor_data.distance4 > THRESHOLD_CONTACT)
	{}
}

void handleTape(volatile TurnStack* turn_stack, uint8_t turn)
{
	uint16_t timer_count = 800000000/(1024*(control_signals.left_value + control_signals.right_value)); // Prescaler 1024
		
	switch(turn)
	{
		case LINE_GOAL:
			// algo mål
			break;
			
		case LINE_TURN_LEFT:
			startTimer();
		
			while(TCNT1 < timer_count)
			{}
			pushTurnStack(turn_stack, newTurnNode(RIGHT_TURN));
			makeTurn(LEFT_TURN);
			break;
			
		case LINE_TURN_RIGHT:
			startTimer();
		
			while(TCNT1 < timer_count)
			{}	
			pushTurnStack(turn_stack, newTurnNode(LEFT_TURN));
			makeTurn(RIGHT_TURN);
			break;
			
		case LINE_STRAIGHT:
			startTimer();
		
			while(TCNT1 < 2*timer_count)
			{}
			pushTurnStack(turn_stack, newTurnNode(STRAIGHT));
			makeTurn(STRAIGHT);
			break;
			
		default:
			break;
	}
	resetTimer();
}