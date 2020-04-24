//
// Created by mwisniewski on 4/1/20.
//

#include <iostream>
#include "../Headers/Hairdresser.h"

using namespace std;

Hairdresser::Hairdresser(shared_ptr<Salon> salon, Scissors &thinning_scissors, Scissors &hair_cutting_shears,
                         vector<shared_ptr<Customer> > &customers) : salon(salon), thinning_scissors(thinning_scissors),
                                                                     hair_cutting_shears(hair_cutting_shears),
                                                                     customers(customers),
                                                                     life(&Hairdresser::work, this),
                                                                     id(current_hairdresser_id++) {
    state = Hairdressers_state::WAITING_FOR_A_CLIENT;
}

Hairdresser::~Hairdresser() {
    customers.clear();
    life.join();
}

void Hairdresser::take_a_break() {
    state = Hairdressers_state::TAKING_A_BREAK;
    this_thread::sleep_for(chrono::milliseconds(BREAK_TIME));
}

void Hairdresser::cut_hair() {
    if (no_of_ready_customers == 0) {
        state = Hairdressers_state::END_OF_WORK;
        this_thread::sleep_for(chrono::seconds(WORKING_DAY_TIME));
    }

    state = Hairdressers_state::WAITING_FOR_A_CLIENT;
    shared_ptr<Customer> current_customer = wait_for_a_client();

    if (current_customer == nullptr) {
        return;
    } else {
        current_customer->state = Customers_state::HAVING_A_HAIRCUT;
    }

    state = Hairdressers_state::WAITING_FOR_SCISSORS;

    lock(thinning_scissors.mutex, hair_cutting_shears.mutex,
         current_customer->mutex);    // ensures there are no deadlocks
    lock_guard<mutex> thinning_scissors_lock(thinning_scissors.mutex, adopt_lock);
    lock_guard<mutex> hair_cutting_shears_lock(hair_cutting_shears.mutex, adopt_lock);
    lock_guard<mutex> current_customer_lock(current_customer->mutex, adopt_lock);

    state = Hairdressers_state::CUTTING_HAIR;
    this_thread::sleep_for(chrono::milliseconds(CUTTING_HAIR_TIME));

    current_customer->state = Customers_state::DONE;
    no_of_ready_customers--;
}

void Hairdresser::work() {
    salon->wait_for_all();

    while (salon->no_of_ready_hairdressers) {
        take_a_break();
        cut_hair();
    }
}

shared_ptr<Customer> Hairdresser::wait_for_a_client() {
    for (auto customer : customers) {
        if (customer->get_state() == Customers_state::WAITING_FOR_A_CUT) {
            customer->salon = salon;

            return customer;
        }
    }
    return nullptr;
}
