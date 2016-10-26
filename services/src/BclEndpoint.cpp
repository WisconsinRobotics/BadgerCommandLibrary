#include "BclEndpoint.h"

using namespace BCL;

// Constructor
//
// Depending on whether this is a Serial or UDP endpoint, create either a BCL::UdpSocket or a
// BCL::SerialPort class instance. 
//
// When used as a Serial endpoint, addr is const char * specifying the COM port
// When used as a UDP endpoint, addr is the struct sockaddr_in * specifying the local address
BclEndpoint::BclEndpoint(int robot_id, bool serial, void *addr) {
	
}

// Destructor
//
// Should delete the BCL::UdpSocket or BCL::SerialPort object created in the constructor
BclEndpoint::~BclEndpoint() {
	
}

// Call BCL::UdpSocket.Write() or BCL::SerialPort.Write()
int Write(void *buff) {
	
}

// Call BCL::UdpSocket.Read() or BCL::SerialPort.Read()
int Write(void *buff) {
	
}