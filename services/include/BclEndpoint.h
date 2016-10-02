#pragma once

namespace BCL
{
    class BclEndpoint
    {
    public:
        BclEndpoint(int robot_id, bool serial, struct sockaddr_in *addr);
        ~BclEndpoint();
    private:
        
    };
}