#pragma once

#include "../Organism.h"

class Animal : public Organism {
protected:
    Animal(const OrganismInitParams &organism);

public:
    void moveTo(Position *position, int turn) override;

    void die(int turn) override;
};
