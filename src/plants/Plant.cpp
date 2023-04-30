#include "Plant.h"

Plant::Plant(const OrganismInitParams &organism, const Position position, World *world) : Organism(organism, position,
                                                                                                   world) {}

void Plant::move(const int dx, const int dy) {}
