#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

class tPoint
{
private:

    CircleShape _gPoint;

    void make_point(int x, int y);

protected:

    int xLoc;

    int yLoc;

    bool moveDirectionX = rand() % 2;; // true - Right, false - Left

    bool moveDirectionY = rand() % 2; // true - Up, false - Down

    int vX = 0; // speed for X

    int vY = 0; // speed for Y

    int modX = rand() % 2 + 1; // speed modifier for X

    int modY = rand() % 2 + 1; // speed modifier for Y

    RenderWindow* curWindow;

    void setWindow(RenderWindow& window);

    void setColor();

public:

    tPoint();

    void make_point(RenderWindow& window);

    int get_xLoc();

    int get_yLoc();

    void move_straight();

    void move_randomly(Clock& clock);

    void setColor(int r, int g, int b);

    void print();

    void setCoords(int x, int y);
};

