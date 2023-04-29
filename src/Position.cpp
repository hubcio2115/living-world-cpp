#include "Position.h"
#include <math.h>

Position::Position(int x, int y) {
    setX(x);
    setY(y);
}

int Position::getX() const { return this->x; }

void Position::setX(int newX) {
    if (x >= 0)
        this->x = newX;
    else
        this->x = 0;
}

int Position::getY() const { return this->y; }

void Position::setY(int newY) {
    if (y >= 0)
        this->y = newY;
    else
        this->y = 0;
}

std::string Position::toString() const {
    return "(" + std::to_string(getX()) + ", " + std::to_string(getY()) + ")";
}

double Position::distance(Position position) const {
    double dx = (double) this->getX() - (double) position.getX();
    double dy = (double) this->getY() - (double) position.getY();
    return sqrt((dx * dx) + (dy * dy));
}

void Position::move(int dx, int dy) {
    setX(getX() + dx);
    setY(getY() + dy);
}
