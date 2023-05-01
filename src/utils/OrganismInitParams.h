#include "../Position.h"

struct OrganismInitParams {
    int power;
    int initiative;
    int liveLength;
    int powerToReproduce;
    Position *position;
    std::string species;
};
