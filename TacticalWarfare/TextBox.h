//
//  TextBox.h
//  client
//
//  Created by Thomas Redding on 6/10/14.
//  Copyright (c) 2014 Thomas Redding. All rights reserved.
//

#ifndef __client__TextBox__
#define __client__TextBox__

#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>

class TextBox
{
public:
    // set-up
    TextBox(sf::Font *fontToUse, sf::Vector2f pos, sf::Vector2f siz);
    
    /*
     0 - text box
     1 - password box
     2 - number box
    */
    TextBox(sf::Font *fontToUse, sf::Vector2f pos, sf::Vector2f siz, int typeOfBox);
    int maxCharacterLength = 10;
    
    // mandatory hook-up
    void render(sf::RenderWindow* window); // draws the textbox
    void textEntered(int key);  // for "normal" keys
    void keyPressed(sf::Event::KeyEvent key);  // for the "delete", "left", and "right" buttons
    bool mouseButtonPressed(sf::Event::MouseButtonEvent mouse);  // this causese the box to become "focused" when the user clicks on it
    
    // adjusting size & position (centered)
    void setPosition(sf::Vector2f vect);
    void setPosition(float x, float y);
    sf::Vector2f getPosition();
    void setSize(sf::Vector2f vect);
    void setSize(float x, float y);
    void center(sf::Vector2u screenSize);
    
    // optional hook-up
    void focus();
    void unfocus();
    
    std::string getValue();
    std::string setValue(std::string newValue);
private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2f absolutePosition;
    sf::Vector2f absoluteSize;
    std::string str;
    sf::Font *font;
    int cursorSpot = 0;
    bool focused = false;
    sf::Vector2u windowSize;
    int boxType = 0;
    std::clock_t startClock = std::clock();
    
    std::string UnicodeToString(int key);
};

#endif /* defined(__client__TextBox__) */
