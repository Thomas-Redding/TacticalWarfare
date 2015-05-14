//
//  Server.cpp
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/12/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "Server.h"

Server::Server(ServerInterface &interfaceToUse) {
    interface = &interfaceToUse;
}

Server::~Server() {
    udpSocket.unbind();
}

void Server::update() {
    if(interface->shouldServerBeRunning) {
        checkForUdpMessages();
    }
    else {
        // sleep 1 millisecond
        struct timespec tim, tim2;
        tim.tv_sec = 0;
        tim.tv_nsec = 1000;      // microseconds
        tim.tv_nsec *= 1000;
        nanosleep(&tim , &tim2);
    }
    // sleep 1 microsecond
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 1000;      // microseconds
    tim.tv_nsec *= 1000;
    nanosleep(&tim , &tim2);
}

void Server::checkForUdpMessages() {
    if(udpSocket.receive(udpData, UDP_DATA_LENGTH, udpLengthReceived, udpAddress, udpPort) != sf::Socket::NotReady) {
        std::string messageFromClient = "";
        for(int i = 0; i < udpLengthReceived; i++) {
            messageFromClient += udpData[i];
        }
        processUdpMessage(messageFromClient, udpAddress, udpPort);
    }
}

void Server::processUdpMessage(std::string& messageFromClient, sf::IpAddress address, unsigned int short port) {
    // if request can't be fulfilled, return user with empty username
    // TODO
}

void Server::sendUdpMessages(std::string message, sf::IpAddress address, unsigned int port) {
    char m[message.size()];
    for(int i = 0; i < message.size(); i++) {
        m[i] = message[i];
    }
    udpSocket.send(m, message.size(), address, port);
}
