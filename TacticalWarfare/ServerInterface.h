//
//  ServerInterface.h
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/12/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __TacticalWarfare__ServerInterface__
#define __TacticalWarfare__ServerInterface__

#include <stdio.h>
#include <mutex>

struct ServerInterface {
    std::mutex lock;
    bool shouldServerBeRunning = false;
};


#endif /* defined(__TacticalWarfare__ServerInterface__) */
