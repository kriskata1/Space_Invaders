#include "bullet.h"

#include "player.h"

extern void draw_char(char ch, double y, double x, COLORS foreground, COLORS background);

Bullet::Bullet():GameObject(0,0,' ',BLACK), direction(-1){}
Bullet::Bullet(double x, double y, char symbol, COLORS color, int direction) : GameObject(x, y, (direction == -1) ? '|' : '*', WHITE), direction(direction) {} //default
Bullet::Bullet(const Bullet& other) : GameObject(other), direction(other.direction) {} //copy
Bullet::Bullet(Bullet&& other) noexcept : GameObject(std::move(other)), direction(other.direction) {}

Bullet &Bullet::operator=(const Bullet& other) {
    if (this != &other) {
        GameObject::operator=(other);
        direction = other.direction;
    }

    return *this;
}

Bullet &Bullet::operator=(Bullet &&other) noexcept {
    if (this != &other) {
        GameObject::operator=(std::move(other));
        direction = other.direction;
    }

    return *this;
}


void Bullet::update() {
    setY(getY() + direction);
}

//out of bounds?

int Bullet::getDirection() const {
    return direction;
}

void Bullet::render() {
    draw_char(getSymbol(), getY(), getX(), getColor(), BLACK);
}