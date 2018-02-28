#if ROBOT == Amelio
#ifndef _COMMON_H
#define _COMMON_H

/* Opcode definitions */

/* Debug packets (0x00 - 0x1F) */
#define BYTE_DISPLAY_OPCODE             0x11


/* Mechanical packets (0x20 - 0x4F) */
#define SET_TANK_DRIVE_SPEED            0x20
#define SET_ALL_WHEEL_SPEED             0x21

#define QUERY_ARM_POS                   0x22
#define REPORT_ARM_POS                  0x23
#define SET_ARM_POS                     0x24

#define SET_RIDE_HEIGHT_SPEED           0x25
#define SET_ALL_RIDE_HEIGHT_SPEED       0x26

/* Sensor packets (0x50 - 0x6F) */
#define QUERY_GPS                       0x50
#define REPORT_GPS                      0x51
#define SET_GPS                         0x52

#define QUERY_SOIL                      0x53
#define REPORT_SOIL                     0x54

#define QUERY_IMU                       0x55
#define REPORT_IMU                      0x56
#define CALIBRATE_IMU                   0x57

#define QUERY_BAT                       0x60
#define REPORT_BAT                      0x61

#define QUERY_MICROSCOPE                0x6F

/* AI packets (0x70 - 0x7F) */
#define AI_SIMPLE_REPORT                0x70
#define AI_DEBUG_REPORT                 0x71


/* Misc definitions */
#define FRONT_LEFT_WHEEL                0
#define MIDDLE_LEFT_WHEEL               1
#define BACK_LEFT_WHEEL                 2
#define FRONT_RIGHT_WHEEL               3
#define MIDDLE_RIGHT_WHEEL              4
#define BACK_RIGHT_WHEEL                5

#define NUMBER_OF_WHEELS                6

#define TURNTABLE_INDEX                 0
#define HUMERUS_INDEX                   1
#define FOREARM_INDEX                   2
#define WRIST_UP_DOWN_INDEX             3
#define WRIST_ROT_INDEX                 4
#define CLAW_INDEX                      5

#define FRONT_LEFT_ACTUATOR             0
#define BACK_LEFT_ACTUATOR              1
#define FRONT_RIGHT_ACTUATOR            2
#define BACK_RIGHT_ACTUATOR             3

#endif
#endif
