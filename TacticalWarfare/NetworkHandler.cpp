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
    udpSocket.bind(sf::Socket::AnyPort);
}

NetworkHandler::~NetworkHandler()
{
    // send disconnect packet
    udpSocket.unbind();
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
        
        // get messages from from server - todo
        sf::IpAddress sender;
        unsigned short port;
        std::size_t received;
        char data[2048];
        std::string potentialServerData;
        unsigned int i;
        unsigned int j;
        for(i=0; i < 1000; i++) {
            if(udpSocket.receive(data, 2048, received, sender, port) != sf::Socket::NotReady) {
                potentialServerData = "";
                for(j=0; j < received; j++) {
                    potentialServerData += data[j];
                }
                if(potentialServerData!="") {
                    appInterface->lock.lock();
                    appInterface->receivedFromServer.push_back(potentialServerData);
                    appInterface->lock.unlock();
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
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
