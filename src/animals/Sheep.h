//
// Created by Hubert Kowalski on 25/04/2023.
//

#ifndef INC_01_LIVING_WORLD_HUBCIO2115_SHEEP_H
#define INC_01_LIVING_WORLD_HUBCIO2115_SHEEP_H

#include "Animal.h"

class Sheep : public Animal {
public:
    explicit Sheep(Position position, World* world);
};

#endif // INC_01_LIVING_WORLD_HUBCIO2115_SHEEP_H
