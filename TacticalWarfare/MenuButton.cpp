//
//  MenuButton.cpp
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/5/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "MenuButton.h"

MenuButton::MenuButton() {
    //
}

MenuButton::MenuButton(std::string labelInput, sf::Texture *texture, sf::Font *font) {
    label = labelInput;
    sprite = sf::Sprite(*texture);
    text = sf::Text(labelInput, *font, 100);
    textureWidth = texture->getSize().x;
    textureHeight = texture->getSize().y;
}
void MenuButton::draw(sf::RenderWindow *w) {
    sprite.setPosition(x, y);
    sprite.setScale(size/textureWidth, size/textureWidth);
    float fontSize = textureHeight * size/textureWidth;
    w->draw(sprite);
    text.setScale(fontSize/120, fontSize/120);
    float leftMargin = (sprite.getGlobalBounds().width - text.getGlobalBounds().width)/2;
    float bottomMargin = 0.05*fontSize;
    text.setPosition(x+leftMargin, y-bottomMargin);
    w->draw(text);
}

void MenuButton::center(sf::Vector2u screenSize) {
    size = screenSize.x/3.0;
    x = screenSize.x/2.0 - size/2.0;
    y = screenSize.y/2.0 - size/2.0*textureHeight/textureWidth;
    
}