#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
using namespace std;
#include "Grid.h"
#include "SFML/Graphics.hpp"
#include "windows.h"
#include "AStar.h"

class Engine {
    public:
        Engine(int delayMilliseconds);
        ~Engine();
        void setDelay(int milliseconds);
        int getDelay() const;
        void run();
        void draw(Grid &grid, AStar &aStar, sf::RenderWindow &window) const;
        void input(Grid &grid, AStar &aStar, sf::RenderWindow &window) const;
    private:
        int delay;
};
#endif