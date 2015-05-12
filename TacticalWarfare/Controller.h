//
//  Controller.h
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/5/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __TacticalWarfare__Controller__
#define __TacticalWarfare__Controller__

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

class Controller {
public:
    Controller(sf::RenderWindow &w);
    void think();
    void draw();
    void mouseMove(sf::Event::MouseMoveEvent event);
    void mouseDown(sf::Event::MouseButtonEvent event);
    void mouseUp(sf::Event::MouseButtonEvent event);
    void keyDown(sf::Event::KeyEvent event);
    void keyUp(sf::Event::KeyEvent event);
    void textEntered(sf::Event::TextEvent event);
    virtual void giveOtherController(Controller &cont);
    virtual void sendMessage(std::string message);
protected:
    sf::RenderWindow *window;
};


#endif /* defined(__TacticalWarfare__Controller__) */
