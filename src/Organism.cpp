#include "Organism.h"

#include <utility>

Organism::Organism(int newPower, Position newPosition) {
    setPower(newPower);
    setPosition(newPosition);
    setSpecies("O");
}

int Organism::getPower() const {
    return this->power;
}

void Organism::setPower(int newPower) {
    this->power = newPower;
}

Position Organism::getPosition() const {
    return this->position;
}

void Organism::setPosition(Position newPosition) {
    this->position = newPosition;
}

std::string Organism::toString() const {
    return "{ species: " + this->getSpecies() +
           ", power: " + std::to_string(getPower()) +
           ", position: " + getPosition().toString() + "}";
}

void Organism::move(int dx, int dy) {
    position.move(dx, dy);
}

std::string Organism::getSpecies() const {
    return this->species;
}

void Organism::setSpecies(std::string spec) {
    this->species = std::move(spec);
}
