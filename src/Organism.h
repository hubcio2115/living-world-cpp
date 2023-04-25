#pragma once

#include <string>
#include "Position.h"

class Organism {
private:
    int power;
    Position position;
    std::string species;
public:
    Organism(int power, Position position);

    Organism() : power(0), position(0, 0), species("O") {};

    [[nodiscard]] int getPower() const;

    void setPower(int newPower);

    [[nodiscard]] Position getPosition() const;

    void setPosition(Position newPosition);

    [[nodiscard]] std::string getSpecies() const;

    void setSpecies(std::string spec);

    [[nodiscard]] std::string toString() const;

    void move(int dx, int dy);
};
