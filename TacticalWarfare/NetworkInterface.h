//
//  NetworkInterface.h
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/11/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __TacticalWarfare__NetworkInterface__
#define __TacticalWarfare__NetworkInterface__

#include <stdio.h>
#include <vector>
#include <mutex>

struct NetworkInterface {
    std::mutex lock;
    std::vector<std::string> sendToServer;
    std::vector<std::string> receivedFromServer;
    
    /*
     0 - all is good
     1 - should close ASAP
     2 - network is closed
     */
    int networkClosingStage;
};

#endif /* defined(__TacticalWarfare__NetworkInterface__) */
