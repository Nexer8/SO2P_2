#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include "../Headers/Parameters.h"
#include "../Headers/Hairdresser.h"
#include "../Headers/Salon.h"
#include "../Headers/Visualizer.h"

using namespace std;

int main() {
    Salon salon;
    vector < shared_ptr<Hairdresser> > hairdressers;

    for (int i = 0; i < NUMBER_OF_HAIRDRESSERS; i++) {
        if (i != NUMBER_OF_HAIRDRESSERS - 1) {
            hairdressers.emplace_back(new Hairdresser(salon, *salon.scissors[i], *salon.scissors[i+1], salon.customers));
        }
        else {
            hairdressers.emplace_back(new Hairdresser(salon, *salon.scissors[i], *salon.scissors[0], salon.customers));
        }
    }

    Visualizer *visualizer = new Visualizer(hairdressers, salon);
    this_thread::sleep_for(chrono::seconds(WORKING_DAY_TIME));
    salon.no_of_ready_customers = 0;

    delete visualizer;
    hairdressers.clear();

    return 0;
}
