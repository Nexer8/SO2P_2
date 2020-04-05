//
// Created by mwisniewski on 4/1/20.
//

#include <iostream>
#include "../Headers/Hairdresser.h"

using namespace std;

Hairdresser::Hairdresser(Salon &salon, Scissors &thinning_scissors, Scissors &hair_cutting_shears,
                         list<shared_ptr<Customer> > &customers) : salon(salon), thinning_scissors(thinning_scissors),
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
//    std::cout << "Hairdresser" << id << " is " << "taking a break\n";

    chrono::milliseconds break_time(BREAK_TIME);
    this_thread::sleep_for(break_time);
}

void Hairdresser::cut_hair() {
    state = Hairdressers_state::WAITING_FOR_A_CLIENT;
    shared_ptr<Customer> current_customer = wait_for_a_client();

    if (current_customer == nullptr) {
//        std::cout << "No customers left\n";
        return;
    }

    state = Hairdressers_state::WAITING_FOR_SCISSORS;
//    std::cout << "Hairdresser" << id << " is " << "waiting for scissors\n";

    lock(thinning_scissors.mutex, hair_cutting_shears.mutex,
         current_customer->mutex);    // ensures there are no deadlocks
    lock_guard<mutex> thinning_scissors_lock(thinning_scissors.mutex, adopt_lock);
    lock_guard<mutex> hair_cutting_shears_lock(hair_cutting_shears.mutex, adopt_lock);
    lock_guard<mutex> current_customer_lock(current_customer->mutex, adopt_lock);

    current_customer->set_state(Customers_state::HAVING_A_HAIRCUT);
//    std::cout << "Customer" << current_customer->get_id() << " is " << "having a haircut\n";

    state = Hairdressers_state::CUTTING_HAIR;
//    std::cout << "Hairdresser" << id << " is " << "cutting hair\n";

    chrono::milliseconds cutting_har_time(CUTTING_HAIR_TIME);
    this_thread::sleep_for(cutting_har_time);

    current_customer->set_state(Customers_state::WAITING_FOR_A_CUT);

    customers.remove(current_customer);
    salon.no_of_ready_customers--;
}

void Hairdresser::work() {
    salon.wait_for_all();

    while (salon.no_of_ready_customers) {
        take_a_break();
        cut_hair();
    }
}

shared_ptr<Customer> Hairdresser::wait_for_a_client() {
    for (auto customer : customers) {
        if (customer->get_state() == Customers_state::WAITING_FOR_A_CUT) {
            return customer;
        }
    }
    return nullptr;
}
