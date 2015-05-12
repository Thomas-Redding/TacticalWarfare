//
//  MenuPage.h
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/5/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __TacticalWarfare__MenuPage__
#define __TacticalWarfare__MenuPage__

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "ResourcePath.hpp"
#include "MenuButton.h"

struct MenuPage {
    std::string name;
    std::vector<MenuButton> buttons;
    std::vector<sf::Text> labels;
};

#endif /* defined(__TacticalWarfare__MenuPage__) */
