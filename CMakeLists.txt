cmake_minimum_required(VERSION 3.29)
project(Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(Project player.cpp
        player.h
        bullet.h
        bullet.cpp
        gameObject.h
        gameObject.cpp
        enemy.h
        enemy.cpp
        main.cpp
        Game.cpp
        Game.h
        EnemyType1.cpp
        EnemyType1.h
        EnemyType2.cpp
        EnemyType2.h
        EnemyType3.cpp
        EnemyType3.h
        EnemyType4.cpp
        EnemyType4.h)
