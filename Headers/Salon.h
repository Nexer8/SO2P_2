//
// Created by mwisniewski on 4/2/20.
//

#ifndef SO2P_2_SALON_H
#define SO2P_2_SALON_H

#include <memory>
#include <vector>
#include <list>
#include <condition_variable>
#include <atomic>
#include "Scissors.h"

using namespace std;

static int current_salon_id = 0;

/*! \class Salon
    \brief A class that is responsible for scissors distribution among hairdressers.

    Salon where hairdressers work.
*/
class Salon {
private:
    int id;

public:
    condition_variable cv;
    mutex cv_m;
    vector<shared_ptr<Scissors> > scissors;
    string name;
    atomic<int> no_of_available_scissors = NUMBER_OF_SCISSORS_PER_SALON;

    int get_id() { return id; }

    Salon(string name);

    ~Salon();
};


#endif //SO2P_2_SALON_H
