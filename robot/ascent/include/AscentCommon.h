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

#define SET_TANK_DRIVE_SPEED            0x2E
#define SET_ALL_WHEEL_SPEED             0x2F


/* Sensor packets (0x50 onwards)*/
#define QUERY_GPS                       0x50
#define REPORT_GPS                      0x51

#define QUERY_SOIL                      0x52
#define REPORT_SOIL                     0x53

#define QUERY_IMU                       0x54
#define REPORT_IMU                      0x55


/* Other Ascent definitions */
#define NUMBER_WHEELS                   6
#define NUMBER_ARM_MOTOR_POSITONS       5

#endif
