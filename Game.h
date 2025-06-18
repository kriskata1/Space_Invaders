

#ifndef GAME_H
#define GAME_H
#include <conio.h>
#include <windows.h>
#include <vector>
#include "enemy.h"
#include "player.h"
#include "bullet.h"
#include<cmath>
#include "EnemyType1.h"
#include "EnemyType2.h"
#include "EnemyType3.h"
#include "EnemyType4.h"

class Game {
public:
    void initializeEnemies();
    void input();
    void update();
    void checkCollisions();
    void render();
    void run();

    void checkLevelAndWinConditions();
    bool isColliding(double x1, double y1, double x2, double y2, double hitbox = 1.0);
    void enemyShooting();

    static void clearScreen();
    HANDLE hConsole;

    Game();
    virtual ~Game();



private:
    Player player;
    std::vector<GameObject*> enemies;
    std::vector<Bullet*> enemyBullets;
    std::vector<GameObject*> bullets;
    int score, level;
    bool running;
    int enemyMove;
    int enemyShoot;
    bool bonusLifeGiven = false;
    int enemyShootCooldown = 0; //timer към следващия патрон(кога се създават)
    int enemyBulletCounter = 0; //бързина на патрони(брои frameovete)
    int enemyBulletFrequency = 5; //threshold на колко фрейма се активира бързината

    char screenBuffer[90][117];

};



#endif //GAME_H
