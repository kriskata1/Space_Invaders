

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
    void cls();
    void setCursorPosition(int x, int y);

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
