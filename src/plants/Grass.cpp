//
// Created by Hubert Kowalski on 27/04/2023.
//
#include "Grass.h"

Grass::Grass(Position position) : Plant(OrganismInitParams{0, 0, 6, 3, &position, "G"}) {}
