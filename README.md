# BadgerCommandLibrary
This is intended to be WisconsinRobotics' main communication protocol for its robots. The codebase is split into two parts: the packet parsing library and a services framework. The packet parsing library is intended to be able to compile and link into embedded toolchains, but the framework is only for Windows and Linux.

## Packet Library
The nitty gritty details of the packet structure can be found in doc/BCL-Spec.docx. This section assumes you have read through the document, and will focus on the code structure and types needed to serialize, deserialize, and extend the packets.

### Using BclPacket
Let's start off with a simple example.
```
BclPacket pkt;
BCL_STATUS status;
uint8_t buffer[16];
uint8_t bytes_written;

InitializeActivateServicePacket(&pkt);
status = SerializeBclPacket(&pkt, buffer, 16, &bytes_written);
if (status != BCL_OK)
{
    printf("Failed to serialize!\n");
    exit(1);
}

BclPacket parsed_pkt;
status = DeserializeBclPacket(&pkt, buffer, bytes_written);
if (status != BCL_OK)
{
    printf("Failed to deserialize!\n");
    exit(1);
}
```

Right off the bat - the `BclPacket` is the base type. In order to get the packet type that you desire, you must call the appropriate Initialize\*Packet function. If you want to serialize or deserialize, just call the SerializeBclPacket or DeserializeBclPacket, respectively. The `BCL_STATUS` enum is in the same spirit as the errno values in Linux - just descriptive return values.

### Extending BclPacket
The packets that come with BCL is fairly barebones, and only provide for service activation/deactivation and discovery. For each new robot, it will be necessary to create new message types. To do this, you must do the following:

* Create a Initialize\*Packet function that takes in a BclPacket\* and, if you have a payload, a pointer to the payload struct. After that, you will need to call the InitializeBclPacket function the properly initialize the BclPacket struct.
* Create a Serialize\*Payload function to write the payload struct into the byte buffer.
* Create a Deserialize\*Payload function to parse the byte buffer into the payload struct.

For examples, look at ControlServicePackets.h in packets/include.

## Services Framework
The services framework is intended to allow for runtime selection of code snippets. 

### Concepts and Terminology
* A *Service* represents a piece of code that can be turned on and off at runtime. If it is active, it can be configured to run at periodic intervals or when a packet is routed to it.
* A *Service Master* mediates all of the services running. It is responsible for any incoming and outgoing I/O, as well as activating/deactivating services.

### Creating new services
*To be added at some point...*

### Bringup process
*To be added at some point...*

## Building
### Windows and Linux
Go to the build/ folder and navigate to the appropriate platform folder. For Windows, build within Visual Studio, which will build both the native and C# libraries. Run `make` on Linux to build the static binary.

### Launchpad
1. Open Code Composer Studio, and import the project using BadgerCommandLibrary/build/launchpad as the root directory.
2. Build the project (Click the hammer icon in the toolbar).
