#include "World.h"
#include <fstream>
#include <random>

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
    return this->getOrganismFromPosition(position.getX(), position.getY()).empty();
}

std::vector<Position> World::getVectorOfFreePositionsAround(Position position) {
    int pos_x = position.getX(), pos_y = position.getY();
    std::vector<Position> result;
    for (int x = -1; x < 2; ++x)
        for (int y = -1; y < 2; ++y)
            if ((x != 0 || y != 0) &&
                this->isPositionOnWorld(pos_x + x, pos_y + y))
                result.emplace_back(pos_x + x, pos_y + y);

    auto iter = remove_if(result.begin(), result.end(),
                          [this](Position pos) { return !isPositionFree(pos); });
    result.erase(iter, result.end());

    return result;
}

World::World(int newWorldX, int newWorldY) {
    setWorldX(newWorldX);
    setWorldY(newWorldY);
}

World::~World() {
    for (auto organism: this->organisms)
        delete organism;
}

int World::getWorldX() const {
    return this->worldX;
}

void World::setWorldX(int newWorldX) {
    this->worldX = newWorldX;
}

int World::getWorldY() const {
    return this->worldY;
}

void World::setWorldY(int newWorldY) {
    this->worldY = newWorldY;
}

int World::getTurn() const {
    return this->turn;
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
    std::fstream my_file;
    my_file.open(fileName, std::ios::out | std::ios::binary);
    if (my_file.is_open()) {
        my_file.write((char *) &this->worldX, sizeof(int));
        my_file.write((char *) &this->worldY, sizeof(int));
        my_file.write((char *) &this->turn, sizeof(int));

        int organisms_size = (int) this->organisms.size();
        my_file.write((char *) &organisms_size, sizeof(int));
        for (int i = 0; i < organisms_size; i++) {
            int data;
            data = this->organisms[i]->getPower();
            my_file.write((char *) &data, sizeof(int));

            data = this->organisms[i]->getPosition().getX();
            my_file.write((char *) &data, sizeof(int));

            data = this->organisms[i]->getPosition().getY();
            my_file.write((char *) &data, sizeof(int));

            std::string s_data = this->organisms[i]->getSpecies();
            int s_size = (int) s_data.size();

            my_file.write((char *) &s_size, sizeof(int));
            my_file.write(s_data.data(), (int) s_data.size());
        }

        my_file.close();
    }
}

void World::readWorld(const std::string &fileName) {
    std::fstream my_file;
    my_file.open(fileName, std::ios::in | std::ios::binary);

    if (my_file.is_open()) {
        int result;
        my_file.read((char *) &result, sizeof(int));
        this->worldX = (int) result;

        my_file.read((char *) &result, sizeof(int));
        this->worldY = (int) result;

        my_file.read((char *) &result, sizeof(int));
        this->turn = (int) result;

        my_file.read((char *) &result, sizeof(int));
        int organisms_size = (int) result;

        std::vector<Organism *> new_organisms;
        for (int i = 0; i < organisms_size; i++) {
            int power;
            my_file.read((char *) &result, sizeof(int));
            power = (int) result;

            int pos_x;
            my_file.read((char *) &result, sizeof(int));
            pos_x = (int) result;

            int pos_y;
            my_file.read((char *) &result, sizeof(int));
            pos_y = (int) result;

            Position pos(pos_x, pos_y);

            int s_size;
            my_file.read((char *) &result, sizeof(int));
            s_size = (int) result;

            std::string species;
            species.resize(s_size);
            my_file.read((char *) &species[0], s_size);

            auto organism = new Organism(power, pos);
            organism->setSpecies(species);
            new_organisms.push_back(organism);
        }
        this->organisms = new_organisms;
        my_file.close();
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
