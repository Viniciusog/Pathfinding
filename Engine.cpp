#include "Engine.h"
using namespace sf;

Engine::Engine(int milliseconds) {
    this->delay = milliseconds;
}

Engine::~Engine() {

}

void Engine::setDelay(int milliseconds) {
    this->delay = milliseconds;
}

int Engine::getDelay() const {
    return this->delay;
}

void Engine::run() {
    int lines = 5;
    int columns = 5;

    Grid g(120, 600, 600);
    g.initGrid();

    const unsigned int FPS = 60;

    RenderWindow window(VideoMode(1000, 600), "Path finding!", Style::Close);
    window.setFramerateLimit(FPS);

    AStar aStar(&g);

    while (window.isOpen())
    {
        input(g, aStar, window);
        draw(g, aStar, window);
    }
}

void Engine::draw(Grid &grid, AStar &aStar, sf::RenderWindow &window) const {
    //cout << "draw" << endl;
    Node *endNode = grid.getEndPoint();
    cout << (endNode == nullptr ? "PONTEIRO NULO" : "PONTEIRO NORMAL") << endl;
    grid.drawTo(aStar.getPath(grid.getEndPoint()), window);
    window.display();
    window.clear();
    Sleep(30);
}

void Engine::input(Grid &grid, AStar &aStar, sf::RenderWindow &window) const {
    //cout << "input" << endl;
    Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                if (Keyboard::isKeyPressed(Keyboard::A)) {
                    cout << "A" << endl;
                    Node *start = grid.getStartPoint();
                    Node *end = grid.getEndPoint();

                    if (start != nullptr && end != nullptr) {
                        aStar.findPath(start->getX(), start->getY(), end->getX(), end->getY());
                    }
                } 
            case Event::MouseMoved:
            case Event::MouseButtonPressed:
                if (Mouse::isButtonPressed(Mouse::Right)) {     
                    int column = Mouse::getPosition(window).x / grid.getUnitSize();
                    int line = Mouse::getPosition(window).y / grid.getUnitSize();
                    grid.setWalkable(line, column);
                } else if (Mouse::isButtonPressed(Mouse::Left)) {
                        cout << "KEY PRESSED" << endl;
                        if (Keyboard::isKeyPressed(Keyboard::S)) {
                            cout << "S" << endl;
                            int column = Mouse::getPosition(window).x / grid.getUnitSize();
                            int line = Mouse::getPosition(window).y / grid.getUnitSize();
                            cout << "Line: " << line << ", Column: " << column << endl;
                            grid.setStartPoint(grid.at(line, column));
                        } else if (Keyboard::isKeyPressed(Keyboard::E)) {
                            cout << "E" << endl;
                            int column = Mouse::getPosition(window).x / grid.getUnitSize();
                            int line = Mouse::getPosition(window).y / grid.getUnitSize();
                            grid.setEndPoint(grid.at(line, column));
                        } 


                    // testar para setar nó inicial e nó final

                    int x = Mouse::getPosition(window).x;
                    int y = Mouse::getPosition(window).y;
                    int column = x / grid.getUnitSize();
                    int line = y / grid.getUnitSize();

                    Node *node = grid.getNodeFromWorldPoint(x, y);
                    // if its not the end node, then set node as wall
                    if (grid.getEndPoint() != nullptr) {
                        cout << "---------------------------------------------------" << endl;
                        if (!(*node == *grid.getEndPoint())) {
                            grid.setWall(line, column);
                        } 
                    } else {
                        cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
                    }
                }
                break;
        }   
    }
}