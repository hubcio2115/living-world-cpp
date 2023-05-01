#include "../Position.h"

class Organism;

struct OrganismInitParams {
    int power;
    int initiative;
    int liveLength;
    int powerToReproduce;
    Position *position;
    std::string species;
    int turnOfBirth;
    Organism* child;
};
