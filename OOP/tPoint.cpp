#include "tPoint.h"

void tPoint::make_point(int x, int y)
{
    srand(time(0));
    CircleShape point(6.f);
    point.move(xLoc, yLoc);
    _gPoint = point;
    setColor();
}

void tPoint::setWindow(RenderWindow& window)
{
    curWindow = &window;
}

void tPoint::setColor()
{
    _gPoint.setFillColor(Color(0, 0, 0));
}

tPoint::tPoint()
{
    srand(time(0));
    xLoc = (rand() % GetSystemMetrics(SM_CXSCREEN));
    yLoc = (rand() % GetSystemMetrics(SM_CYSCREEN));
    make_point(xLoc, yLoc);
}

void tPoint::make_point(RenderWindow& window)
{
    srand(time(0));
    make_point(xLoc, yLoc);
    setWindow(window);
    setColor();
}

int tPoint::get_xLoc()
{
    return xLoc;
}

int tPoint::get_yLoc()
{
    return yLoc;
}

void tPoint::move_straight()
{
    int x = _gPoint.getPosition().x, y = _gPoint.getPosition().y;

    if (x >= curWindow->getSize().x || x <= 0)
    {
        moveDirectionX = !moveDirectionX;
        vX = -vX;
    }
    if (y >= curWindow->getSize().y || y <= 0)
    {
        moveDirectionY = !moveDirectionY;
        vY = -vY;
    }

    if (moveDirectionX)
    {
        vX = 1;
    }
    if (!moveDirectionX)
    {
        vX = -1;
    }
    if (moveDirectionY)
    {
        vY = -1;
    }
    if (!moveDirectionY)
    {
        vY = 1;
    }

    _gPoint.move(vX, vY);

    xLoc = _gPoint.getPosition().x;
    yLoc = _gPoint.getPosition().y;
}

void tPoint::move_randomly(Clock& clock)
{
    srand(time(0));
    int time = clock.getElapsedTime().asSeconds();
    if (time > 0.1)
    {
        modX = rand() % 3 + 1;
        modY = rand() % 3 + 1;
        clock.restart();
    }

    int x = _gPoint.getPosition().x, y = _gPoint.getPosition().y;

    if (x >= curWindow->getSize().x || x <= 0)
    {
        moveDirectionX = !moveDirectionX;
        vX = -vX;
    }
    if (y >= curWindow->getSize().y || y <= 0)
    {
        moveDirectionY = !moveDirectionY;
        vY = -vY;
    }

    if (moveDirectionX)
    {
        vX = 1;
    }
    if (!moveDirectionX)
    {
        vX = -1;
    }
    if (moveDirectionY)
    {
        vY = -1;
    }
    if (!moveDirectionY)
    {
        vY = 1;
    }

    _gPoint.move(modX * vX, modY * vY);

    xLoc = _gPoint.getPosition().x;
    yLoc = _gPoint.getPosition().y;
}

void tPoint::setColor(int r, int g, int b)
{
    _gPoint.setFillColor(Color(r, g, b));
}

void tPoint::print()
{
    curWindow->draw(_gPoint);
}

void tPoint::setCoords(int x, int y)
{
    xLoc = x;
    yLoc = y;
    _gPoint.setPosition(xLoc, yLoc);
}