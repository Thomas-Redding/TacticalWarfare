//
//  NetworkHandler.h
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/11/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __TacticalWarfare__NetworkHandler__
#define __TacticalWarfare__NetworkHandler__

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <SFML/Network.hpp>
#include "NetworkInterface.h"

class NetworkHandler {
public:
    NetworkHandler(NetworkInterface &interface);
    ~NetworkHandler();
    void update();
private:
    NetworkInterface *appInterface;
    void sendMessageToServer(std::string message);
    void connectToServer(sf::IpAddress addressOfServer, unsigned short portOfServer);
    void sendUdpMessage(std::string message);
    void receivedUdpMessage(std::string message);
    sf::IpAddress serverAddress = "";
    unsigned short serverPort = 0;
    sf::UdpSocket udpSocket;
};

#endif /* defined(__TacticalWarfare__NetworkHandler__) */
