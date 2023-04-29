#pragma once

#include "utils/OrganismInitParams.h"
#include "Position.h"
#include "World.h"
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class Organism {
private:
    int power;
    int initiative;
    Position position;
    int liveLength;
    int powerToReproduce;
    std::string species;
    World *world;

protected:
    Organism(const OrganismInitParams &organism, Position position, World *world);

    explicit Organism(Organism *organism);

public:
    virtual ~Organism() = default;

    [[nodiscard]] int getPower() const;

    void setPower(int newPower);

    [[nodiscard]] int getInitiative() const;

    void setInitiative(int newInitiative);

    [[nodiscard]] Position getPosition() const;

    void setPosition(Position newPosition);

    [[nodiscard]] int getLiveLength() const;

    void setLiveLength(int newLiveLength);

    [[nodiscard]] int getPowerToReproduce() const;

    void setPowerToReproduce(int newPowerToReproduce);

    [[nodiscard]] std::string getSpecies() const;

    void setSpecies(const std::string &spec);

    void setWorld(World *world);

    [[nodiscard]] virtual std::string toString() const;

    virtual void move(int dx, int dy);

    Organism &operator=(const Organism *);

    [[nodiscard]] virtual bool isReproducible() const;

    [[nodiscard]] virtual json serialize() const;

    static Organism *deserialize(const json *organism, World *world);

    [[nodiscard]] static Organism *createOrganism(char species, Position position);
};
