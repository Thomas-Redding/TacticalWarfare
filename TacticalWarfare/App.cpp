//
//  App.cpp
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/5/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "App.h"

App::App(sf::RenderWindow &w) :Controller(w), mainMenu(w, this) {
}

App::App(sf::RenderWindow &w, NetworkInterface &interfaceForNetwork) :Controller(w), mainMenu(w, this) {
    networkInterface = &interfaceForNetwork;
}

void App::think() {
    pollEventsFromServer();
    mainMenu.think();
}

void App::pollEventsFromServer() {
    networkInterface->lock.lock();
    int size = networkInterface->receivedFromServer.size();
    networkInterface->lock.unlock();
    for(int i=0; i<size; i++) {
        networkInterface->lock.lock();
        std::string message = networkInterface->receivedFromServer[0];
        networkInterface->receivedFromServer.erase(networkInterface->receivedFromServer.begin(), networkInterface->receivedFromServer.begin()+1);
        networkInterface->lock.unlock();
        handleServerInfo(message);
    }
}

void App::handleServerInfo(std::string message) {
    //
}

void App::draw() {
     mainMenu.draw();
}

void App::mouseMove(sf::Event::MouseMoveEvent event) {
     mainMenu.mouseMove(event);
}

void App::mouseDown(sf::Event::MouseButtonEvent event) {
     mainMenu.mouseDown(event);
}

void App::mouseUp(sf::Event::MouseButtonEvent event) {
     mainMenu.mouseUp(event);
}

void App::keyDown(sf::Event::KeyEvent event) {
     mainMenu.keyDown(event);
}

void App::keyUp(sf::Event::KeyEvent event) {
     mainMenu.keyUp(event);
}

void App::textEntered(sf::Event::TextEvent event) {
    mainMenu.textEntered(event);
}

void App::sendMessage(std::string message) {
    std::vector<std::string> vect = splitString(message, '\n');
    if(vect.size() == 0) {
        return -1;
    }
    
    if(vect[0] == "Attempt Login") {
        if(vect.size() < 3) {
            return -1;
        }
        std::cout << "{" << message << "}";
        networkInterface->lock.lock();
        networkInterface->sendToServer.push_back(vect[1]+"\n"+vect[2]);
        networkInterface->lock.unlock();
    }
    else {
        // todo
    }
    
    return -2;
}

std::vector<std::string> App::splitString(std::string str, char delimiter) {
    // split str by the deliminatr
    /*
     Ex: "It was the best of times" -> ["It", "was", "the", "best", "of", "times"]
    */
    std::vector<std::string> internal;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tok;
    
    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }
    
    return internal;
}

void App::giveOtherController(Controller &cont) {
    //
}