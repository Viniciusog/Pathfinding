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

    Grid g(10, 600, 600);
    g.initGrid();

    const unsigned int FPS = 60;

    RenderWindow window(VideoMode(1000, 600), "Path finding!", Style::Close);
    window.setFramerateLimit(FPS);

    while (window.isOpen())
    {
        input(g, window);
        draw(g, window);
    }
}

void Engine::draw(Grid &grid, sf::RenderWindow &window) const {
    grid.drawTo(window);
    window.display();
    window.clear();
    Sleep(30);
}

void Engine::input(Grid &grid, sf::RenderWindow &window) const {
    Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseMoved:
            case Event::MouseButtonPressed:                
                if (Mouse::isButtonPressed(Mouse::Right)) {
                    int column = Mouse::getPosition(window).x / grid.getUnitSize();
                    int line = Mouse::getPosition(window).y / grid.getUnitSize();
                    grid.setWalkable(line, column);
                } else if (Mouse::isButtonPressed(Mouse::Left)) {
                    int column = Mouse::getPosition(window).x / grid.getUnitSize();
                    int line = Mouse::getPosition(window).y / grid.getUnitSize();
                    grid.setWall(line, column);
                }
                break;
        }   
    }
}