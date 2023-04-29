#include "Organism.h"

Organism::Organism(const OrganismInitParams &organism, Position position, World *world) {
    this->setPower(organism.power);
    this->setInitiative(organism.initiative);
    this->setPosition(position);
    this->setLiveLength(organism.liveLength);
    this->setPowerToReproduce(organism.powerToReproduce);
    this->setSpecies(organism.species);
    this->setWorld(world);
}

Organism::Organism(Organism *organism) {
    this->setPower(organism->getPower());
    this->setInitiative(organism->getInitiative());
    this->setPosition(organism->getPosition());
    this->setLiveLength(organism->getLiveLength());
    this->setPowerToReproduce(organism->getPowerToReproduce());
    this->setSpecies(organism->getSpecies());
    this->setWorld(organism->world);
}

int Organism::getPower() const { return this->power; }

void Organism::setPower(const int newPower) { this->power = newPower; }

int Organism::getInitiative() const { return this->initiative; }

void Organism::setInitiative(const int newInitiative) {
    this->initiative = newInitiative;
}

Position Organism::getPosition() const { return this->position; }

void Organism::setPosition(const Position newPosition) {
    this->position = newPosition;
}

int Organism::getLiveLength() const { return this->liveLength; }

void Organism::setLiveLength(const int newLiveLength) {
    this->liveLength = newLiveLength;
}

int Organism::getPowerToReproduce() const { return this->powerToReproduce; }

void Organism::setPowerToReproduce(const int newPowerToReproduce) {
    this->powerToReproduce = newPowerToReproduce;
}

std::string Organism::getSpecies() const { return this->species; }

void Organism::setSpecies(const std::string &spec) { this->species = spec; }

void Organism::setWorld(World *newWorld) {
    this->world = newWorld;
}

std::string Organism::toString() const {
    return "{ species: " + this->getSpecies() +
           ", power: " + std::to_string(getPower()) +
           ", position: " + getPosition().toString() + "}";
}

void Organism::move(const int dx, const int dy) { this->getPosition().move(dx, dy); }

Organism &Organism::operator=(const Organism *) { return *this; }

bool Organism::isReproducible() const {
    return this->power >= this->powerToReproduce;
}

std::string Organism::getSpecies() const {
    return this->species;
}

void Organism::setSpecies(std::string spec) {
    this->species = std::move(spec);
}
