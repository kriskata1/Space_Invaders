

#ifndef GAME_H
#define GAME_H
#include <vector>
#include <conio.h>
#include <windows.h>
#include "player.h"


class Game {
public:
    void initializeEnemies();
    void input();
    void update();
    void checkCollisions();
    void render();
    void run();

    void checkLevel();

    Game();
    virtual ~Game();

private:
    Player player;
    std::vector<GameObject*> enemies;
    std::vector<GameObject*> bullets;
    int score, level;
    bool running;
    int enemyMove;
    int enemyShoot;

};



#endif //GAME_H
