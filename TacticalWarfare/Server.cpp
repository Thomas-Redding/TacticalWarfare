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
    interface->lock.lock();
    if(interface->shouldServerBeRunning) {
        interface->lock.unlock();
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
        
        std::unordered_map<size_t, User>::iterator it = users.find(udpAddress.toInteger());
        if(it == users.end()) {
            User user = commandFromNewUser(messageFromClient, udpAddress, udpPort);
            if(user.username != "") {
                users.insert(std::pair<size_t, User>(udpAddress.toInteger(), user));
            }
        }
        else {
            commandFromOldUser(it, messageFromClient);
        }
    }
}

User Server::commandFromNewUser(std::string messageFromClient, sf::IpAddress address, unsigned int short port) {
    // if request can't be fulfilled, return user with empty username
    // TODO
    return User("", 0, 0);
}

void Server::commandFromOldUser(std::unordered_map<size_t, User>::iterator client, std::string message) {
    // TODO
}


void Server::sendMessage(std::string message, sf::IpAddress address, unsigned int port) {
    char m[message.size()];
    for(int i = 0; i < message.size(); i++) {
        m[i] = message[i];
    }
    udpSocket.send(m, message.size(), address, port);
}
