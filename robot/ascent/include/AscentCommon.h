#ifndef _ASCENT_COMMON_H
#define _ASCENT_COMMON_H

/* Opcode definitions */

/* Debug packets (0x00 - 0x1F) */
#define BYTE_DISPLAY_OPCODE             0x11


/* Mechanical packets (0x20 - 0x4F) */
#define QUERY_ARM_POS                   0x20
#define REPORT_ARM_POS                  0x21
#define SET_ARM_POS                     0x22

#define QUERY_TURRET_POS                0x23
#define REPORT_TURRET_POS               0x24
#define SET_TURRET_POS                  0x25
#define FREEZE_TURRET                   0x26

#define SET_TANK_DRIVE_SPEED            0x2E
#define SET_ALL_WHEEL_SPEED             0x2F

#define START_CAR_HORN                  0x30

#define SET_SOIL_DOOR_SPEED             0x31


/* Sensor packets (0x50 - 0x6F) */
#define QUERY_GPS                       0x50
#define REPORT_GPS                      0x51
#define SET_GPS                         0x52

#define QUERY_SOIL                      0x53
#define REPORT_SOIL                     0x54

#define QUERY_IMU                       0x55
#define REPORT_IMU                      0x56
#define CALIBRATE_IMU                   0x57


#define QUERY_MICROSCOPE                0x6F

/* AI packets (0x70 - 0x7F) */
#define AI_SIMPLE_REPORT                0x70
#define AI_DEBUG_REPORT                 0x71


/* Other Ascent definitions */
#define FRONT_LEFT_WHEEL                0
#define MIDDLE_LEFT_WHEEL               1
#define BACK_LEFT_WHEEL                 2
#define FRONT_RIGHT_WHEEL               3
#define MIDDLE_RIGHT_WHEEL              4
#define BACK_RIGHT_WHEEL                5

#define TURNTABLE_INDEX                 0
#define HUMERUS_INDEX                   1
#define FOREARM_INDEX                   2
#define WRIST_UP_DOWN_INDEX             3
#define WRIST_ROT_INDEX                 4
#define CLAW_INDEX                      5

#endif
