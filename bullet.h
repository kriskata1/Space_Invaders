#include "gameObject.h"
#include "gameObject.cpp"

class Bullet : public GameObject {
public:
    Bullet();
    Bullet(int x, int y, char symbol, COLORS color, int direction);
    Bullet(const Bullet &other); //copy
    Bullet(Bullet &&other) noexcept ; //move

    Bullet& operator=(const Bullet& other);
    Bullet& operator=(Bullet&& other) noexcept;

    //metodi
    void update() override;
    void render() override;

private:
    int direction;
};

#ifndef BULLET_H
#define BULLET_H

#endif //BULLET_H
