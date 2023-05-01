#include "Animal.h"

Animal::Animal(const OrganismInitParams &organism) : Organism(organism) {}

void Animal::moveTo(Position *position) {
    this->setPosition(*position);
}
