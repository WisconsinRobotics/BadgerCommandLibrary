#include "ServiceMaster.h"


void RunServiceMaster(
    ServiceMaster *     serviceMaster
    )
{
    if (!serviceMaster)
        return;

    /*
     * Thoughts from Will:
     * On Windows and Linux, the ServiceMaster is intended to act as the 
     * entry point, schedule services, and receive/send packets. However, on the launchpad,
     * you have the FreeRTOS scheduler, which effectively does all of the scheduling for us.
     * Thus, we reduce the scope of the ServiceMaster for FreeRTOS to only route packets.
     *
     * Each "service", therefore, would be its own Task. When writing a Service, you normally set
     * the sleep interval, Execute(), and PacketHandler() function pointers. You can safely ignore the
     * sleep interval and Execute(). The PacketHandler fn ptr must still be defined, since the ServiceMaster
     * will need that defined in order to update internal service data. Other than that, just use the FreeRTOS
     * vTaskDelayUntil or whatever function you need to set intervals and whatnot.  
     *
     * Another simplification for the launchpad is that everything is via serial. If you want to transmit via serial,
     * 
     *
     * Implementation steps for this function as a FreeRTOS task:
     * Poll the USB queue to see if a new packet has arrived. If it has, call DeserializeBclPacket()
     *     and route it to the subsystems.
     *     Normally, you would also parse the control access packets, like enable/disable services. But!
     *     The launchpad doesn't need to support enable/disable services at runtime.
     * 
     */

     // init task to run the function ServiceMasterTask
     // jump into scheduler, or return back to main to jump into scheduler
}

void ServiceMasterTask(void *param)
{
    ServiceMaster *serviceMaster = (ServiceMaster *) param;

    while (1)
    {
        uint8_t *buffer; // assume data lives in here
        uint8_t buffer_length;
        int data_arrived;

        // TODO poll serial queue
    poll_serial:

        if (!data_arrived)
        {
            vTaskDelay(10);
            continue;
        }        

        DeserializeBclPacket(&pkt, buffer, length);
        
        // route packet to services
        for (int i = 0; i < MAX_SUBSYSTEMS; i++)
        {
            if (!BIT_SET(serviceMaster->_allocated_bitset, i))
                continue;

            Subsystem *subsystem = serviceMaster->Subsystems[i];
            for (int j = 0; j < MAX_SERVICES_PER_SUBSYSTEM; j++)
            {
                if (!BIT_SET(subsystem->_allocated_bitset, i))
                    continue;

                Service *service = subsystem->Services[i];

                if (!service->HandlePacket)
                    continue;

                BCL_STATUS status = (*service->HandlePacket)(service, buffer, buffer_length);
                if (status == BCL_SUCCESS)
                {
                    // clean up, and break out
                    service->LastPacketOrigin.Interface = lpinterface;
                    goto poll_serial;
                }
            }
        }
    }
}