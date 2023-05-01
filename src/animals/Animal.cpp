#include "Animal.h"

Animal::Animal(const OrganismInitParams &organism, const Position position, World *world) : Organism(organism, position,
                                                                                                     world) {}

void Animal::moveTo(Position *position) {
    this->setPosition(*position);
}
