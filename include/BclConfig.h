#ifndef _BCL_CONFIG_H
#define _BCL_CONFIG_H

/*
 * The lazy way to have a build config without Kconfig or anything fancier.
  *Feel free to adjust the values.
 * 
 * If you do increase the number of subsystems, or services, you may 
 * need to increase the size of the bitset that keep track of what resources
 * are in use. Most are currently set to uint8_t!
 */


#define MAX_SUBSYSTEMS                  8
#define MAX_SERVICES_PER_SUBSYSTEM      4
#define MAX_SERVICE_NAME_LENGTH         10
#define DEFAULT_SLEEP_INTERVAL          100