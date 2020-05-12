//
// Created by mwisniewski on 4/25/20.
//

#ifndef SO2P_2_SUPPLIES_H
#define SO2P_2_SUPPLIES_H


#include <memory>
#include <vector>
#include <thread>
#include "Salon.h"

using namespace std;

/*! \class Supplies
    \brief A class that is responsible for supplying a salon with scissors.

    Supplies of scissors during the work day.
*/
class Supplies {
private:
    Salon &salon;
    thread life;

    void supply();

public:
    Supplies(Salon &salon);

    ~Supplies();
};


#endif //SO2P_2_SUPPLIES_H
