#include "gameObject.h"

class Bullet : public GameObject {
public:
    Bullet();
    Bullet(double x, double y, char symbol, COLORS color, int direction);
    Bullet(const Bullet &other); //copy
    Bullet(Bullet &&other) noexcept ; //move

    Bullet& operator=(const Bullet& other);
    Bullet& operator=(Bullet&& other) noexcept;

    //metodi
    void update() override;
    void render() override;

    int getDirection() const;

private:
    int direction;
};

#ifndef BULLET_H
#define BULLET_H

#endif //BULLET_H
