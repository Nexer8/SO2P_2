//
// Created by mwisniewski on 4/2/20.
//

#include "../Headers/Salon.h"

Salon::Salon(std::string name) : name(name), id(current_salon_id++) {
    for (int i = 0; i < NUMBER_OF_SCISSORS; i++) {
        scissors.emplace_back(new Scissors());
    }

    for (int i = 0; i < NUMBER_OF_CLIENTS; i++) {
        customers.emplace_back(new Customer());
        no_of_ready_customers++;
    }
}

Salon::~Salon() {
    scissors.clear();
    customers.clear();
}

void Salon::wait_for_all() {
    std::unique_lock<std::mutex> lk(cv_m);
    no_of_ready_hairdressers++;
    cv.wait(lk, [&] { return no_of_ready_hairdressers >= NUMBER_OF_HAIRDRESSERS_PER_SALON; });
    cv.notify_all();
}
