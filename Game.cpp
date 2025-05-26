
#include "Game.h"

extern void draw_char(char ch, int y, int x, COLORS foreground, COLORS background);

Game::Game(): score(0), level(1), running(true),enemyMove(0),enemyShoot(0) {
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

void Game::run() {

}


void Game::initializeEnemies() { //dovurshvane
    for (GameObject* enemy: enemies) {
        delete enemy;
    }
    enemies.clear();


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

void Game::update() { //dovurshvane
    for (auto* bullet: bullets) {
        bullet->update();
    }

    for (auto& enemy: enemies) {
        enemy->update();
    }



}

void Game::render() {

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





