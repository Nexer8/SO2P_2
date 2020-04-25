//
// Created by mwisniewski on 4/25/20.
//

#include "../Headers/Supplies.h"

Supplies::Supplies(std::vector<std::shared_ptr<Scissors> > scissors) : scissors(scissors), life(&Supplies::supply, this) {}

void Supplies::supply() {
    std::this_thread::sleep_for(std::chrono::seconds(SUPPLY_WAITING_TIME));

    for (int i = 0; i < SCISSORS_SUPPLIES_AMOUNT; i++) {
        scissors.emplace_back(new Scissors());
    }
}

Supplies::~Supplies() {
    scissors.clear();
    life.join();
}


