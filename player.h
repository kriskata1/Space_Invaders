#include <vector>

#include "gameObject.h"
#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameObject{
public:
    Player();
    Player(int x, int y, char symbol, COLORS color, int lives, int score);
    Player(const Player &other); //copy
    Player(Player &&other) noexcept; //move

    Player &operator=(const Player &other);
    Player &operator=(Player&& other) noexcept;

    //metodi
    void moveLeft();
    void moveRight();
    void shoot(std::vector<GameObject*>& bullets);

    //getters && setters
    int getLives() const;
    int getScore() const;

    void setLives(int lives);
    void setScore(int score);

    //operatori
    Player& operator+(int points);
    Player& operator-(int points);

    void update() override;
    void render() override;

private:
    int lives; //jivoti
    int score; //tochki
};

#endif //PLAYER_H
