//
// Created by Hubert Kowalski on 27/04/2023.
//
#include "Wolf.h"

Wolf::Wolf(Position position) : Animal(OrganismInitParams{6, 5, 15, 12, &position, "W"}) {}
