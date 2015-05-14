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
#include <unordered_map>

#include <SFML/Network.hpp>

#include "ServerInterface.h"
#include "User.h"

class Server {
public:
    Server(ServerInterface &interface);
    ~Server();
    void update();
    
protected:
    
    virtual void processUdpMessage(std::string& message, sf::IpAddress address, unsigned short port) = 0;
    ServerInterface *interface;
    
private:
    
    bool checkForUdpMessages();
    void sendUdpMessages(std::string message, sf::IpAddress address, unsigned int port);
    
    sf::UdpSocket udpSocket;
    sf::IpAddress udpAddress;
    unsigned short udpPort;
    static const size_t UDP_DATA_LENGTH = 1024;
    char udpData[UDP_DATA_LENGTH];
    size_t udpLengthReceived;
};

#endif /* defined(__TacticalWarfare__Server__) */
