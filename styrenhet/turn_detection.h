﻿/*
 * FILNAMN:       turn_detection.h
 * PROJEKT:       Mazeter
 * PROGRAMMERARE: Martin Andersson
 *				  Joel Davidsson
 * DATUM:         2013-04-25
 *
 * BESKRIVNING: 
 *
 */


#ifndef TURN_DETECTION_H_
#define TURN_DETECTION_H_

#include "sensor_data.h"
#include "turn_stack.h"

#define LEFT_TURN 1
#define RIGHT_TURN 2
#define STRAIGHT 3

/* Avståndsvärde då man inte längre har kontakt med väggen,
	dvs sväng eller återvändsgränd upptäckt */
#define THRESHOLD_CONTACT_SIDE 80

/* Avståndsvärde när man ska rotera */
#define THRESHOLD_STOP 60

/* Avstånd då vi är på väg att köra in i ngt */
#define THRESHOLD_ABORT 25

/* Avståndsvärde när man ska rotera  om det är en återvändsgränd man mäter mot*/
#define THRESHOLD_STOP_DEAD_END 130

/* Avståndsvärde när vi inte kan detektera sväng */
#define THRESHOLD_NO_CONTACT 160

uint8_t min(uint8_t x, uint8_t y);
uint8_t max(uint8_t x, uint8_t y);

/* Upptäcker svängar på väg in i labyrinten */
void detectTurn(volatile TurnStack* turn_stack);

/* Upptäcker svängar på väg ut ur labyrinten */
void detectTurnOut(volatile TurnStack* turn_stack);




#endif /* TURN_DETECTION_H_ */