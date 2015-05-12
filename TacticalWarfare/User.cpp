//
//  User.cpp
//  TacticalWarfare
//
//  Created by Morgan Redding on 5/12/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "User.h"

size_t User::numberCreated = 0;

User::User() : id(numberCreated) {
    numberCreated++;
}

bool User::operator==(const User &a) const {
    return id == a.id;
}

inline size_t User::getId() const {
    return id;
}