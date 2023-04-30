#pragma once

#include "../Organism.h"

class Animal : public Organism {
protected:
    Animal(const OrganismInitParams &organism, Position position, World *world);

public:
    void move(int dx, int dy) override;
};
