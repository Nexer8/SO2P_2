#include "../Headers/Common.h"
#include "../Headers/Hairdresser.h"
#include "../Headers/Supplies.h"
#include "../Headers/Visualizer.h"
#include <iostream>
#include <list>
#include <memory>
#include <vector>

int main() {
    vector<shared_ptr<Hairdresser>> hairdressers;
    vector<shared_ptr<Customer>> customers;
    vector<shared_ptr<Salon>> salons;

    customers.reserve(NUMBER_OF_CLIENTS);
    for (int i = 0; i < NUMBER_OF_CLIENTS; i++) {
        customers.emplace_back(new Customer());
    }

    salons.reserve(NUMBER_OF_SALONS);
    for (int i = 0; i < NUMBER_OF_SALONS; i++) {
        salons.emplace_back(new Salon("Salon " + to_string(i)));
    }

    for (const auto &salon : salons) {
        for (int i = 0; i < NUMBER_OF_HAIRDRESSERS_PER_SALON; i++) {
            hairdressers.emplace_back(new Hairdresser(salon, customers));
        }
    }

    City city(salons);
    Supplies supplies(*salons[0]);

    unique_ptr<Visualizer> visualizer =
            make_unique<Visualizer>(city, hairdressers);
    this_thread::sleep_for(chrono::seconds(WORKING_DAY_TIME));

    city.no_of_ready_salons = 0;
    no_of_ready_hairdressers = 0;

    this_thread::sleep_for(chrono::milliseconds(FIXED_VISUALIZER_TIME));

    customers.clear();

    return 0;
}
