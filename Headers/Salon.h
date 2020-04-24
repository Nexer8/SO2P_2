//
// Created by mwisniewski on 4/2/20.
//

#ifndef SO2P_2_SALON_H
#define SO2P_2_SALON_H

#include <memory>
#include <vector>
#include <list>
#include <condition_variable>
#include "Scissors.h"

static int current_salon_id = 0;

class Salon {
private:
    int id;
    std::condition_variable cv;
    std::mutex cv_m;

public:
    std::vector<std::shared_ptr<Scissors> > scissors;
    std::string name;
    volatile int no_of_ready_hairdressers = 0;

    void wait_for_all();

    int get_id() { return id; }

    Salon(std::string name);

    ~Salon();
};


#endif //SO2P_2_SALON_H
