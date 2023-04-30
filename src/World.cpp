#include "World.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <random>
#include <utility>

using json = nlohmann::json;

std::string World::getOrganismFromPosition(int x, int y) {
    for (auto org: this->organisms)
        if (org->getPosition().getX() == x && org->getPosition().getY() == y)
            return org->getSpecies();
    return "";
}

bool World::isPositionOnWorld(int x, int y) const {
    return (x >= 0 && y >= 0 && x < getWorldX() && y < getWorldY());
}

bool World::isPositionFree(Position position) {
    return this->getOrganismFromPosition(position.getX(), position.getY())
            .empty();
}

std::vector<Position> World::getVectorOfFreePositionsAround(Position position) {
    int pos_x = position.getX(), pos_y = position.getY();
    std::vector<Position> result;
    for (int x = -1; x < 2; ++x)
        for (int y = -1; y < 2; ++y)
            if ((x != 0 || y != 0) && this->isPositionOnWorld(pos_x + x, pos_y + y))
                result.emplace_back(pos_x + x, pos_y + y);

    auto iter = remove_if(result.begin(), result.end(),
                          [this](Position pos) { return !isPositionFree(pos); });
    result.erase(iter, result.end());

    return result;
}

World::World(const int worldX, const int worldY) {
    this->setWorldX(worldX);
    this->setWorldY(worldY);
}

World::~World() {
    for (auto organism: this->organisms)
        delete organism;
}

int World::getWorldX() const { return this->worldX; }

void World::setWorldX(const int newWorldX) { this->worldX = newWorldX; }

int World::getWorldY() const { return this->worldY; }

void World::setWorldY(const int newWorldY) { this->worldY = newWorldY; }

int World::getTurn() const { return this->turn; }

void World::setTurn(int newTurn) { this->turn = newTurn; }

void World::setOrganisms(std::vector<Organism *> newOrganisms) {
    for (auto organism: this->organisms) delete organism;

    this->organisms = std::move(newOrganisms);
}

void World::addOrganism(Organism *organism) {
    this->organisms.push_back(organism);
}

void World::makeTurn() {
    std::vector<Position> newPositions;
    int numberOfNewPositions;
    int randomIndex;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(100);

    for (auto org: this->organisms) {
        newPositions = getVectorOfFreePositionsAround(org->getPosition());
        numberOfNewPositions = (int) newPositions.size();
        if (numberOfNewPositions > 0) {
            randomIndex = dist(rng) % numberOfNewPositions;
            org->setPosition(newPositions[randomIndex]);
        }
    }
    this->turn++;
}

void World::writeWorld(const std::string &fileName) {
    std::ofstream my_json(fileName);
    if (my_json.is_open()) {
        json data = {{"worldX",    this->getWorldX()},
                     {"worldY",    this->getWorldY()},
                     {"turn",      this->getTurn()},
                     {"organisms", json::array()}};

        for (auto organism: this->organisms) data["organisms"].push_back(organism->serialize());

        my_json << data.dump(4) << std::endl;
        my_json.close();
    }
}

void World::readWorld(const std::string &fileName) {
    std::ifstream my_json(fileName);

    if (my_json.is_open()) {
        json data;
        my_json >> data;
        this->setWorldX(data.at("worldX"));
        this->setWorldY(data.at("worldY"));
        this->setTurn(data.at("turn"));
        this->setOrganisms(std::vector<Organism *>());

        for (const auto &organism: data.at("organisms")) {
            Organism *newOrganism = Organism::deserialize(&organism, this);
            this->addOrganism(newOrganism);
        }
        my_json.close();
    }
}

std::string World::toString() {
    std::string result = "\nturn: " + std::to_string(getTurn()) + "\n";
    std::string spec;

    for (int wY = 0; wY < getWorldY(); ++wY) {
        for (int wX = 0; wX < getWorldX(); ++wX) {
            spec = getOrganismFromPosition(wX, wY);
            if (!spec.empty())
                result += spec;
            else
                result += this->separator;
        }
        result += "\n";
    }
    return result;
}
