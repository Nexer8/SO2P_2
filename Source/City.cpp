//
// Created by mwisniewski on 4/22/20.
//

#include "../Headers/City.h"

City::City(vector<shared_ptr<Salon> > &salons) : salons(salons) {
    no_of_ready_salons = salons.size();
}

City::~City() {
    salons.clear();
}
