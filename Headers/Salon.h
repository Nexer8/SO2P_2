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
#include "Customer.h"

class Salon {
private:
    std::condition_variable cv;
    std::mutex cv_m;

public:
    std::vector<std::shared_ptr<Scissors> > scissors;
    std::vector<std::shared_ptr<Customer> > customers;
    volatile int no_of_ready_hairdressers = 0;
    volatile int no_of_ready_customers = 0;

    void wait_for_all();

    Salon();

    ~Salon();
};


#endif //SO2P_2_SALON_H
