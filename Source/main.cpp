#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include "../Headers/Parameters.h"
#include "../Headers/Hairdresser.h"
#include "../Headers/Salon.h"
#include "../Headers/Visualizer.h"
#include "../Headers/City.h"

using namespace std;

int main() {
    vector<shared_ptr<Hairdresser> > hairdressers;

    City city;

    for (const auto& salon: city.salons) {
        for (int i = 0; i < NUMBER_OF_HAIRDRESSERS_PER_SALON; i++) {
            if (i != NUMBER_OF_HAIRDRESSERS_PER_SALON - 1) {
                hairdressers.emplace_back(
                        new Hairdresser(*salon, *salon->scissors[i], *salon->scissors[i + 1], salon->customers));
            } else {
                hairdressers.emplace_back(new Hairdresser(*salon, *salon->scissors[i], *salon->scissors[0], salon->customers));
            }
        }
    }

    Visualizer *visualizer = new Visualizer(city, hairdressers);
    this_thread::sleep_for(chrono::seconds(WORKING_DAY_TIME));
    for (const auto& salon: city.salons) {
        salon->no_of_ready_customers = 0;
        salon->no_of_ready_hairdressers = 0;
    }
    city.no_of_ready_salons = 0;

    delete visualizer;
    hairdressers.clear();

    return 0;
}
