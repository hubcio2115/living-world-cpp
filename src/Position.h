#pragma once

#include <string>

class Position {
private:
    int x;
    int y;

public:
    Position(int x, int y);

    Position() : x(0), y(0) {}

    [[nodiscard]] int getX() const;

    void setX(int x);

    [[nodiscard]] int getY() const;

    void setY(int y);

    [[nodiscard]] std::string toString() const;

    [[nodiscard]] double distance(Position position) const;

    void move(int dx, int dy);
};
