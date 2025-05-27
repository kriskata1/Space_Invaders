

#include "Game.h"
#include <conio.h>
#include <windows.h>

#include "EnemyType1.h"
#include "EnemyType2.h"
#include "EnemyType3.h"
#include "EnemyType4.h"

int countUpdates = 0;
int speedInMs = 15;

extern void draw_char(char ch, double y, double x, COLORS foreground, COLORS background);

Game::Game(): score(0), level(1), running(false) {
    initializeEnemies();
}

Game::~Game() {
    for (auto* enemy: enemies) {
        delete enemy;
    }

    for (auto* bullet: bullets) {
        delete bullet;
    }
}

void Game::render() {
    system("cls");

    std::cout << "Score: " << player.getScore() << " Lives: " << player.getLives() << " Level: " << level << std::endl;
    player.render();
    for (auto* enemy : enemies) {
        enemy->render();
    }

    for (auto* bullet : bullets) {
        bullet->render();
    }

}

void Game::run() {
    system("cls");

    std::cout << "\n\n\n";
    std::cout << "\n \n \t \t \t \t \t \t PLAY\n";
    std::cout << std::endl;
    std::cout << "\n \n \t \t \t \t \t \t SPACE INVADERS\n";
    std::cout << std::endl;
    std::cout << "\n \n \t \t \t \t \t \t TO PLAY PRESS ENTER\n";

    while (true) {
        if (_kbhit() && _getch() == 13) {
            running = true;
            break;
        }
    }


    while (running && player.getLives() > 0) {
        input();
        update();
        render();
        Sleep(5);
    }

    if (player.getLives() == 0) {
        std::cout << "\n \n GAME OVER\n";
    }
}



void Game::input() {
    static int shootCooldown = 0;

    if (GetAsyncKeyState('A') & 0x8000) {
        player.moveLeft();
    }

    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        player.moveLeft();
    }

    if (GetAsyncKeyState('D') & 0x8000) {
        player.moveRight();
    }

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        player.moveRight();
    }

    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        if (shootCooldown <= 0) {
            player.shoot(bullets);
            shootCooldown = 15; //на всеки 15 кадъра в секунда стреля
        }
    }

    if (GetAsyncKeyState(VK_ESCAPE)) {
        system("cls");
        Game::~Game();
        running = false;
    }

    // намаля cooldown-a с 1 всеки път
    if (shootCooldown > 0) {
        shootCooldown--;
    }
}

void Game::checkLevel() {
    if (level == 1 && player.getScore() >= 200) {
        level = 2;
        speedInMs = 7;
        initializeEnemies();
    }
    else if (level == 2 && player.getScore() >= 500) {
        level = 3;
        speedInMs = 2;
        initializeEnemies();
    }

    if(level == 2 && player.getScore() >= 300) {
        player.setLives(player.getLives() + 1);
    }

    if(enemies.empty()) {
        if(level < 3) {
            ++level;
            initializeEnemies();
        }
        else {
            // std::cout << "You win" << std::endl;
            running = false;
        }
    }

    if(player.getLives() <= 0) {
        // std::cout << "You lose" << std::endl;
        running = false;
    }
}

void Game::update() {
    countUpdates++;

    if (countUpdates >= speedInMs) {
        for (auto* enemy : enemies) {
            enemy->update();
        }

        countUpdates = 0;
    }

    for (auto* bullet : bullets) {
        bullet->update();
    }
}

void Game::initializeEnemies() {
    enemies.clear();
    double initialY = 2.0;
    int x = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 17; ++j) {
            x = j * 3 + 5;
            switch (i) {
                case 0:
                    enemies.push_back(new EnemyType4(x, initialY + i * 2));
                break;

                case 1:
                    enemies.push_back(new EnemyType3(x, initialY + i * 2));
                break;

                case 2:
                    enemies.push_back(new EnemyType2(x, initialY + i * 2));
                break;

                case 3:
                    enemies.push_back(new EnemyType1(x, initialY + i * 2));
                break;

                default: ;
            }
        }
    }
}






