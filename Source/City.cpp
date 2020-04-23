//
// Created by mwisniewski on 4/22/20.
//

#include "../Headers/City.h"

City::City() {
    for (int i = 0; i < NUMBER_OF_SALONS; i++) {
        salons.emplace_back(new Salon("Salon " + to_string(i)));
        no_of_ready_salons++;
    }
}

City::~City() {
    salons.clear();
}
