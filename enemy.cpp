
#include "enemy.h"

extern void draw_char(char ch, int y, int x, COLORS foreground, COLORS background);

Enemy::Enemy():GameObject(0,0,' ',BLACK), direction(1), points(10) {}
Enemy::Enemy(int x, int y, char symbol, COLORS color, int points) : GameObject(x, y, symbol, color), points(points) {
    direction = 1;
}
Enemy::Enemy(const Enemy &other) : GameObject(other), direction(other.direction), points(other.points) {}
Enemy::Enemy(Enemy &&other) noexcept : GameObject(std::move(other)), direction(other.direction), points(other.points) {}

Enemy &Enemy::operator=(const Enemy &other) {
    if (this != &other) {
        GameObject::operator=(other);
        direction = other.direction;
        points = other.points;
    }

    return *this;
}

Enemy &Enemy::operator=(Enemy &&other) noexcept {
    if (this != &other) {
        GameObject::operator=(std::move(other));
        direction = other.direction;
        points = other.points;
    }

    return *this;
}

void Enemy::update() {
    setX(getX() + direction);

    if (getX() <= 0 || getX() >= 79) {
        direction = direction * (-1);
        // setY(getY() + 1); //dvijenie nadolu
    }
}

int Enemy::getPoints() const {
    return points;
}

int Enemy::getDirection() const {
    return direction;
}

void Enemy::setDirection(int direction) {
    this->direction = direction;
}

void Enemy::render() {
    draw_char(getSymbol(), getY(), getX(), getColor(), BLACK);
}
