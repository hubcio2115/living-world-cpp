#include "World.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <random>
#include <utility>

using json = nlohmann::json;
namespace sv = std::views;

std::string World::getOrganismFromPosition(int x, int y) {
    for (auto organism: this->organisms)
        if (organism->getPosition().getX() == x && organism->getPosition().getY() == y)
            return organism->getSpecies();
    return "";
}

bool World::isPositionOnWorld(int x, int y) const {
    return x >= 0 && y >= 0 && x < this->getWorldX() && y < this->getWorldY();
}

bool World::isPositionFree(Position position) {
    return this->getOrganismFromPosition(position.getX(), position.getY())
            .empty();
}

std::vector<Position> World::getVectorOfFreePositionsAround(Position position) {
    int pos_x = position.getX(), pos_y = position.getY();
    std::vector<Position> result;
    for (int x: sv::iota(-1, 2))
        for (int y: sv::iota(-1, 2))
            if ((x != 0 || y != 0) && this->isPositionOnWorld(pos_x + x, pos_y + y))
                result.emplace_back(pos_x + x, pos_y + y);

    auto iter = std::remove_if(result.begin(), result.end(),
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
    std::uniform_int_distribution<int> dist(8);

    for (int i: sv::iota(0, (int) this->organisms.size())) {
        auto organism = this->organisms[i];
        auto currentPosition = organism->getPosition();
        newPositions = getVectorOfFreePositionsAround(currentPosition);

        numberOfNewPositions = (int) newPositions.size();
        if (numberOfNewPositions > 0) {
            bool wasMoveMade = false;
            randomIndex = dist(rng) % numberOfNewPositions;
            Position newPosition = newPositions[randomIndex];

            organism->moveTo(&newPosition, this->getTurn());
        }

        if (organism->getLiveLength() == 0) {
            auto pointerToErase = this->organisms.begin() + i;
            this->organisms.erase(pointerToErase);
            delete organism;
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

        for (auto organism: this->organisms)
            data["organisms"].push_back(organism->serialize());


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
            Organism *newOrganism = Organism::deserialize(&organism);
            this->addOrganism(newOrganism);
        }
        my_json.close();
    }
}

std::string World::toString() {
    std::string result = "\nturn: " + std::to_string(getTurn()) + "\n";
    std::string spec;

    for (int wY: sv::iota(0, this->getWorldY())) {
        for (int wX: sv::iota(0, this->getWorldX())) {
            spec = getOrganismFromPosition(wX, wY);
            !spec.empty() ?
                    result += spec :
                    result += this->separator;
        }
        result += "\n";
    }
    return result;
}
