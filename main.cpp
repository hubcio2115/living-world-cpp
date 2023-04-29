#include "src/Position.h"
#include "src/World.h"

#include "src/animals/Sheep.h"

#include "src/plants/Grass.h"
#include "src/plants/Dandelion.h"

#include <iostream>

int main() {
    // Position
    // Position p1;
    Position p2(1, 1);
    Position p3(-3, -5);

    // std::cout << p1.toString() << std::endl;
    // std::cout << p2.toString() << std::endl;
    // std::cout << p3.toString() << std::endl;
    // std::cout << p1.distance(p2) << std::endl;
    // p2.move(4, 6);
    // std::cout << p2.toString() << std::endl;

    // Organism
    // Organism org1;
    // Organism org2( 10, p2 );

    // std::cout << org1.toString() << std::endl;
    // std::cout << org2.toString() << std::endl;
    // org1.move(2, 3);
    // std::cout << org1.toString() << std::endl;

    // Plant & Animal
    Grass grass(p3);
    Sheep sheep(p2);

    std::cout << grass.toString() << std::endl;
    std::cout << sheep.toString() << std::endl;

    grass.move(3, 4);
    std::cout << grass.toString() << std::endl;

    sheep.move(1, 2);
    std::cout << sheep.toString() << std::endl;

    // World test
    World world(6, 6);
    Position posP1(4, 5);
    Grass grassW1(posP1);
    Position posP2(5, 4);
    Dandelion dandelionW2(posP2);

    Position posW2(3, 2);
    Sheep sheepW1(posW2);
    Position posW3(2, 3);
    Sheep sheepW2(posW3);

    world.addOrganism(&grassW1);
    world.addOrganism(&grassW1);
    world.addOrganism(&sheepW2);
    world.addOrganism(&sheepW2);

    std::vector<Position> positions = world.getVectorOfFreePositionsAround(Position(5, 5));

    for (Position pos: positions)
        std::cout << pos.toString() << std::endl;

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
//    world.readWorld("world.bin");
//    std::cout << world.toString() << std::endl;

    return 0;
}
