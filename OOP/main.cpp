#include <iostream>



//*******************************   lab 2   ******************************//
enum Order {
    FROM_CENTER,
    FROM_LEFT_UP_CORNER
};

void spiral(int** matrix, int size, int* array, Order order) {
    int y = -1, x = 0, d = 1, counter, modifier;
    switch (order) {
    case FROM_LEFT_UP_CORNER:
        counter = -1;
        modifier = 1;
        break;
    case FROM_CENTER:
        counter = size * size;
        modifier = -1;
    }

    for (int i = 0; i < size;) {
        for (int j = i; j < size; j++) {
            y += d;
            array[counter += modifier] = matrix[x][y];
        }
        i++;
        for (int j = i; j < size; j++) {
            x += d;
            array[counter += modifier] = matrix[x][y];
        }
        d *= -1;
    }
}

void FIRST(int size) {
    int N = size * size * 4;
    auto buffArray = new int* [size];

    for (int i = 0; i < size; i++) {
        buffArray[i] = new int[size];
        for (int j = 0; j < size; j++) {
            buffArray[i][j] = rand() % 90 + 10;
        }
    }

    auto array = new int[N];
    int iterator = 0;

    for (int x = size - 1; x >= 0; x--) {
        int xLoc = x;
        for (int y = 0; y < size - x; ++y) {
            array[iterator++] = buffArray[y][xLoc++];
        }
    }

    for (int y = 1; y < size; y++) {
        int yLoc = y;
        for (int x = 0; x < size - y; ++x) {
            array[iterator++] = buffArray[yLoc++][x];
        }
    }

    for (int x = 0; x < size; x++) {
        int xPosition = x;
        for (int y = 0; y < x + 1; y++) {
            array[iterator++] = buffArray[y][xPosition--];
        }
    }

    for (int y = 1; y < size; y++) {
        int yPosition = y;
        for (int x = size - 1; x >= y; x--) {
            array[iterator++] = buffArray[yPosition++][x];
        }
    }

    spiral(buffArray, size, array + iterator, Order::FROM_CENTER);
    iterator += size * size;
    spiral(buffArray, size, array + iterator, Order::FROM_LEFT_UP_CORNER);

    std::cout << "\nMain matrix ^-^:\n";

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << buffArray[i][j] << ' ';
        }
        delete[] buffArray[i];
        std::cout << '\n';
    }

    delete[] buffArray;
    std::cout << "\nVariants of question:";

    for (int i = 0; i < 4; i++) {
        std::cout << '\n' << char('A' + i) << ")";
        for (int j = size * size * i; j < size * size * (i + 1); ++j) {
            std::cout << array[j] << ' ';
        }
    }

    delete[] array;
    std::cout << '\n';
}

void SECOND() {
    srand(time(0));
    std::cout << "\nMatrix ^-^:\n";
    int amountOfStr = rand()%10 + 2;
    auto buffArray = new int* [amountOfStr];

    for (int i = 0; i < amountOfStr; i++) {
        int amountOfElementsInStr = rand()%10 + 2;
        buffArray[i] = new int[amountOfElementsInStr + 1];
        buffArray[i][0] = amountOfElementsInStr;
        for (int j = 1; j <= amountOfElementsInStr; j++) {
            int element = rand()%10;
            buffArray[i][j] = element;
        }
    }

    for (int i = 0; i < amountOfStr; i++) {
        for (int j = 1; j <= buffArray[i][0]; j++) {
            std::cout << buffArray[i][j] << ' ';
        }
        delete[] buffArray[i];
        std::cout << '\n';
    }

    delete[] buffArray;
}

void lab_2()
{
    srand(time(0));
    std::cout << "First part of home work:\n";
    FIRST(rand() % 5 + 3);
    std::cout << "\n\n\nSecond part of home work:\n";
    SECOND();
}

//-******************************   lab 2  ******************************-//



//-******************************   lab 3  ******************************-//
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <ctime>

#include "tPoint.h"

using namespace sf;


//Tut tose bez piva pisano, a nado bilo s pivom!!!!
void lab_3()
{
    Clock clock;

    // Setting antialiasing
    ContextSettings settings;
    settings.antialiasingLevel = 16;

    // Getting screen metrics
    int scrX = GetSystemMetrics(SM_CXSCREEN);
    int scrY = GetSystemMetrics(SM_CYSCREEN);

    // Generating window
    RenderWindow window(VideoMode(scrX, scrY), "Programming lab. work #12", Style::Default, settings);

    // Setting frame Limit
    window.setFramerateLimit(300);

    srand(time(nullptr));

    // Make Point object
    const int amountOfPoints = 10; 

    int r[amountOfPoints], b[amountOfPoints], g[amountOfPoints];
    int xStart[amountOfPoints], yStart[amountOfPoints];

    for (int i = 0; i < amountOfPoints; ++i)
    {
        r[i] = rand() % 256;
        g[i] = rand() % 256;
        b[i] = rand() % 256;
        xStart[i] = rand() % window.getSize().x;
        yStart[i] = rand() % window.getSize().y;
    }

    tPoint point[amountOfPoints];
    for (int i = 0; i < amountOfPoints; ++i)
    {
        point[i].make_point(window);
        point[i].setColor(r[i], g[i], b[i]);
        point[i].setCoords(xStart[i], yStart[i]);

    }

    while (window.isOpen())
    {
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::White);

        for (int i = 0; i < amountOfPoints; ++i) {
            point[i].move_straight();
            point[i].print();
        }

        window.display();
    }

    return;
}

//-******************************   lab 3 ******************************-//

class tSection :tPoint
{
    
};

int main()
{
    return 0;
}