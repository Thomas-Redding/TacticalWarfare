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
    udpSocket.setBlocking(false);
    connectToServer("137.22.169.68", 6670);
}

NetworkHandler::~NetworkHandler()
{
    // send disconnect packet
    udpSocket.unbind();
    udpSocket.bind(sf::Socket::AnyPort);
}

void NetworkHandler::connectToServer(sf::IpAddress addressOfServer, unsigned short portOfServer) {
    serverAddress = addressOfServer;
    serverPort = portOfServer;
}

void NetworkHandler::update() {
    if(appInterface->networkClosingStage == 0) {
        // read messages from server
        char buffer[1024];
        std::size_t received = 0;
        sf::IpAddress sender;
        unsigned short port;
        udpSocket.receive(buffer, sizeof(buffer), received, sender, port);
        receivedUdpMessage(std::string(buffer));
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

void NetworkHandler::sendUdpMessage(std::string message) {
    udpSocket.send(message.c_str(), message.length(), serverAddress, serverPort);
}

void NetworkHandler::receivedUdpMessage(std::string message) {
    std::cout << "Received Message: " << message << std::endl;
    // do stuff with this
}
