
#include "gameObject.h"


GameObject::~GameObject() = default;

GameObject::GameObject():x(0), y(0), symbol(' '), color(WHITE) {}
GameObject::GameObject(int x, int y, char symbol, COLORS color) : x(x), y(y), symbol(symbol), color(color){}
GameObject::GameObject(const GameObject &other) : x(other.x), y(other.y), symbol(other.symbol), color(other.color){}
GameObject::GameObject(GameObject &&other) noexcept {
    this->x = other.x;
    this->y = other.y;
    this->symbol = other.symbol;
    this->color = other.color;
}

GameObject& GameObject::operator=(const GameObject& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        symbol = other.symbol;
        color = other.color;
    }

    return *this;
}

GameObject &GameObject::operator=(GameObject &&other) noexcept {
    if (this != &other) {
        x = other.x;
        y = other.y;
        symbol = other.symbol;
        color = other.color;
    }

    return *this;
}


int GameObject::getX() const {
    return x;
}

void GameObject::setX(int x) {
    this->x = x;
}

int GameObject::getY() const {
    return y;
}

void GameObject::setY(int y) {
    this->y = y;
}

char GameObject::getSymbol() const {
    return symbol;
}

void GameObject::setSymbol(char symbol) {
    this->symbol = symbol;
}

COLORS GameObject::getColor() const {
    return color;
}

void GameObject::setColor(COLORS color) {
    this->color = color;
}

