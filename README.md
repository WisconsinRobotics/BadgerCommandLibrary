# BadgerCommandLibrary
This is intended to be WisconsinRobotics' main communication protocol for its robots. The codebase is split into two 
parts: the packet parsing library and a services framework. The packet parsing library is intended to be able to
compile and link into embedded toolchains, but the framework is only for Windows and Linux.

## Packet Library
The nitty gritty details of the packet structure can be found in doc/BCL-Spec.docx. This section assumes you have read
through the document, and will focus on the code structure and types needed to serialize, deserialize, and extend the 
packets.

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

Right off the bat - the `BclPacket` is the base type. In order to get the packet type that you desire, you must call 
the appropriate Initialize\*Packet function. If you want to serialize or deserialize, just call the 
SerializeBclPacket or DeserializeBclPacket, respectively. The `BCL_STATUS` enum is in the same spirit as the errno 
values in Linux - just descriptive return values.

If there is a payload associated with the packet, it's also quite easy to use.
Assume we have defined a tank drive packet that has a payload of two signed bytes, left and right speed.
```
BclPacket tank_drive_pkt;
TankDrivePayload tank_drive_payload;
BCL_STATUS status;

InitializeTankDrivePacket(&tank_drive_pkt, &tank_drive_payload);

tank_drive_payload.left = 100;
tank_drive_payload.right = -100;

tank_drive_pkt.Header.Destination = { 1, 2 };
```

Here, we associate a TankDrivePayload struct with the BclPacket via the InitializeTankDrivePacket() function call. Note
that BclPacket does NOT copy the contents; it merely stores a pointer to the payload struct. After the initialization,
we can adjust the payload however we want. We also set the destination address of the packet, which is robot ID 1 and
service ID 2.

### Extending BclPacket
The packets that come with BCL is fairly barebones, and only provide for service activation/deactivation and discovery.
For each new robot, it will be necessary to create new message types. To do this, you must do the following:

* Create a Initialize\*Packet function that takes in a BclPacket\* and, if you have a payload, a pointer to the payload struct.
    After that, you will need to call the InitializeBclPacket function the properly initialize the BclPacket struct.
* Create a Serialize\*Payload function to write the payload struct into the byte buffer.
* Create a Deserialize\*Payload function to parse the byte buffer into the payload struct.

For examples, look at ControlServicePackets.h in packets/include.

## Services Framework
The services framework is intended to allow for runtime selection of code snippets. 

### Concepts and Terminology
* A *Service* represents a piece of code that can be turned on and off at runtime. 
* Active services can be run periodically or whenever it receives a packet.
* A *Service Master* mediates all of the services running, all incoming/outgoing I/O,and activating/deactivating services.
* A *BclAddress* is defined by (robot ID, service ID), and must be unique, otherwise packets cannot be routed correctly. 

### Creating new services
Creating a new service is straightforward - you only need to subclass the Service class. There are two virtual functions 
that you may need to override: `bool HandlePacket(uint8_t *buffer, int length)` and `void Execute()`. `HandlePacket` is
responsible for parsing a BclPacket intended for that service. Return true if successfully handled, false if service 
wasn't supposed to or can't handle the given packet. `Execute` is called either periodically or after `HandlePacket`,
depending on if the service was configured to run periodically or not.

In any case, it is probably easier to see a code example.

```
#include <iostream>
#include <Service.hpp>

class SimpleService : public BCL::Service
{
public:
    SimpleService(int id) : BCL::Service(id, 100, false) { }

    bool HandlePacket(uint8_t *buffer, int length)
    {
        BclPacket pkt;
        BCL_STATUS status;

        InitializeTestPacket(&pkt);
        status = DeserializeBclPacket(&pkt, buffer, length);
        if (status != BCL_OK)
        {
            std::cout << "Failed to parse packet!" << std::endl;
            return false;
        }

        std::cout << "Received Test Packet!" << std::endl;
        return true;
    }

protected:
    void Execute()
    {
        std::cout << "Hello, world!" << std::endl;
    }
};
```

In this case, assume there's a packet defined called TestPacket. We subclassed Service, and called its constructor with
the id parameter, an interval of 100ms, and to set the SimpleService as default inactive. So this service would print
out "Hello, World!" every 100ms. When the robot receives a BclPacket intended for the SimpleService, then it'll run the 
`HandlePacket` method, which in turn will attempt to parse the packet, and print out some text on success or failure.

### Bringup process
1. Initialize a ServiceMaster instance with a robot id. Make sure to set up a serial port or udp socket or both.
2. (Optional) Add known IP endpoints to the ServiceMaster instance.
3. Initialize all of your custom services, and add them to the ServiceMaster.
4. Call `ServiceMaster::Run()`, and spin loop afterwards as it isn't a blocking call.

## Building
### Windows and Linux
Cmake 3.3 or greater is required to build for Windows and Linux. You can configure what robot you want to build for by
specifying it on the command line. Note: if the robot flag is omitted, only the core library will be built. 
```
cd build/
cmake [-DROBOT=Ascent|NONE] ..
cmake --build .
```

### Launchpad
1. Open Code Composer Studio, and import the project using BadgerCommandLibrary/build/launchpad as the root directory.
2. Build the project (Click the hammer icon in the toolbar).
