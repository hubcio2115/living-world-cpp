#include "Animal.h"

Animal::Animal(const OrganismInitParams &organism) : Organism(organism) {}

void Animal::moveTo(Position *position, int turn) {
    this->setLiveLength(this->getLiveLength() - 1);

    if (this->getLiveLength() != 0)
        this->setPosition(*position);
    else this->die(turn);
}

void Animal::die(int turn) {
    if (this->getChild() != nullptr) {
        auto history = this->getChild()->getHistoryOfAncestors();
        history.push_back(turn);
        this->getChild()->setHistoryOfAncestors(history);
    }
}
