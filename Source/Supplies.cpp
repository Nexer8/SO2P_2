//
// Created by mwisniewski on 4/25/20.
//

#include "../Headers/Supplies.h"

Supplies::Supplies(Salon &salon) : salon(salon),
                                   life(&Supplies::supply, this) {}

void Supplies::supply() {
    this_thread::sleep_for(std::chrono::seconds(SUPPLY_WAITING_TIME));
    for (int i = 0; i < SCISSORS_SUPPLIES_AMOUNT; i++) {
        salon.scissors.emplace_back(new Scissors());
        salon.no_of_available_scissors++;
    }
}

Supplies::~Supplies() {
    life.join();
}
