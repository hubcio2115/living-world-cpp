#pragma once

#include "../Organism.h"

class Plant : public Organism {
protected:
    Plant(const OrganismInitParams &organism, Position position, World *world);

public:
    void move(int dx, int dy) override;
};
