﻿/*
 * FILNAMN:       look_up.h
 * PROJEKT:       Mazeter
 * PROGRAMMERARE: Mattias Fransson
 *				  Herman Ekwall
 * DATUM:         2013-04-18
 *
 */

#include "look_up.h"
#include "sensor_names.h"
#include <avr/pgmspace.h> 

const uint8_t distance1_table[256] PROGMEM =
{0};
const uint8_t distance2_table[256] PROGMEM =
{0};
const uint8_t distance3_table[256] PROGMEM =
{0};
const uint8_t distance4_table[256] PROGMEM =
{0};
const uint8_t distance5_table[256] PROGMEM =
{0};
const uint8_t distance6_table[256] PROGMEM =
{0};
const uint8_t distance7_table[256] PROGMEM =
{0};	
	
uint8_t lookUpDistance(uint8_t raw_value, uint8_t sensor)
{
	switch(sensor)
	{
		case DISTANCE_1:
			return distance1_table[raw_value];
			break;
		
		case DISTANCE_2:
			return distance2_table[raw_value];
			break;
		
		case DISTANCE_3:
			return distance3_table[raw_value];
			break;
		
		case DISTANCE_4:
			return distance4_table[raw_value];
			break;
		
		case DISTANCE_5:
			return distance5_table[raw_value];
			break;
			
		case DISTANCE_6:
			return distance6_table[raw_value];
			break;
					
		case DISTANCE_7:
			return distance7_table[raw_value];
			break;
			
		default:
			break;
	}
	
	return 0;
}
