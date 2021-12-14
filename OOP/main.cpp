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
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

int width = 600;
int height = 600;

class tPixel {
protected:
    float x;
    float y;
    float xSpeed = 0;
    float ySpeed = 0;
    int color[3];
    int radius = 30;
    int angles = 4;
    int rotate = 0;

public:
    //конструктор по умолчанию
    tPixel() {
        x = 0;
        y = 0;
        xSpeed = 1;
        ySpeed = 1;
        color[0] = color[1] = color[2] = 0;
        radius = 3;
        angles = 30;
        rotate = 0;
    };
    //конструктор с несколькими параметрами
    tPixel(int a, int b, int c, int d) {
        x = a;
        y = b;
        xSpeed = c;
        ySpeed = d;
        color[0] = color[1] = color[2] = 0;
        radius = 3;
        angles = 30;
        rotate = 0;
    }
    virtual void drawPolygon(RenderWindow* window) {
        CircleShape polygon(radius, angles);
        polygon.setPosition(x, y);
        polygon.setOrigin(radius, radius);
        polygon.rotate(rotate);
        polygon.setOutlineThickness(3);
        polygon.setOutlineColor(Color(color[0], color[1], color[2]));
        polygon.setFillColor(Color(0, 0, 0, 0));
        // последний 0 == прозрачность
        window->draw(polygon);
    }
    virtual void forwardMove() {
        rotate = 0;
        if (x >= width - xSpeed - radius || x <= -xSpeed + radius) {
            xSpeed = -xSpeed;
        }
        if (y >= height - ySpeed - radius || y <= -ySpeed + radius) {
            ySpeed = -ySpeed;
        }
        x += xSpeed;
        y += ySpeed;
    }
    virtual void randomMove() {
        if (x >= width - xSpeed || x <= -xSpeed) {
            xSpeed = -xSpeed;
        }
        if (y >= height - ySpeed || y <= -ySpeed) {
            ySpeed = -ySpeed;
        }
        x += xSpeed;
        y += ySpeed;
        int s;
        s = rand() % 50;
        // чем меньше, тем чаще меняется направление
        // и почему-то все скапливаются в углу
        switch (s) {
        case 0: {
            xSpeed = rand() % 10;
            ySpeed = rand() % 10;
            break;
        }
        case 1: {
            xSpeed = rand() % 10;
            break;
        }
        case 2: {
            ySpeed = rand() % 10;
            break;
        }
        case 3: {
            xSpeed = -xSpeed;
            break;
        }
        case 4: {
            ySpeed = -ySpeed;
            break;
        }
        case 5: {
            xSpeed = -xSpeed;
            ySpeed = -ySpeed;
            break;
        }
        default: {
            break;
        }
        }
    }

    virtual void rotateMove() {
        rotate++;
    }
};

class tTriangle : public tPixel {
public:
    //конструктор по умолчанию
    tTriangle() {
        radius = rand() % 30 + 5;
        while ((x <= radius * 2) || (x >= width - radius * 2)) {
            x = rand() % width;
        }
        while ((y <= radius * 2) || (y >= height - radius * 2)) {
            y = rand() % height;
        }
        xSpeed = 0.3f;
        ySpeed = 0.3f;
        for (int i = 0; i < 3; i++) {
            color[i] = rand() % 255;
        }
        angles = 3;
        rotate = 0;
    };
};

class tCircle : public tPixel {
public:
    //конструктор по умолчанию
    tCircle() {
        radius = rand() % 30 + 5;
        while ((x <= radius * 2) || (x >= width - radius * 2)) {
            x = rand() % width;
        }
        while ((y <= radius * 2) || (y >= height - radius * 2)) {
            y = rand() % height;
        }
        xSpeed = 0.3f;
        ySpeed = 0.3f;
        for (int i = 0; i < 3; i++) {
            color[i] = rand() % 255;
        }
        angles = 30;
        rotate = 0;
    };
    tCircle(int rad) {
        radius = rad;
        while ((x <= radius * 2) || (x >= width - radius * 2)) {
            x = rand() % width;
        }
        while ((y <= radius * 2) || (y >= height - radius * 2)) {
            y = rand() % height;
        }
        xSpeed = 0.3f;
        ySpeed = 0.3f;
        for (int i = 0; i < 3; i++) {
            color[i] = rand() % 255;
        }
        angles = 30;
        rotate = 0;
    };
};

class tPoint : public tCircle {
public:
    //конструктор по умолчанию
    tPoint() {
        radius = 3;
        while ((x <= radius * 2) || (x >= width - radius * 2)) {
            x = rand() % width;
        }
        while ((y <= radius * 2) || (y >= height - radius * 2)) {
            y = rand() % height;
        }
        xSpeed = 0.3f;
        ySpeed = 0.3f;
        for (int i = 0; i < 3; i++) {
            color[i] = rand() % 255;
        }
        angles = 30;
        rotate = 0;
    };
    tPoint(int rad)
    {
        radius = rad;
        while ((x <= radius * 2) || (x >= width - radius * 2)) {
            x = rand() % width;
        }
        while ((y <= radius * 2) || (y >= height - radius * 2)) {
            y = rand() % height;
        }
        xSpeed = 0.3f;
        ySpeed = 0.3f;
        for (int i = 0; i < 3; i++) {
            color[i] = rand() % 255;
        }
        angles = 30;
        rotate = 0;
    };
    virtual void drawPolygon(RenderWindow* window) {
        CircleShape polygon(radius, angles);
        polygon.setPosition(x, y);
        polygon.setFillColor(Color(color[0], color[1], color[2]));
        window->draw(polygon);
    }
};
// ромб
class tRhomb : public tPixel {
public:
    //конструктор по умолчанию
    tRhomb()
    {
        radius = rand() % 30 + 5;
        while ((x <= radius * 2) || (x >= width - radius * 2)) {
            x = rand() % width;
        }
        while ((y <= radius * 2) || (y >= height - radius * 2)) {
            y = rand() % height;
        }
        xSpeed = 0.3f;
        ySpeed = 0.3f;
        for (int i = 0; i < 3; i++) {
            color[i] = rand() % 255;
        }
        angles = 4;
        rotate = 0;
    };

};
// прямоугольник
class tRectangle : public tPixel {
protected:
    int ox;
    int oy;
public:
    //конструктор по умолчанию
    tRectangle() {
        ox = rand() % 30 + 5;
        oy = rand() % 30 + 5;
        while ((x <= ox * 2) || (x >= width - ox * 2)) {
            x = rand() % width;
        }
        while ((y <= oy * 2) || (y >= height - oy * 2)) {
            y = rand() % height;
        }
        xSpeed = 0.3f;
        ySpeed = 0.3f;
        for (int i = 0; i < 3; i++) {
            color[i] = rand() % 255;
        }
        angles = 4;
        rotate = 0;
    };
    virtual void drawPolygon(RenderWindow* window) {
        RectangleShape polygon(Vector2f(ox, oy));
        polygon.setPosition(x, y);
        polygon.setOrigin(ox / 2, oy / 2);
        polygon.rotate(rotate);
        polygon.setOutlineThickness(3);
        polygon.setOutlineColor(Color(color[0], color[1], color[2]));
        polygon.setFillColor(Color(0, 0, 0, 0));
        // последний 0 == прозрачность
        window->draw(polygon);
    }
    virtual void forwardMove() {
        rotate = 0;
        if (x >= width - xSpeed - ox / 2 || x <= -xSpeed + ox / 2) {
            xSpeed = -xSpeed;
        }
        if (y >= height - ySpeed - oy / 2 || y <= -ySpeed + oy / 2) {
            ySpeed = -ySpeed;
        }
        x += xSpeed;
        y += ySpeed;
    }

};

class tLine : public tRectangle {
public:
    //конструктор по умолчанию
    tLine() {
        ox = rand() % 30 + 5;
        oy = 3;
        while ((x <= ox * 2) || (x >= width - ox * 2)) {
            x = rand() % width;
        }
        while ((y <= oy * 2) || (y >= height - oy * 2)) {
            y = rand() % height;
        }
        xSpeed = 0.3f;
        ySpeed = 0.3f;
        for (int i = 0; i < 3; i++) {
            color[i] = rand() % 255;
        }
        angles = 4;
        rotate = 0;
    };
    virtual void drawPolygon(RenderWindow* window) {
        RectangleShape polygon(Vector2f(ox, oy));
        polygon.setPosition(x, y);
        polygon.setOrigin(ox / 2, oy / 2);
        polygon.setFillColor(Color(color[0], color[1], color[2]));
        polygon.rotate(rotate);
        window->draw(polygon);
    }
};

class tEllipse : public tRectangle {
public:
    //конструктор по умолчанию
    tEllipse() {
        radius = rand() % 30 + 5;
        ox = 4 * radius;
        oy = 2 * radius;
        while ((x <= ox * 2) || (x >= width - ox * 2)) {
            x = rand() % width;
        }
        while ((y <= oy * 2) || (y >= height - oy * 2)) {
            y = rand() % height;
        }
        xSpeed = 0.3f;
        ySpeed = 0.3f;
        for (int i = 0; i < 3; i++) {
            color[i] = rand() % 255;
        }
        angles = 30;
        rotate = 0;
    };
    tEllipse(int rad, int angl)
    {
        radius = rad;
        ox = 4 * radius;
        oy = 2 * radius;
        while ((x <= ox * 2) || (x >= width - ox * 2)) {
            x = rand() % width;
        }
        while ((y <= oy * 2) || (y >= height - oy * 2)) {
            y = rand() % height;
        }
        xSpeed = 0.3f;
        ySpeed = 0.3f;
        for (int i = 0; i < 3; i++) {
            color[i] = rand() % 255;
        }
        angles = angl;
        rotate = 0;
    }
    virtual void drawPolygon(RenderWindow* window) {
        CircleShape polygon(radius, angles);
        polygon.setPosition(x, y);
        polygon.setOrigin(radius, radius);
        polygon.rotate(rotate);
        polygon.setOutlineThickness(3);
        polygon.setOutlineColor(Color(color[0], color[1], color[2]));
        polygon.setFillColor(Color(0, 0, 0, 0));
        // последний 0 == прозрачность
        polygon.setScale(2, 1);
        window->draw(polygon);
    }
};

void lab_3()
{
    srand(time(0));
    RenderWindow window(VideoMode(width, height), "lab_3");

    tPoint arr[100];
    bool mode = 1;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    mode = !mode;
                }
            }
        }
        window.clear();
        for (int i = 0; i < 100; i++)
        {
            if (mode == 1)
            {
                //sto[i].forwardMove();
                arr[i].randomMove();
                arr[i].drawPolygon(&window);
                //
                //arr[i].forwardMove();
                //arr[i].drawPolygon(&window);
            }
            else
            {
                arr[i].rotateMove();
                //arr[i].rotateMove();
            }
            arr[i].drawPolygon(&window);
            //arr[i].drawPolygon(&window);
        }
        sleep(seconds(0.05));
        window.display();
    }
}

void lab_4()
{
    ContextSettings set;
    set.antialiasingLevel = 16;
    srand(time(0));
    RenderWindow window(VideoMode(width, height), "lab_4", Style::Default, set);

    tTriangle triangle;
    tRhomb rhomb;
    bool mode = 1;

    window.setFramerateLimit(120);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    mode = !mode;
                }
            }
        }
        window.clear();
        for (int i = 0; i < 100; i++)
        {
            if (mode)
            {
                //sto[i].forwardMove();
                //triangle.randomMove();
                //triangle.rotateMove();
                triangle.forwardMove();
                rhomb.forwardMove();
                rhomb.drawPolygon(&window);
                triangle.drawPolygon(&window);
                //arr[i].forwardMove();
                //arr[i].drawPolygon(&window);
            }
            else
            {
                triangle.rotateMove();
                rhomb.rotateMove();
                //arr[i].rotateMove();
            }
            window.clear();
            rhomb.drawPolygon(&window);
            triangle.drawPolygon(&window);
            //arr[i].drawPolygon(&window);
        }
        sleep(seconds(0.05));
        window.display();
    }
}

struct tStructures
{
    tPoint point;
    tLine line;
    tTriangle triangle;
    tRectangle rectangle;
    tRhomb rhomb;
    tCircle circle;
    tEllipse ellipse;
};

void lab_6()
{
    ContextSettings set;
    set.antialiasingLevel = 16;
    srand(time(0));
    RenderWindow window(VideoMode(width, height), "lab_4", Style::Default, set);

    tStructures* structures;
    structures = new tStructures[3];
    bool mode = 1;

    window.setFramerateLimit(120);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    mode = !mode;
                }
            }
        }
        window.clear();
        for (int i = 0; i < 3; i++)
        {
            if (mode)
            {
                structures[i].point.forwardMove();
                structures[i].point.drawPolygon(&window);
                structures[i].circle.forwardMove();
                structures[i].circle.drawPolygon(&window);
                structures[i].line.forwardMove();
                structures[i].line.drawPolygon(&window);
                structures[i].triangle.forwardMove();
                structures[i].triangle.drawPolygon(&window);
                structures[i].rectangle.forwardMove();
                structures[i].rectangle.drawPolygon(&window);
                structures[i].ellipse.forwardMove();
                structures[i].ellipse.drawPolygon(&window);
                structures[i].rhomb.forwardMove();
                structures[i].rhomb.drawPolygon(&window);
            }
            else
            {
                structures[i].point.rotateMove();
                structures[i].circle.rotateMove();
                structures[i].line.rotateMove();
                structures[i].triangle.rotateMove();
                structures[i].rectangle.rotateMove();
                structures[i].ellipse.rotateMove();
                structures[i].rhomb.rotateMove();
            }
            structures[i].point.drawPolygon(&window);
            structures[i].rhomb.drawPolygon(&window);
            structures[i].ellipse.drawPolygon(&window);
            structures[i].rectangle.drawPolygon(&window);
            structures[i].triangle.drawPolygon(&window);
            structures[i].line.drawPolygon(&window);
            structures[i].circle.drawPolygon(&window);
        }
        sleep(seconds(0.05));
        window.display();
        window.clear();
    }
}

using namespace std;

class tNode

{
public:
    int data;
    tNode* next;

    tNode() :data()
    {
        next = NULL;
    }

    tNode(int value) 
    {
        data = value;
        next = NULL;
    }

    tNode(int value, tNode* next_pointer)
    {
        data = value;
        next = next_pointer;
    }
};

class tList
{
protected:
    tNode* head;
    static int count;

public:
    tList()
    {
        head = NULL;
        count++;
    }

    virtual void push() = 0;
    virtual void push(int value) = 0;
    virtual void push(int value, tNode* next_pointer) = 0;
    virtual void clear() = 0;

    void deleteHead()
    {
        try
        {
            if (head == NULL) throw "Nothing to delete";

            tNode* p = head->next;
            delete head;
            head = p;
        }
        catch (const char* exception)
        {
            cerr << "Error: " << exception << '\n';
        }
    };
    void print()
    {
        try
        {
            if (head == NULL) throw "Nothing to print";
            tNode* pos = head;

            while (pos != NULL)
            {
                cout << pos->data << " ";
                pos = pos->next;
            }
            cout << "\n";
        }
        catch (const char* exception)
        {
            cerr << "Error: " << exception << '\n';
        }
    };
    int getCount()
    {
        return count;
    };
};

int tList::count = 0;

class tQueue : public tList
{
protected:
    tNode* tail;

public:
    tQueue()
    {
        tail = (tNode*)&head;
    }

    ~tQueue()
    {
        if (head != NULL) clear();
        count--;
    }

    virtual void push()
    {
        tNode* p = new tNode();

        if (head != NULL)
        {
            tail->next = p;
        }
        else
        {
            head = p;
        }

        tail = p;
    };
    virtual void push(int value)
    {
        tNode* p = new tNode(value);

        if (head != NULL)
        {
            tail->next = p;
        }
        else
        {
            head = p;
        }

        tail = p;
    };
    virtual void push(int value, tNode* next_pointer)
    {
        tNode* p = new tNode(value);

        if (head != NULL)
        {
            tail->next = p;
        }
        else
        {
            head = p;
        }

        tail = p;

        p = next_pointer;
        tail->next = p;
        tail = p;
    };
    virtual void clear()
    {
        try
        {
            if (head == NULL) throw "Nothing to free";

            tNode* pos, * q;
            q = pos = head;

            while (pos != NULL)
            {
                pos = q->next;
                delete q;
                q = pos;
            }

            head = NULL;
            tail = NULL;
        }
        catch (const char* exception)
        {
            cerr << "Error: " << exception << '\n';
        }
    };
};

class tStack : public tList
{
public:
    ~tStack()
    {
        if (head != NULL) clear();
        count--;
    }

    virtual void push()
    {
        if (head == NULL)
        {
            head = new tNode();
        }
        else
        {
            tNode* p = new tNode();

            p->next = head;
            head = p;
        }
    };
    virtual void push(int value)
    {
        if (head == NULL)
        {
            head = new tNode(value);
        }
        else
        {
            tNode* p = new tNode(value);

            p->next = head;
            head = p;
        }
    };
    virtual void push(int value, tNode* next_pointer)
    {
        if (head == NULL)
        {
            head = new tNode(value);
        }
        else
        {
            tNode* p = new tNode(value);

            p->next = head;
            head = p;
        }

        tNode* p = next_pointer;
        p->next = head;
        head = p;
    };
    virtual void clear()
    {
        try
        {
            if (head == NULL) throw "Nothing to free";

            tNode* pos, * q;
            q = pos = head;

            while (pos != NULL)
            {
                pos = q->next;
                delete q;
                q = pos;
            }

            head = NULL;
        }
        catch (const char* exception)
        {
            cerr << "Error: " << exception << '\n';
        }
    };
};

void lab_7()
{
    tNode* next = new tNode();
    srand(time(NULL));
    tStack* stack = new tStack();
    cout << "\nStack:";
    stack->push(1);
    stack->push(16);
    stack->push(72);
    stack->print();
    stack->deleteHead();
    stack->print();
    stack->deleteHead();
    stack->print();
    stack->deleteHead();


    stack->print();
    stack->deleteHead();


    tQueue* queue = new tQueue();
    cout << "\nQueue:";
    queue->push(1);
    queue->push(213);
    queue->push(11);
    queue->print();
    queue->deleteHead();
    queue->print();
    queue->deleteHead();
    queue->print();
    queue->deleteHead();


    queue->print();
    queue->deleteHead();


    delete queue;
    delete stack;
}

int main() {
    //lab_3();
    //lab_4();
    //lab_6();
    lab_7();
    return 0;
}