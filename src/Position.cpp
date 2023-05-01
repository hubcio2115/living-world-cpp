#include "Position.h"
#include <cmath>

Position::Position(int x, int y) {
    setX(x);
    setY(y);
}

int Position::getX() const { return this->x; }

void Position::setX(int newX) {
    newX >= 0 ?
            this->x = newX :
            this->x = 0;
}

int Position::getY() const { return this->y; }

void Position::setY(int newY) {
    newY >= 0 ?
            this->y = newY :
            this->y = 0;
}

std::string Position::toString() const {
    return "(" + std::to_string(this->getX()) + ", " + std::to_string(this->getY()) + ")";
}

double Position::distance(Position position) const {
    double dx = (double) this->getX() - (double) position.getX();
    double dy = (double) this->getY() - (double) position.getY();
    return sqrt((dx * dx) + (dy * dy));
}

void Position::move(int dx, int dy) {
    this->setX(this->getX() + dx);
    this->setY(this->getY() + dy);
}
