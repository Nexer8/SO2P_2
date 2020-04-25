//
// Created by mwisniewski on 4/25/20.
//

#ifndef SO2P_2_SUPPLIES_H
#define SO2P_2_SUPPLIES_H


#include <memory>
#include <vector>
#include <thread>
#include "Scissors.h"

class Supplies {
private:
    std::vector<std::shared_ptr<Scissors> > scissors;
    std::thread life;

    void supply();

public:
    Supplies(std::vector<std::shared_ptr<Scissors> > scissors);

    ~Supplies();
};


#endif //SO2P_2_SUPPLIES_H
