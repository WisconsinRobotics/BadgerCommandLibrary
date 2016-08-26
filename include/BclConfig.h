#ifndef _BCL_CONFIG_H
#define _BCL_CONFIG_H

/*
 * The lazy way to have a build config without Kconfig or anything fancier.
  *Feel free to adjust the values.
 * 
 * If you do increase the number of subsystems, services, or ports, you may 
 * need to increase the size of the bitset that keep track of what resources
 * are in use. Most are currently set to uint8_t!
 */


#define MAX_SUBSYSTEMS                  8
#define MAX_SERVICES_PER_SUBSYSTEM      4
#define SERVICE_MAX_NAME_LENGTH         10
#define DEFAULT_SLEEP_INTERVAL          100

// maximum number of serial ports that BCL can use
#if defined(_WIN32) || defined(__linux__)
#define MAX_SERIAL 4
#else
#define MAX_SERIAL 1
#endif

// maximum number of UDP ports that BCL can use
#if defined(_WIN32) || defined(__linux__)
#define MAX_PORTS 16
#else
#define MAX_PORTS 0
#endif