//
// Created by mwisniewski on 4/1/20.
//

#ifndef SO2P_2_SCISSORS_H
#define SO2P_2_SCISSORS_H

#include <mutex>
#include "Parameters.h"

class Scissors {
public:
    volatile bool areTaken = false;
};


#endif //SO2P_2_SCISSORS_H
