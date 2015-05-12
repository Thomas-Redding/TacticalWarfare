//
//  Controller.cpp
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/5/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "Controller.h"

Controller::Controller(sf::RenderWindow &w) {
    window = &w;
}

void Controller::think() {
}

void Controller::draw() {
}

void Controller::mouseMove(sf::Event::MouseMoveEvent event) {
}

void Controller::mouseDown(sf::Event::MouseButtonEvent event) {
}

void Controller::mouseUp(sf::Event::MouseButtonEvent event) {
}

void Controller::keyDown(sf::Event::KeyEvent event) {
}

void Controller::keyUp(sf::Event::KeyEvent event) {
}

void textEntered(sf::Event::TextEvent event) {
}

void Controller::giveOtherController(Controller &cont) {
    //
}

void Controller::sendMessage(std::string message) {
    std::cout << "QQQ";
}
