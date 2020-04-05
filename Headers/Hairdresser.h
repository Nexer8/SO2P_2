//
// Created by mwisniewski on 4/1/20.
//

#ifndef SO2P_2_HAIRDRESSER_H
#define SO2P_2_HAIRDRESSER_H

#include <thread>
#include <list>
#include "Scissors.h"
#include "Customer.h"
#include "Salon.h"

enum class Hairdressers_state {
    WAITING_FOR_A_CLIENT,
    TAKING_A_BREAK,
    CUTTING_HAIR,
    WAITING_FOR_SCISSORS
};

static int current_hairdresser_id = 0;

/*! \class Hairdresser
    \brief A class that simulates hairdresser.

    Hairdresser that work at a hairdresser's.
*/
class Hairdresser {
private:
    int id;
    volatile Hairdressers_state state;
    Salon &salon;
    Scissors &thinning_scissors;
    Scissors &hair_cutting_shears;
    std::list<std::shared_ptr<Customer> > &customers;
    std::thread life;

    std::shared_ptr<Customer> wait_for_a_client();

    void work();

    void take_a_break();

    void cut_hair();

public:
    Hairdresser(Salon &salon, Scissors &thinning_scissors, Scissors &hair_cutting_shears,
                std::list<std::shared_ptr<Customer> > &customers);

    ~Hairdresser();

    int get_id() { return id; }

    Hairdressers_state get_state() { return state; }
};


#endif //SO2P_2_HAIRDRESSER_H
