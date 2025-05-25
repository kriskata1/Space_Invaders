//
// Created by Kris on 24.05.2025.
//

#include "Game.h"

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


