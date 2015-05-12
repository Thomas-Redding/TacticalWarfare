//
//  App.h
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/5/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __TacticalWarfare__App__
#define __TacticalWarfare__App__

#include <stdio.h>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "MainMenu.h"
#include "NetworkInterface.h"

class App : Controller {
public:
    App(sf::RenderWindow &w);
    App(sf::RenderWindow &w, NetworkInterface &interfaceForNetwork);
    void think();
    void draw();
    void mouseMove(sf::Event::MouseMoveEvent event);
    void mouseDown(sf::Event::MouseButtonEvent event);
    void mouseUp(sf::Event::MouseButtonEvent event);
    void keyDown(sf::Event::KeyEvent event);
    void keyUp(sf::Event::KeyEvent event);
    void textEntered(sf::Event::TextEvent event);
    virtual void giveOtherController(Controller &cont);
    /*
     0 - successful processing of message
     -1 - message was invalid
     -2 - unknown validity of message
    */
    virtual void sendMessage(std::string message);
private:
    sf::Texture buttonTexture;
    sf::Font font;
    MainMenu mainMenu;
    NetworkInterface *networkInterface;
    
    std::vector<std::string> splitString(std::string str, char delimiter);
    void pollEventsFromServer();
    void handleServerInfo(std::string message);
};

#endif /* defined(__TacticalWarfare__App__) */
