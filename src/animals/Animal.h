#pragma once

#include "../Organism.h"

class Animal : public Organism {
protected:
    Animal(const OrganismInitParams &organism, Position position, World *world);

public:
    void moveTo(Position *position) override;
};
