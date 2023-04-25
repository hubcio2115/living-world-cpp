#include <iostream>
#include "src/Position.h"
#include "src/Plant.h"
#include "src/Animal.h"
#include "src/World.h"

int main() {
    // Position
    Position p1;
    Position p2(1, 1);
    Position p3(-3, -5);

    //std::cout << p1.toString() << std::endl;
    //std::cout << p2.toString() << std::endl;
    //std::cout << p3.toString() << std::endl;
    //std::cout << p1.distance(p2) << std::endl;
    //p2.move(4, 6);
    //std::cout << p2.toString() << std::endl;

    // Organism
    //Organism org1;
    //Organism org2( 10, p2 );

    //std::cout << org1.toString() << std::endl;
    //std::cout << org2.toString() << std::endl;
    //org1.move(2, 3);
    //std::cout << org1.toString() << std::endl;

    // Plant & Animal
    Plant plant(3, p3);
    Animal animal(5, p2);
    Plant plant2;
    Animal animal2;

    std::cout << plant.toString() << std::endl;
    std::cout << animal.toString() << std::endl;
    std::cout << plant2.toString() << std::endl;
    std::cout << animal2.toString() << std::endl;
    plant.move(3, 4);
    std::cout << plant.toString() << std::endl;
    animal.move(1, 2);
    std::cout << animal.toString() << std::endl;

    // World test
    World world;
    Position posP1(4, 5);
    Plant plantW1(3, posP1);
    Position posP2(5, 4);
    Plant plantW2(3, posP2);

    Position posW2(3, 2);
    Animal animalW1(6, posW2);
    Position posW3(2, 3);
    Animal animalW2(6, posW3);

    world.addOrganism(&plantW1);
    world.addOrganism(&plantW2);
    world.addOrganism(&animalW1);
    world.addOrganism(&animalW2);

    auto positions = world.getVectorOfFreePositionsAround(Position(5, 5));

    for (auto pos: positions)
        std::cout << pos.toString() << std::endl;

    // Tura 0
    std::cout << world.toString() << std::endl;

    // Tura 1
    world.makeTurn();
    std::cout << world.toString() << std::endl;

    // Tura 2
    world.makeTurn();
    std::cout << world.toString() << std::endl;

    world.writeWorld("world.bin");

    // Tura 3
    world.makeTurn();
    std::cout << world.toString() << std::endl;

    // powrot do Tury 2
    world.readWorld("world.bin");
    std::cout << world.toString() << std::endl;

    return 0;
}
