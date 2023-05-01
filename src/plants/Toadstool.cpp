//
// Created by Hubert Kowalski on 27/04/2023.
//
#include "Toadstool.h"

Toadstool::Toadstool(Position position) : Plant(OrganismInitParams{0, 0, 10, 5, &position, "T"}) {}
