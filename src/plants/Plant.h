#pragma once

#include "../Organism.h"

class Plant : public Organism {
protected:
    Plant(const OrganismInitParams &organism);

public:
    void moveTo(Position *position, int turn) override;

    void die(int turn) override;
};
