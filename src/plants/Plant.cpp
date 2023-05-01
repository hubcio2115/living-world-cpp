#include "Plant.h"

Plant::Plant(const OrganismInitParams &organism) : Organism(organism) {}

void Plant::moveTo(Position *position, int turn) {
    this->setLiveLength(this->getLiveLength() - 1);

    if (this->getLiveLength() == 0) this->die(turn);
}

void Plant::die(int turn) {
    if (this->getChild() != nullptr) {
        auto history = this->getChild()->getHistoryOfAncestors();
        history.push_back(turn);
        this->getChild()->setHistoryOfAncestors(history);
    }
}
