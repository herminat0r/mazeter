/*
 * FILNAMN:       spi_commands.h
 * PROJEKT:       Mazeter
 * PROGRAMMERARE: Martin Andersson
 *                Mattias Fransson
 * DATUM:         2013-05-16
 *
 * BESKRIVNING:   Inneh�ller alla kommandokoder som skickas �ver SPI och bluetooth.
 *
 */

#ifndef SPI_COMMANDS_H
#define SPI_COMMANDS_H

#define SENSOR_DISTANCE1 0x01
#define SENSOR_DISTANCE2 0x02
#define SENSOR_DISTANCE3 0x03
#define SENSOR_DISTANCE4 0x04
#define SENSOR_DISTANCE5 0x05
#define SENSOR_DISTANCE6 0x06
#define SENSOR_DISTANCE7 0x07
#define SENSOR_LINE_DEVIATION 0x08
#define SENSOR_ANGLE 0x09
#define SENSOR_LINE_TYPE 0x0A
#define SENSOR_DATA_ALL 0x0F

#define CONTROL_SIGNALS 0x20
#define STEER_STRAIGHT 0x21
#define STEER_STRAIGHT_LEFT 0x22
#define STEER_STRAIGHT_RIGHT 0x23
#define STEER_BACK 0x24
#define STEER_STOP 0x25
#define STEER_ROTATE_LEFT 0x26
#define STEER_ROTATE_RIGHT 0x27
#define CALIBRATE_LINE_SENSOR 0x28
#define CLAW_OPEN 0x29
#define CLAW_CLOSE 0x2A
#define CONTROL_THROTTLE 0x2B

#define SEND_STRING 0x30
#define BT_CONNECT 0x31
#define BT_DISCONNECT 0x32

#define FLAG_AUTO 0x41
#define FLAG_MANUAL 0x42

// Bara v�rden, inte kommandon.
// L�gg dessa i sin egna header?
#define LINE_TURN_LEFT 0x51
#define LINE_TURN_RIGHT 0x52
#define LINE_STRAIGHT 0x53
#define LINE_GOAL 0x54
#define LINE_GOAL_STOP 0x55
#define LINE_START_STOP 0x56
#define LINE_NONE 0x57

#define CONTROL_PARAMETERS_ALL 0x60
#define PARA_DIST_KP 0x61
#define PARA_DIST_KD 0x62
#define PARA_LINE_KP 0x63
#define PARA_LINE_KD 0x64

#define CHECK_STACK 0x70
#define TURN_STACK_TOP 0x71
#define ALGO_STATE 0x72
#define RUN_START 0x73
#define TURN_DONE 0x74
#define RESET_GYRO 0x75

#define ABORT 0x99

#define ERROR_SPI 0xE0
#define ERROR_UNKNOWN_SPI_COMMAND 0xE1
#define ERROR_FATAL 0xEE

#endif /* SPI_COMMANDS */
