#include "src/World.h"

#include <iostream>

namespace sv = std::views;

int main() {
    // Position
    Position p1;
    Position p2(1, 1);
    Position p3(-3, -5);

//     std::cout << p1.toString() << std::endl;
//     std::cout << p2.toString() << std::endl;
//     std::cout << p3.toString() << std::endl;
//     std::cout << p1.distance(p2) << std::endl;
//     p2.move(4, 6);
//     std::cout << p2.toString() << std::endl;

    // Plant & Animal
    auto grass = Organism::createOrganism('G', p2);
    auto sheep = Organism::createOrganism('S', p3);

    std::cout << grass->toString() << std::endl;
    std::cout << sheep->toString() << std::endl;

    grass->moveTo(new Position(1, 2), 0);
    std::cout << grass->toString() << std::endl;

    sheep->moveTo(new Position(1, 2), 0);
    std::cout << sheep->toString() << std::endl;

    delete grass;
    delete sheep;

    // World test
    World world(6, 6);
    Position pos1(4, 5);
    auto grass1 = Organism::createOrganism('G', pos1);
    Position pos2(5, 4);
    auto dandelion2 = Organism::createOrganism('D', pos2);

    Position pos3(3, 2);
    auto sheep1 = Organism::createOrganism('S', pos3);
    Position pos4(2, 3);
    auto sheep2 = Organism::createOrganism('S', pos4);

    sheep1->setLiveLength(6);
    sheep1->setChild(sheep2);

    world.addOrganism(grass1);
    world.addOrganism(dandelion2);
    world.addOrganism(sheep1);
    world.addOrganism(sheep2);

    auto positions = world.getVectorOfFreePositionsAround(Position(5, 5));

    for (auto position: positions)
        std::cout << position.toString() << std::endl;

    // Tura 0
    std::cout << world.toString() << std::endl;

    for (int i: sv::iota(0, 10)) {
        world.makeTurn();
        std::cout << world.toString() << std::endl;

        if (i == 4) world.writeWorld("world.json");
    }

    // powrót do Tury 5
    world.readWorld("world.json");
    std::cout << world.toString() << std::endl;

    return 0;
}
