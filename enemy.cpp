
#include "enemy.h"

extern void draw_char(char ch, int y, int x, COLORS foreground, COLORS background);

Enemy::Enemy():GameObject(), direction(0) {}
Enemy::Enemy(int x, int y, char symbol, COLORS color, int direction) : GameObject(x, y, symbol, color), direction(direction){}
Enemy::Enemy(const Enemy &other) : GameObject(other), direction(other.direction) {}
Enemy::Enemy(Enemy &&other) noexcept : GameObject(std::move(other)), direction(other.direction) {}

Enemy &Enemy::operator=(const Enemy &other) {
    if (this != &other) {
        GameObject::operator=(other);
        direction = other.direction;
    }

    return *this;
}

Enemy &Enemy::operator=(Enemy &&other) noexcept {
    if (this != &other) {
        GameObject::operator=(std::move(other));
        direction = other.direction;
    }

    return *this;
}

void Enemy::update() {
    setX(getX() + direction);

    if (getX() <= 0 || getX() >= 79) {
        direction = direction * (-1);
    }
}

void Enemy::render() {
    draw_char(getSymbol(), getY(), getX(), getColor(), BLACK);
}









