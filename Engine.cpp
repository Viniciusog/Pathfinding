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

    Grid g(20, 600, 600);
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
                } else if (Keyboard::isKeyPressed(Keyboard::R)) {
                    aStar.reset();
                }
            case Event::MouseMoved:
            case Event::MouseButtonPressed:
                if (Mouse::isButtonPressed(Mouse::Right)) {     
                    if (!aStar.getPathFound()) {
                        int column = Mouse::getPosition(window).x / grid.getUnitSize();
                        int line = Mouse::getPosition(window).y / grid.getUnitSize();
                        grid.setWalkable(line, column);
                    }                
                } else if (Mouse::isButtonPressed(Mouse::Left)) {
                        cout << "KEY PRESSED" << endl;
                        if (Keyboard::isKeyPressed(Keyboard::S)) {
                            if (!aStar.getPathFound()) {
                                cout << "S" << endl;
                                int column = Mouse::getPosition(window).x / grid.getUnitSize();
                                int line = Mouse::getPosition(window).y / grid.getUnitSize();
                                cout << "Line: " << line << ", Column: " << column << endl;
                                ValidElement<Node *> obj = grid.at(line, column);
                                if (obj.isValid()) {
                                    grid.setStartPoint(obj.getElement());
                                }
                            }
                        } else if (Keyboard::isKeyPressed(Keyboard::E)) {
                            cout << "E" << endl;
                            int column = Mouse::getPosition(window).x / grid.getUnitSize();
                            int line = Mouse::getPosition(window).y / grid.getUnitSize();
                            //if the node in the (x,y) exists
                            ValidElement<Node *> obj = grid.at(line, column);
                            if (obj.isValid()) {
                                grid.setEndPoint(obj.getElement());
                            }                            
                        } 


                    // testar para setar nó inicial e nó final

                    int x = Mouse::getPosition(window).x;
                    int y = Mouse::getPosition(window).y;
                    int column = x / grid.getUnitSize();
                    int line = y / grid.getUnitSize();

                    Node *node = grid.getNodeFromWorldPoint(x, y);
                    // if its not the end node, then set node as wall

                    // only set walls when path is not found and when A or E is not pressed
                    if (!aStar.getPathFound() && !Keyboard::isKeyPressed(Keyboard::S) 
                    && !Keyboard::isKeyPressed(Keyboard::E)) {
                        grid.setWall(line, column); 
                    }         
                }
                break;
        }   
    }
}