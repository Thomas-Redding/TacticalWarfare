//
//  TacticalWarfareServer.h
//  TacticalWarfare
//
//  Created by Morgan Redding on 5/14/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __TacticalWarfare__TacticalWarfareServer__
#define __TacticalWarfare__TacticalWarfareServer__

#include "Server.h"

class TacticalWarfareServer : public Server {
public:
    TacticalWarfareServer(ServerInterface &interface) : Server(interface) {};
private:
    void processUdpMessage(std::string& message, sf::IpAddress address, unsigned short port);
};


#endif /* defined(__TacticalWarfare__TacticalWarfareServer__) */
