//
//  MenuButton.h
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/5/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __TacticalWarfare__MenuButton__
#define __TacticalWarfare__MenuButton__

#include <stdio.h>
#include <SFML/Graphics.hpp>

class MenuButton {
public:
    MenuButton();
    MenuButton(std::string labelInput, sf::Texture *texture, sf::Font *font);
    void draw(sf::RenderWindow *w);
    void center(sf::Vector2u screenSize);
    
    std::string label;
    sf::Sprite sprite;
    sf::Text text;
    float x = 0;
    float y = 0;
    unsigned int textureWidth;
    unsigned int textureHeight;
    float size = 300;
};


#endif /* defined(__TacticalWarfare__MenuButton__) */
