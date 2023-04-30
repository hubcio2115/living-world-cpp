#include "Animal.h"

Animal::Animal(const OrganismInitParams &organism, const Position position, World *world) : Organism(organism, position,
                                                                                                     world) {}

void Animal::move(const int dx, const int dy) {
    auto newPosition = this->getPosition();
    newPosition.move(dx, dy);

    this->setPosition(newPosition);
}
