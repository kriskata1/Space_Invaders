#include "player.h"

#include "bullet.h"

extern void draw_char(char ch, double y, double x, COLORS foreground, COLORS background);

Player::Player():GameObject(60, 28, 193, LIGHT_GREEN), lives(3), score(0) {}
Player::Player(double x, double y, char symbol, COLORS color, int lives, int score) :GameObject(x, y, symbol, color), lives(lives), score(score) {}
Player::Player(const Player &other):GameObject(other), lives(other.lives), score(other.score) {}
Player::Player(Player &&other) noexcept : GameObject(std::move(other)), lives(other.lives), score(other.score) {}

Player &Player::operator=(const Player &other) {
    if (this != &other) {
        GameObject::operator=(other);
        lives = other.lives;
        score = other.score;
    }

    return *this;
}

Player &Player::operator=(Player &&other) noexcept {
    if (this != &other) {
        GameObject::operator=(std::move(other));
        lives = other.lives;
        score = other.score;
    }

    return *this;
}


void Player::moveLeft() {
    if (getX() > 0) setX(getX()-1);
}

void Player::moveRight() {
    if (getX() < 117) setX(getX()+1);
}

void Player::shoot(std::vector<GameObject*>& bullets) {
    bullets.push_back(new Bullet(getX(), getY()-1, getSymbol(), getColor(), -1));
}

Player& Player::operator+(int points) {
    score = score + points;
    return *this;
}

Player& Player::operator-(int points) {
    score = score - points;
    return *this;
}

void Player::update() {}

void Player::render(){
    draw_char(getSymbol(), getY(), getX(), getColor(), BLACK);
}

int Player::getLives() const { return lives; }
int Player::getScore() const { return score; }

void Player::setLives(int lives) { this->lives = lives; }
void Player::setScore(int score) { this->score = score; }
