//
// Created by mwisniewski on 4/1/20.
//

#ifndef SO2P_2_SCISSORS_H
#define SO2P_2_SCISSORS_H

#include <mutex>
#include <atomic>
#include "Parameters.h"

/*! \class Scissors
    \brief A class that is responsible for imitating scissors.

    Scissors used by Hairdressers inside a salon.
*/
class Scissors {
public:
    std::atomic<bool> areTaken = false;
};


#endif //SO2P_2_SCISSORS_H
