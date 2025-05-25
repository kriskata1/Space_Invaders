#include "gameObject.h"
#include "gameObject.cpp"

#ifndef ENEMY_H
#define ENEMY_H



class Enemy: public GameObject {
public:
    Enemy();
    Enemy(int x, int y, char symbol, COLORS color, int direction);
    Enemy(const Enemy &other); //copy
    Enemy(Enemy &&other) noexcept; //move

    Enemy& operator=(const Enemy& other);
    Enemy& operator=(Enemy&& other) noexcept ;

    //metodi
    void update() override;
    void render() override;

protected:
    int direction; // posoka na dvijenie

};



#endif //ENEMY_H
