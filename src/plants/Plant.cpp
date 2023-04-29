#include "Plant.h"

Plant::Plant(const OrganismInitParams &organism, const Position position) : Organism(organism, position) {}

void Plant::move(const int dx, const int dy) {
    Organism::move(0, 0);
}
