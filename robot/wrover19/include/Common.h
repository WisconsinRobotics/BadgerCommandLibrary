#if ROBOT == WRover19
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

#define SET_MAST_POS                    0x27

#define QUERY_ARM_SPEED                 0x28
#define REPORT_ARM_SPEED                0x29
#define SET_ARM_SPEED                   0x2A

#define ACTIVATE_SOLENOID               0x2B

#define QUERY_PID                       0x2C
#define REPORT_PID                      0x2D
#define SET_PID                         0x2E

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

/* Misc definitions */
#define FRONT_LEFT_WHEEL                0
#define MIDDLE_LEFT_WHEEL               1
#define BACK_LEFT_WHEEL                 2
#define FRONT_RIGHT_WHEEL               3
#define MIDDLE_RIGHT_WHEEL              4
#define BACK_RIGHT_WHEEL                5

#define NUMBER_OF_WHEELS                6

#define TURNTABLE_INDEX                 0
#define SHOULDER_INDEX                  2
#define ELBOW_INDEX                     4
#define FOREARM_INDEX                   6
#define WRIST_LEFT_INDEX                8
#define WRIST_RIGHT_INDEX               10
#define CLAW_INDEX                      12

#define FRONT_LEFT_ACTUATOR             0
#define BACK_LEFT_ACTUATOR              1
#define FRONT_RIGHT_ACTUATOR            2
#define BACK_RIGHT_ACTUATOR             3

#endif
#endif
