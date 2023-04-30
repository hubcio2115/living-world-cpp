//
// Created by Hubert Kowalski on 27/04/2023.
//
#include "Sheep.h"

Sheep::Sheep(Position position, World *world) : Animal(OrganismInitParams{3, 3, 10, 6, "S"}, position, world) {}
