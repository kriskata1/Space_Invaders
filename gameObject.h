
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <windows.h>

enum COLORS {
    BLACK = 0,
    BLUE = FOREGROUND_BLUE,
    CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN,
    GREEN = FOREGROUND_GREEN,
    RED = FOREGROUND_RED,
    BROWN = FOREGROUND_RED | FOREGROUND_GREEN,
    PURPLE = FOREGROUND_RED | FOREGROUND_BLUE,
    LIGHT_GREY = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN,
    GREY = 0 | FOREGROUND_INTENSITY,
    LIGHT_BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    LIGHT_CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    LIGHT_GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    LIGHT_RED = FOREGROUND_RED | FOREGROUND_INTENSITY,
    YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    PINK = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    WHITE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
};

class GameObject {
public:
    GameObject();
    GameObject(double x, double y, char symbol, COLORS color);
    GameObject(const GameObject &other); //copy
    GameObject(GameObject &&other) noexcept; //move

    virtual ~GameObject();

    GameObject& operator=(const GameObject& other);
    GameObject& operator=(GameObject&& other) noexcept;

    virtual void update() = 0;
    virtual void render() = 0; //zapisvane na poziciq(vizualizaciq)

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    char getSymbol() const;

    void setSymbol(char symbol);

    [[nodiscard]] COLORS getColor() const;

    void setColor(COLORS color);

private:
    double x,y; //koordinati
    char symbol; //vizualen simvol
    COLORS color; //cvqt na simvola
};



#endif //GAMEOBJECT_H
