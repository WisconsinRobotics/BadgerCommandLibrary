#if ROBOT == Atlas
#ifndef _ATLAS_COMMON_H
#define _ATLAS_COMMON_H

/* Opcode definitions */

/* Debug packets (0x00 - 0x1F) */

/* Mechanical packets (0x20 - 0x4F) */
#define SET_TANK_DRIVE_SPEED		0x20
#define SET_ALL_WHEEL_SPEED			0x21

/* Other Atlas definitions */
#define FRONT_LEFT_WHEEL                0
#define BACK_LEFT_WHEEL                 1
#define FRONT_RIGHT_WHEEL               2
#define BACK_RIGHT_WHEEL                3

#define NUMBER_OF_WHEELS				4

#endif
#endif