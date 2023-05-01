#include "Organism.h"
#include "./animals/Wolf.h"
#include "./animals/Sheep.h"
#include "plants/Grass.h"
#include "plants/Dandelion.h"
#include "plants/Toadstool.h"
#include <iostream>

Organism::Organism(const OrganismInitParams &organism) {
    this->setPower(organism.power);
    this->setInitiative(organism.initiative);
    this->setPosition(*organism.position);
    this->setLiveLength(organism.liveLength);
    this->setPowerToReproduce(organism.powerToReproduce);
    this->setSpecies(organism.species);
    this->setTurnOfBirth(organism.turnOfBirth);
    this->child = organism.child;
}

Organism::Organism(const Organism *organism) {
    this->setPower(organism->getPower());
    this->setInitiative(organism->getInitiative());
    this->setPosition(organism->getPosition());
    this->setLiveLength(organism->getLiveLength());
    this->setPowerToReproduce(organism->getPowerToReproduce());
    this->setSpecies(organism->getSpecies());
    this->setHistoryOfAncestors(organism->getHistoryOfAncestors());
    this->setTurnOfBirth(organism->getTurnOfBirth());
    this->child = organism->child;
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

void Organism::setChild(Organism *newChild) {
    auto history = newChild->getHistoryOfAncestors();
    history.push_back(this->getTurnOfBirth());
    newChild->setHistoryOfAncestors(history);

    this->child = newChild;
}

Organism *Organism::getChild() const {
    return this->child;
}

void Organism::setHistoryOfAncestors(std::vector<int> newHistory) {
    this->historyOfAncestors = std::move(newHistory);
}

std::vector<int> Organism::getHistoryOfAncestors() const {
    return this->historyOfAncestors;
}

void Organism::setTurnOfBirth(int turn) {
    this->turnOfBirth = turn;
}

int Organism::getTurnOfBirth() const {
    return this->turnOfBirth;
}

std::string Organism::toString() {
    return to_string(this->serialize());
}

Organism &Organism::operator=(const Organism *) { return *this; }

bool Organism::isReproducible() const {
    return this->power >= this->powerToReproduce;
}

json Organism::serialize() const {
    return json{
            {"power",            this->getPower()},
            {"initiative",       this->getInitiative()},
            {"liveLength",       this->getLiveLength()},
            {"powerToReproduce", this->getPowerToReproduce()},
            {"species",          this->getSpecies()},
            {"historyOfAncestors", this->getHistoryOfAncestors()},
            {"child",            this->getChild() != nullptr ? this->getChild()->serialize() : nullptr},
            {"turnOfBirth", this->getTurnOfBirth()},
            {"position",         {
                                         {"posX", this->getPosition().getX()},
                                         {"posY", this->getPosition().getY()},
                                 }},
    };
}

Organism *Organism::deserialize(const json *organism) {
    std::string species = organism->at("species");
    const char *cstr = species.c_str();
    char buffer[2];
    std::strcpy(buffer, cstr);

    Position position(organism->at("position").at("posX"), organism->at("position").at("posY"));
    Organism *newOrganism = Organism::createOrganism(buffer[0], position);

    newOrganism->setPower(organism->at("power"));
    newOrganism->setInitiative(organism->at("initiative"));
    newOrganism->setLiveLength(organism->at("liveLength"));
    newOrganism->setPowerToReproduce(organism->at("powerToReproduce"));
    newOrganism->setHistoryOfAncestors(organism->at("historyOfAncestors"));
    newOrganism->setTurnOfBirth(organism->at("turnOfBirth"));

    if (organism->at("child") != nullptr) {
        Organism *child = Organism::deserialize(&organism->at("child"));
        newOrganism->setChild(child);
    }

    return newOrganism;
}

Organism *Organism::createOrganism(const char species, Position position) {
    Organism *newOrganism;
    switch (species) {
        case 'W':
            newOrganism = new Wolf(position);
            break;
        case 'S':
            newOrganism = new Sheep(position);
            break;
        case 'G':
            newOrganism = new Grass(position);
            break;
        case 'T':
            newOrganism = new Toadstool(position);
            break;
        case 'D':
            newOrganism = new Dandelion(position);
            break;
        default:
            throw std::runtime_error("No animal ha provided species signature!");
    }

    return newOrganism;
}