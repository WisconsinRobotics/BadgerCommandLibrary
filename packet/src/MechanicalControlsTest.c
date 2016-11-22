#include "MechanicalControlPackets.h"
#include <stdio.h>
#include "packet.h"

int main (int argC, char* argV[]) {
	BclPacket a, b, c, d, e; //do these need to be initialized?
	uint8_t wheelSpeeds[2] = {4, 5};
	
	InitializeWheelSpeedControlPacket (&a, 2, wheelSpeeds);
	InitializeArmPositionControlPacket (&b, 2, wheelSpeeds);
	IntializeArmPositionQueryPacket (&c);
	InitializeArmPositionReportPacket (&d, 2, wheelSpeeds);
	InitializeTurretControlPacket (&e, 10, 30);
	
	//printf (a + \n + b + \n + c + \n + d + \n + e); 
	//how to print? with primitives theres a %d or whatever
	//but what about printing something you defined?
	
	printf (a);
	}
