//
// Created by mwisniewski on 4/1/20.
//

#ifndef SO2P_2_HAIRDRESSER_H
#define SO2P_2_HAIRDRESSER_H

#include <thread>
#include <list>
#include <atomic>
#include "Scissors.h"
#include "Customer.h"
#include "Salon.h"

using namespace std;

enum class Hairdressers_state {
    WAITING_FOR_A_CLIENT,
    TAKING_A_BREAK,
    CUTTING_HAIR,
    WAITING_FOR_SCISSORS,
    END_OF_WORK
};

static int current_hairdresser_id = 0;
static atomic<int> no_of_ready_customers = NUMBER_OF_CLIENTS;

/*! \class Hairdresser
    \brief A class that simulates hairdresser.

    Hairdresser that work at a hairdresser's.
*/
class Hairdresser {
private:
    int id;
    atomic<Hairdressers_state> state;
    shared_ptr<Salon> salon;
    shared_ptr<Scissors> thinning_scissors;
    shared_ptr<Scissors> hair_cutting_shears;
    vector<shared_ptr<Customer> > &customers;
    thread life;

    shared_ptr<Customer> wait_for_a_client();

    void work();

    void get_scissors();

    void return_scissors();

    void take_a_break();

    void cut_hair();

public:
    Hairdresser(shared_ptr<Salon> salon, vector<shared_ptr<Customer> > &customers);

    ~Hairdresser();

    int get_id() { return id; }

    vector<shared_ptr<Customer> > get_customers() {
        return customers;
    }

    Hairdressers_state get_state() { return state; }
};


#endif //SO2P_2_HAIRDRESSER_H
