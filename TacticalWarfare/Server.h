//
//  Server.h
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/12/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __TacticalWarfare__Server__
#define __TacticalWarfare__Server__

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <SFML/Network.hpp>
#include "ServerInterface.h"

class Server {
public:
    Server(ServerInterface &interface);
    ~Server();
    void update();
private:
    void checkForUdpMessages();
    void sendMessage(std::string message, sf::IpAddress address, unsigned int port);
    
    sf::UdpSocket udpSocket;
    std::vector<std::string> messagesFromClients;
    ServerInterface *interface;
};

#endif /* defined(__TacticalWarfare__Server__) */
