//
//  MainMenu.cpp
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/5/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow &w) :Controller(w), usernameTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 50)), serverIpTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 30), 2), portTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 30), 2) {
    std::cout << "Error: Main Menu not constructed with access to parent app";
    w.close();
}

MainMenu::MainMenu(sf::RenderWindow &w, Controller* parentApp) :Controller(w), usernameTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 50)), serverIpTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 30), 2), portTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 30), 2) {
    app = parentApp;
    if(!buttonTexture.loadFromFile(resourcePath() + "button.png")) {
        return;
    }
    
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return;
    }
    
    sf::Vector2u screenSize = window->getSize();
    
    // Home
    pages.push_back(MenuPage());
    pages[0].buttons.push_back(MenuButton("Log In", &buttonTexture, &font));
    pages[0].buttons[0].size = screenSize.x/3.0;
    pages[0].buttons[0].center(screenSize);
    
    // Login
    pages.push_back(MenuPage());
    pages[1].buttons.push_back(MenuButton("Home", &buttonTexture, &font));
    pages[1].buttons[0].size = screenSize.x/3.0;
    pages[1].buttons[0].x = 0;
    pages[1].buttons[0].y = 0;
    pages[1].buttons.push_back(MenuButton("Sign In", &buttonTexture, &font));
    pages[1].buttons[1].size = screenSize.x/3.0;
    pages[1].buttons[1].center(screenSize);
    pages[1].buttons[1].y += screenSize.x/10.0;
    
    usernameTextBox.setSize(screenSize.x/2.0, screenSize.x/20.0);
    usernameTextBox.center(screenSize);
    usernameTextBox.setPosition(usernameTextBox.getPosition().x, usernameTextBox.getPosition().y - screenSize.x/5.0);
    serverIpTextBox.setSize(screenSize.x/2.0, screenSize.x/20.0);
    serverIpTextBox.center(screenSize);
    serverIpTextBox.maxCharacterLength = 20;
    serverIpTextBox.setPosition(serverIpTextBox.getPosition().x, serverIpTextBox.getPosition().y - screenSize.x/10.0);
    portTextBox.setSize(screenSize.x/2.0, screenSize.x/20.0);
    portTextBox.center(screenSize);
    portTextBox.maxCharacterLength = 5;
    
}

void MainMenu::think() {
    //
}

void MainMenu::draw() {
    for(int i=0; i<pages[pageNum].buttons.size(); i++) {
        pages[pageNum].buttons[i].draw(window);
    }
    
    if(pageNum == MainMenuPageName_Login) {
        usernameTextBox.render(window);
        serverIpTextBox.render(window);
        portTextBox.render(window);
    }
    else {
        usernameTextBox.unfocus();
        serverIpTextBox.unfocus();
        portTextBox.unfocus();
    }
    frameCounter++;
}

void MainMenu::mouseMove(sf::Event::MouseMoveEvent event) {
}

void MainMenu::mouseDown(sf::Event::MouseButtonEvent event) {
    float x = event.x;
    float y = event.y;
    for(int i=0; i<pages[pageNum].buttons.size(); i++) {
        if(x > pages[pageNum].buttons[i].x && x < pages[pageNum].buttons[i].x + pages[pageNum].buttons[i].size && y > pages[pageNum].buttons[i].y && y < pages[pageNum].buttons[i].y + pages[pageNum].buttons[i].size*pages[pageNum].buttons[i].textureHeight/pages[pageNum].buttons[i].textureWidth) {
            buttonClicked(i);
            break;
        }
    }
    if(pageNum == MainMenuPageName_Login) {
        usernameTextBox.mouseButtonPressed(event);
        serverIpTextBox.mouseButtonPressed(event);
        portTextBox.mouseButtonPressed(event);
    }
}

void MainMenu::buttonClicked(int index) {
    if(pageNum == MainMenuPageName_Home) {
        if(pages[pageNum].buttons[index].label == "Log In") {
            pageNum = MainMenuPageName_Login;
        }
    }
    else if(pageNum == MainMenuPageName_Login) {
        if(pages[pageNum].buttons[index].label == "Home") {
            pageNum = MainMenuPageName_Home;
        }
        else {
            app->sendMessage("Attempt Login\n" + usernameTextBox.getValue() + "\n" + serverIpTextBox.getValue() + "\n" + portTextBox.getValue());
        }
    }
}

void MainMenu::mouseUp(sf::Event::MouseButtonEvent event) {
}

void MainMenu::keyDown(sf::Event::KeyEvent event) {
    if(pageNum == MainMenuPageName_Login) {
        usernameTextBox.keyPressed(event);
        serverIpTextBox.keyPressed(event);
        portTextBox.keyPressed(event);
    }
}

void MainMenu::keyUp(sf::Event::KeyEvent event) {
}

void MainMenu::textEntered(sf::Event::TextEvent event) {
    if(pageNum == MainMenuPageName_Login) {
        usernameTextBox.textEntered(event.unicode);
        serverIpTextBox.textEntered(event.unicode);
        portTextBox.textEntered(event.unicode);
    }
}

void MainMenu::sendMessage(std::string message) {
}

void MainMenu::giveOtherController(Controller &cont) {
}