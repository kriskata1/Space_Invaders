#include "Game.h"

int countUpdates = 0;
int speedInMs = 15;

extern void draw_char(char ch, double y, double x, COLORS foreground, COLORS background);

Game::Game(): score(0), level(1), running(false) {
    initializeEnemies();
}

Game::~Game() {
    for (auto *enemy: enemies) {
        delete enemy;
    }

    for (auto *bullet: bullets) {
        delete bullet;
    }

    for (auto *bullet: enemyBullets) {
        delete bullet;
    }
}

//rendering
void Game::clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hConsole, coord);

    std::cout << std::string(117 * 90, ' ');
    SetConsoleCursorPosition(hConsole, coord);
}

void Game::render() {
    clearScreen();
    std::cout << "Score: " << player.getScore() << " Lives: " << player.getLives() << " Level: " << level << std::endl;
    player.render();
    for (auto *enemy: enemies) {
        enemy->render();
    }

    for (auto *bullet: bullets) {
        bullet->render();
    }

    for (auto *bullet: enemyBullets) {
        bullet->render();
    }
}

//rendering

//run i update
void Game::run() {
    clearScreen();
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

    while (running) {
        input();
        update();
        render();
        Sleep(1);

        if (player.getLives() <= 0) {
            clearScreen();
            std::cout << "\n\n\n";
            std::cout << "\n \n \t \t \t \t \t \t GAME OVER\n";
            std::cout << std::endl;
            std::cout << "\n \n \t \t \t \t \t \t Final Score: " << player.getScore() << "\n";
            std::cout << std::endl;
            _getch();
        }
    }
}

void Game::update() {
    countUpdates++;
    enemyBulletCounter++;

    if (countUpdates >= speedInMs) {
        for (auto *enemy: enemies) {
            enemy->update();
        }

        countUpdates = 0;
    }

    for (auto *bullet: bullets) {
        bullet->update();
    }

    if (enemyBulletCounter >= enemyBulletSpeed) {
        for (auto *bullet: enemyBullets) {
            bullet->update();
        }
        enemyBulletCounter = 0;
    }

    checkLevelAndWinConditions();
    enemyShooting();
    checkCollisions();
}

//run i update

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
        clearScreen();
        running = false;
    }

    // намаля cooldown-a с 1 всеки път
    if (shootCooldown > 0) {
        shootCooldown--;
    }
}

void Game::checkLevelAndWinConditions() {
    if (level == 1 && player.getScore() >= 200) {
        level = 2;
        speedInMs = 5;
        enemyBulletSpeed = 3;
        enemyBulletCounter = 50 + rand() % 60;
        initializeEnemies();
    } else if (level == 2 && player.getScore() >= 500) {
        level = 3;
        speedInMs = 2;
        enemyBulletSpeed = 1;
        enemyBulletCounter = 30 + rand() % 30;
        initializeEnemies();
    }

    if (level == 2 && player.getScore() >= 300 && !bonusLifeGiven) {
        player.setLives(player.getLives() + 1);
        bonusLifeGiven = true;
    }

    if (enemies.empty()) {
        if (level < 3) {
            ++level;
            initializeEnemies();
        } else {
            clearScreen();
            std::cout << "\n \n \t \t \t \t \t \t YOU WIN!\n";
            std::cout << "\n \n \t \t \t \t \t \t Final Score: " << player.getScore() << "\n";
            _getch();
        }
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

void Game::enemyShooting() {
    enemyShootCooldown--;

    if (enemyShootCooldown <= 0 && !enemies.empty()) {
        // random enemy da strelq
        int randomIndex = rand() % enemies.size();
        std::vector<GameObject *>::value_type shootingEnemy = enemies[randomIndex];

        //enemy bullet da se dviji nadolu
        Bullet *enemyBullet = new Bullet(shootingEnemy->getX(), shootingEnemy->getY() + 1, '*', WHITE, 1);
        enemyBullets.push_back(enemyBullet);

        if (level == 1) enemyShootCooldown = 60 + (rand() % 60);
        else if (level == 2) enemyShootCooldown = 40 + (rand() % 40);
        else if (level == 3) enemyShootCooldown = 20 + (rand() % 20);
    }
}


void Game::checkCollisions() {
    // proverka za dokosvane na bulleti s enemytata
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool bulletHit = false;

        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
            // tesvane na dokosvane na bulleti s enemy
            if (isColliding((*bulletIt)->getX(), (*bulletIt)->getY(),
                            (*enemyIt)->getX(), (*enemyIt)->getY())) {

                int points = 0;
                if (dynamic_cast<EnemyType1*>(*enemyIt)) points = 10;
                if (dynamic_cast<EnemyType2*>(*enemyIt)) points = 20;
                else if (dynamic_cast<EnemyType3*>(*enemyIt)) points = 30;
                else if (dynamic_cast<EnemyType4*>(*enemyIt)) points = 40;
                player.setScore(player.getScore() + points);

                delete *enemyIt;
                enemyIt = enemies.erase(enemyIt);

                delete *bulletIt;
                bulletIt = bullets.erase(bulletIt);

                bulletHit = true;
                break;
            } else {
                ++enemyIt;
            }
        }

        if (!bulletHit) {
            ++bulletIt;
        }
    }

    for (auto bulletIt = enemyBullets.begin(); bulletIt != enemyBullets.end();) {
        if (isColliding((*bulletIt)->getX(), (*bulletIt)->getY(),
                        player.getX(), player.getY())) {
            player.setLives(player.getLives() - 1);

            delete *bulletIt;
            bulletIt = enemyBullets.erase(bulletIt);
        } else {
            ++bulletIt;
        }
    }

    // proverka za dokosvane na enemy s player
    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
        if (isColliding((*enemyIt)->getX(), (*enemyIt)->getY(),
                        player.getX(), player.getY())) {
            player.setLives(0);

            delete *enemyIt;
            enemyIt = enemies.erase(enemyIt);
        } else {
            ++enemyIt;
        }
    }

    // mahane na bulleti izvun ekran
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        if ((*bulletIt)->getY() < 0 || (*bulletIt)->getY() > 40) {
            delete *bulletIt;
            bulletIt = bullets.erase(bulletIt);
        } else {
            ++bulletIt;
        }
    }
}

bool Game::isColliding(double x1, double y1, double x2, double y2, double hitbox) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    double distance = sqrt(dx * dx + dy * dy);
    return distance < hitbox; //pod 1 e hit
}
