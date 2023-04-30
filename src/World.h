#pragma once

#include <vector>
#include <ctime>
#include "Organism.h"


class World {
private:
    int worldX;
    int worldY;
    int turn = 0;
    std::vector<Organism *> organisms;
    char separator = '.';

    std::string getOrganismFromPosition(int x, int y);

    [[nodiscard]] bool isPositionOnWorld(int x, int y) const;

    bool isPositionFree(Position position);

public:
    World(int worldX, int worldY);

    World() : World(6, 6) {};

    ~World();

    [[nodiscard]] int getWorldX() const;

    void setWorldX(int newWorldX);

    [[nodiscard]] int getWorldY() const;

    void setWorldY(int newWorldY);

    [[nodiscard]] int getTurn() const;

    void setTurn(int newTurn);

    void setOrganisms(std::vector<Organism *> newOrganisms);

    void addOrganism(Organism *organism);

    std::vector<Position> getVectorOfFreePositionsAround(Position position);

    void makeTurn();

    void writeWorld(const std::string &fileName);

    void readWorld(const std::string &fileName);

    std::string toString();
};
