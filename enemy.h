#include "gameObject.h"

#ifndef ENEMY_H
#define ENEMY_H



class Enemy: public GameObject {
public:
    Enemy();
    Enemy(int x, int y, char symbol, COLORS color, int points);
    Enemy(const Enemy &other); //copy
    Enemy(Enemy &&other) noexcept; //move

    Enemy& operator=(const Enemy& other);
    Enemy& operator=(Enemy&& other) noexcept ;

    //metodi
    void update() override;
    void render() override;

    int getPoints() const; //nagrada za ubivane
    int getDirection() const;
    void setDirection(int direction);

protected:
    int direction; // posoka na dvijenie
    int points;
};



#endif //ENEMY_H
