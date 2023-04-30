#include "src/World.h"

#include <iostream>

int main() {
    // Position
    Position p1;
    Position p2(1, 1);
    Position p3(-3, -5);

     std::cout << p1.toString() << std::endl;
     std::cout << p2.toString() << std::endl;
     std::cout << p3.toString() << std::endl;
     std::cout << p1.distance(p2) << std::endl;
     p2.move(4, 6);
     std::cout << p2.toString() << std::endl;

    // Plant & Animal
    auto grass = Organism::createOrganism('G', p2, nullptr);
    auto sheep = Organism::createOrganism('S', p3, nullptr);

    std::cout << grass->toString() << std::endl;
    std::cout << sheep->toString() << std::endl;

    grass->move(3, 4);
    std::cout << grass->toString() << std::endl;

    sheep->move(1, 2);
    std::cout << sheep->toString() << std::endl;

    delete grass;
    delete sheep;

    // World test
    World world(6, 6);
    Position posP1(4, 5);
    auto grassW1 = Organism::createOrganism('G', posP1, &world);
    Position posP2(5, 4);
    auto dandelionW2 = Organism::createOrganism('D', posP2, &world);

    Position posW2(3, 2);
    auto sheepW1 = Organism::createOrganism('S', posW2, &world);
    Position posW3(2, 3);
    auto sheepW2 = Organism::createOrganism('S', posW3, &world);

    world.addOrganism(grassW1);
    world.addOrganism(dandelionW2);
    world.addOrganism(sheepW1);
    world.addOrganism(sheepW2);

    auto positions = world.getVectorOfFreePositionsAround(Position(5, 5));

    for (auto position: positions)
        std::cout << position.toString() << std::endl;

    // Tura 0
    std::cout << world.toString() << std::endl;

    // Tura 1
    world.makeTurn();
    std::cout << world.toString() << std::endl;

    // Tura 2
    world.makeTurn();
    std::cout << world.toString() << std::endl;

    world.writeWorld("world.json");

    // Tura 3
    world.makeTurn();
    std::cout << world.toString() << std::endl;

    // powrot do Tury 2
    world.readWorld("world.json");
    std::cout << world.toString() << std::endl;

    return 0;
}
