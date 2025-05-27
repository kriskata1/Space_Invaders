

#include "Game.h"
#include <conio.h>
#include <windows.h>

#include "EnemyType1.h"
#include "EnemyType2.h"
#include "EnemyType3.h"
#include "EnemyType4.h"

extern void draw_char(char ch, int y, int x, COLORS foreground, COLORS background);

Game::Game(): score(0), level(1), running(true) {
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
    while (running && player.getLives() > 0) {
        input();
        update();
        render();
        Sleep(10);
    }

    if (player.getLives() == 0) {
        std::cout << "\n \n GAME OVER\n";
    }
}

void Game::input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'a' || key == 'A') {
            player.moveLeft();
        }
        else if (key == 'd' || key == 'D') {
            player.moveRight();
        }
        else if (key == ' ') {
            player.shoot(bullets);
        }
    }
}

void Game::checkLevel() {
    if (level == 1 && player.getScore() >= 200) {
        level = 2;
        initializeEnemies();
    }
    else if (level == 2 && player.getScore() >= 500) {
        level = 3;
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
    for (auto* enemy : enemies) {
        enemy->update();
    }

    for (auto* bullet : bullets) {
        bullet->update();
    }
}

void Game::initializeEnemies() {
    enemies.clear();
    int initialY = 2;
    int x = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 10; ++j) {
            x = j * 7 + 5;
            switch (i) {
                case 0:
                    enemies.push_back(new EnemyType1(x, initialY + i * 2));
                break;

                case 1:
                    enemies.push_back(new EnemyType2(x, initialY + i * 2));
                break;

                case 2:
                    enemies.push_back(new EnemyType3(x, initialY + i * 2));
                break;

                case 3:
                    enemies.push_back(new EnemyType4(x, initialY + i * 2));
                break;

                default: ;
            }
        }
    }
}






