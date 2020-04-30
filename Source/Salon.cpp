//
// Created by mwisniewski on 4/2/20.
//

#include "../Headers/Salon.h"

Salon::Salon(string name) : name(name), id(current_salon_id++) {
    for (int i = 0; i < NUMBER_OF_SCISSORS_PER_SALON; i++) {
        scissors.emplace_back(new Scissors());
    }
}

Salon::~Salon() {
    scissors.clear();
}
