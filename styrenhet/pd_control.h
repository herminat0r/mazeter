﻿/*
 * FILNAMN:       pd_control.h
 * PROJEKT:       Mazeter
 * PROGRAMMERARE: Mattias Fransson
 *				  Herman Ekwall
 * DATUM:         2013-05-02
 *
 */

#ifndef PD_CONTROL_H_
#define PD_CONTROL_H_

#define DEGREES_90 8700

#include "pd_control.h"
#include "control_parameters.h"
#include "styrenhet.h"
#include "spi_commands.h"
#include "turn_detection.h"

void sensorDataToControlSignal(const SensorData* current, const SensorData* previous);
void makeTurn(uint8_t turn);
void handleTape(volatile TurnStack* turn_stack, uint8_t turn);
void lineRegulator(int8_t current_deviation, int8_t previous_deviation);

#endif /* PD_CONTROL_H_ */