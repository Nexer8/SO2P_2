#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include "../Headers/Parameters.h"
#include "../Headers/Hairdresser.h"
#include "../Headers/Salon.h"
#include "../Headers/Visualizer.h"
#include "../Headers/City.h"
#include "../Headers/Supplies.h"

using namespace std;

/* TODO: Create a class Supplies that would be a separate thread and would wait to supply one of the
 * salons with new scissors. Scissors, therefore, could be accessed per salon, no matter where they are.
 * That would require changes in the Hairdresser implementation. There will be no scissors passed in the constructor,
 * as they already exist in the Salon class. It'll be necessary to implement a wait_for_scissors() function.
 */

int main() {
    vector<shared_ptr<Hairdresser> > hairdressers;
    vector<shared_ptr<Customer> > customers;
    vector<shared_ptr<Salon> > salons;

    for (int i = 0; i < NUMBER_OF_CLIENTS; i++) {
        customers.emplace_back(new Customer());
    }

    for (int i = 0; i < NUMBER_OF_SALONS; i++) {
        salons.emplace_back(new Salon("Salon " + to_string(i)));
    }

    for (const auto &salon: salons) {
        for (int i = 0; i < NUMBER_OF_HAIRDRESSERS_PER_SALON; i++) {
            if (i != NUMBER_OF_HAIRDRESSERS_PER_SALON - 1) {
                hairdressers.emplace_back(
                        new Hairdresser(salon, customers));
            } else {
                hairdressers.emplace_back(
                        new Hairdresser(salon, customers));
            }
        }
    }

    City city(salons);
    Supplies supplies(salons[0]->scissors);

    Visualizer *visualizer = new Visualizer(city, hairdressers);
    this_thread::sleep_for(chrono::seconds(WORKING_DAY_TIME));

    city.no_of_ready_salons = 0;
    for (const auto &salon: city.salons) {
        salon->no_of_ready_hairdressers = 0;
    }
    this_thread::sleep_for(chrono::milliseconds(FIXED_VISUALIZER_TIME));

    delete visualizer;
    hairdressers.clear();
    customers.clear();
    salons.clear();

    return 0;
}
