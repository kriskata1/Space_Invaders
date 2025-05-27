//
// Created by Kris on 24.05.2025.
//

#ifndef GAME_H
#define GAME_H
#include <vector>

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

};



#endif //GAME_H
