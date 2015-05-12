//
//  MainMenu.h
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/5/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __TacticalWarfare__MainMenu__
#define __TacticalWarfare__MainMenu__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "ResourcePath.hpp"
#include "Controller.h"
#include "MenuPage.h"
#include "TextBox.h"

enum MainMenuPageName {
    MainMenuPageName_Home = 0,
    MainMenuPageName_Login = 1
};

class MainMenu : Controller {
public:
    MainMenu(sf::RenderWindow &w);
    MainMenu(sf::RenderWindow &w, Controller *parentApp);
    void think();
    void draw();
    void mouseMove(sf::Event::MouseMoveEvent event);
    void mouseDown(sf::Event::MouseButtonEvent event);
    void mouseUp(sf::Event::MouseButtonEvent event);
    void keyDown(sf::Event::KeyEvent event);
    void keyUp(sf::Event::KeyEvent event);
    void textEntered(sf::Event::TextEvent event);
    void giveOtherController(Controller &cont);
    void sendMessage(std::string message);
private:
    std::vector<MenuPage> pages;
    sf::Texture buttonTexture;
    sf::Font font;
    MainMenuPageName pageNum = MainMenuPageName_Home;
    Controller *app;
    
    void buttonClicked(int index);
    int frameCounter = 0;
    
    TextBox usernameTextBox;
    TextBox passwordTextBox;
};


#endif /* defined(__TacticalWarfare__MainMenu__) */
