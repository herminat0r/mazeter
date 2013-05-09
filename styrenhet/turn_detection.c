﻿/*
 * FILNAMN:       turn_detection.c
 * PROJEKT:       Mazeter
 * PROGRAMMERARE: Martin Andersson
 *				  Joel Davidsson
 *				  Fredrik Stenmark
 * DATUM:         2013-04-25
 *
 * BESKRIVNING: 
 *
 */

#include "sensor_data.h"
#include "turn_detection.h"
#include "turn_stack.h"
#include "styrenhet.h"
#include "pd_control.h"
#include "PWM.h"

uint8_t min(uint8_t x, uint8_t y)
{
	if (x < y)
	{
		return x;
	}
	else
	{
		return y;
	}
}

/* Upptäcker svängar på väg in i labyrinten */
void detectTurn(volatile TurnStack* turn_stack)
{	
	if (current_sensor_data.distance3 > THRESHOLD_CONTACT_SIDE)
	{
		// Vänster ej kontakt
		if ((current_sensor_data.distance1 + current_sensor_data.distance2) / 2 < THRESHOLD_STOP)
		{
			// Fall 1, 3 eller 7
			if (current_sensor_data.distance4 > current_sensor_data.distance3 + THRESHOLD_CONTACT_SIDE / 2)
			{
				// Fall 7
				pushTurnStack(turn_stack, newTurnNode(LEFT_TURN));
				makeTurn(RIGHT_TURN);
			}
			else if (current_sensor_data.distance3 > current_sensor_data.distance4 + THRESHOLD_CONTACT_SIDE / 2)
			{
				// Fall 1 eller 3
				pushTurnStack(turn_stack, newTurnNode(RIGHT_TURN));
				makeTurn(LEFT_TURN);
			}
		}	
		else if (((previous_sensor_data.distance1 + previous_sensor_data.distance2) / 2 >= THRESHOLD_STOP_DEAD_END) &&
				 ((current_sensor_data.distance1 + current_sensor_data.distance2) / 2 < THRESHOLD_STOP_DEAD_END))
		{
			// Fall 2
			pushTurnStack(turn_stack, newTurnNode(RIGHT_TURN));
			makeTurn(LEFT_TURN);
		}
		//else if (previous_sensor_data.distance3 > current_sensor_data.distance3 + 40)
		else
		{
			// Fall 4
			pushTurnStack(turn_stack, newTurnNode(STRAIGHT)); // Pusha att åka rakt fram
			//makeTurn(STRAIGHT);
			//driveStraight(30);
		}
	} 
	else if (current_sensor_data.distance4 > THRESHOLD_CONTACT_SIDE)
	{
		// Höger ej kontakt men vänster har
		if ((current_sensor_data.distance1 + current_sensor_data.distance2) / 2 < THRESHOLD_STOP)
		{
			// Fall 5
			pushTurnStack(turn_stack, newTurnNode(LEFT_TURN));
			makeTurn(RIGHT_TURN);
		}
		else if  (((previous_sensor_data.distance1 + previous_sensor_data.distance2) / 2 >= THRESHOLD_STOP_DEAD_END) &&
				  ((current_sensor_data.distance1 + current_sensor_data.distance2) / 2 < THRESHOLD_STOP_DEAD_END))
		{
			// Fall 6
			pushTurnStack(turn_stack, newTurnNode(LEFT_TURN));
			makeTurn(RIGHT_TURN);
		}
		//else if (previous_sensor_data.distance4 > current_sensor_data.distance4 + THRESHOLD_CONTACT_SIDE - 10)
		else
		{
			// Fall 8
			pushTurnStack(turn_stack, newTurnNode(STRAIGHT)); // Pusha att åka rakt fram
			//makeTurn(STRAIGHT);
			//driveStraight(30);
		}
	}
}

/* Upptäcker svängar (även rakt fram) på väg ut ur labyrinten */
void detectTurnOut(volatile TurnStack* turn_stack)
{
	if (current_sensor_data.distance3 > THRESHOLD_CONTACT_SIDE || current_sensor_data.distance4 > THRESHOLD_CONTACT_SIDE)
	{
		// Kör fram till mitten av svängen.
		driveStraight(DISTANCE_DETECT_TURN);
		makeTurn(popTurnStack(turn_stack));
	}
}