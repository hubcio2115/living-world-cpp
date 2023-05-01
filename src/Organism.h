#pragma once

#include "utils/OrganismInitParams.h"
#include "Position.h"
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
    Organism *child;
    int turnOfBirth;
    std::vector<int> historyOfAncestors;

protected:
    explicit Organism(const OrganismInitParams &organism);

    explicit Organism(const Organism *organism);

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

    void setChild(Organism *newChild);

    [[nodiscard]] Organism *getChild() const;

    void setHistoryOfAncestors(std::vector<int> newHistory);

    [[nodiscard]] std::vector<int> getHistoryOfAncestors() const;

    void setSpecies(const std::string &spec);

    [[nodiscard]] virtual std::string toString();

    void setTurnOfBirth(int turn);

    [[nodiscard]] int getTurnOfBirth() const;

    virtual void moveTo(Position *position, int turn) = 0;

    virtual void die(int turn) = 0;

    Organism &operator=(const Organism *);

    [[nodiscard]] virtual bool isReproducible() const;

    [[nodiscard]] virtual json serialize() const;

    static Organism *deserialize(const json *organism);

    [[nodiscard]] static Organism *createOrganism(char species, Position position);
};
