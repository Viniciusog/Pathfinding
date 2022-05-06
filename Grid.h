#ifndef GRID_H
#define GRID_H

#include <iostream>
using namespace std;
#include <vector>
#include "Node.h"
#include "Matrix.h"
#include <SFML/Graphics.hpp>

class Grid : public Matrix<Node *> {
    public:
        Grid(int unitSize, int screenWidth, int screenHeight);
        ~Grid();
        void initGrid();
        void setUnitSize(int unitSize);
        int getUnitSize() const;
        void print() const;
        void drawTo(sf::RenderWindow &window) const;
        void setWall(int line, int column);
        void setWalkable(int line, int column);
        void setWidth(int width);
        void setHeight(int width);
        int getWidth() const;
        int getHeight() const;
        Node *getNodeFromWorldPoint(int x, int y) const;
    private:
        int unitSize;
        int width;
        int height;
        Node *start;
        Node *end;
};
#endif