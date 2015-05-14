//
//  NetworkHandler.cpp
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/11/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "NetworkHandler.h"

NetworkHandler::NetworkHandler(NetworkInterface &interface) {
    appInterface = &interface;
    udpSocket.setBlocking(false); // just say no to blocking
}

NetworkHandler::~NetworkHandler()
{
    // send disconnect packet
    udpSocket.unbind();
}

void NetworkHandler::connectToServer() {
    // ----- The client -----
    // Create a socket and bind it to some free port
    udpSocket.bind(sf::Socket::AnyPort);
}

void NetworkHandler::update() {
    if(appInterface->networkClosingStage == 0) {
        // everything is normal
        
        // send messages to server
        appInterface->lock.lock();
        if(appInterface->sendToServer.size() != 0) {
            std::string message = appInterface->sendToServer[0];
            appInterface->sendToServer.erase(appInterface->sendToServer.begin(), appInterface->sendToServer.begin()+1);
            appInterface->lock.unlock();
            
            // send message to server
            udpSocket.send(message.c_str(), message.length(), serverAddress, serverPort);
        }
        else {
            appInterface->lock.unlock();
        }
        
        char buffer[1024];
        std::size_t received = 0;
        sf::IpAddress sender;
        unsigned short port;
        udpSocket.receive(buffer, sizeof(buffer), received, sender, port);
        std::cout << sender.toString() << " said: " << buffer << std::endl;
    }
    else {
        appInterface->networkClosingStage = 2;
    }
    
    // sleep for 1 millisecond
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 1000;      // microseconds
    tim.tv_nsec *= 1000;
    nanosleep(&tim , &tim2);
}
