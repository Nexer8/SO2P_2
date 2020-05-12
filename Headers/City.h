//
// Created by mwisniewski on 4/22/20.
//

#ifndef SO2P_2_CITY_H
#define SO2P_2_CITY_H


#include "Salon.h"

using namespace std;

/*! \class City
    \brief A class that wraps salons together.

    City where salons are located.
*/
class City {
public:
    vector<shared_ptr<Salon> > &salons;
    volatile int no_of_ready_salons = 0;

    City(vector<shared_ptr<Salon> > &salons);

    ~City();
};


#endif //SO2P_2_CITY_H
