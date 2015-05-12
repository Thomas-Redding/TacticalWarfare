//
//  User.h
//  TacticalWarfare
//
//  Created by Morgan Redding on 5/12/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __TacticalWarfare__User__
#define __TacticalWarfare__User__

#include <iostream>
#include <SFML/Network.hpp>

struct User {
    User();
    std::string username;
    std::string password;
    sf::IpAddress address;
    unsigned short port;

    inline bool operator==(const User& a) const;
    
    inline size_t getId() const;
    
private:
    
    size_t id;
    
    static size_t numberCreated;
};

#endif /* defined(__TacticalWarfare__User__) */
