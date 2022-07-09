#ifndef GRID_H
#define GRID_H

#include <iostream>
using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include "Node.h"
#include <string>
#include "Matrix.h"
#include <SFML/Graphics.hpp>
#include "ValidElement.h"

class Grid : public Matrix<Node *> {
    public:
        Grid(int unitSize, int screenWidth, int screenHeight);
        ~Grid();
        void initGrid();
        void setUnitSize(int unitSize);
        int getUnitSize() const;
        void print() const;
        void drawTo(vector<Node *> path, sf::RenderWindow &window);
        void drawFindingPath(vector<Node *> openList, vector<Node *> closedList, sf::RenderWindow &window);
        void setWall(int line, int column);
        void setWalkable(int line, int column);
        void setWidth(int width);
        void setHeight(int width);
        void setStartPoint(Node *start);
        void setEndPoint(Node *node);
        bool isEndNode(Node *node) const;
        bool isStartNode(Node *node) const;
        void saveInFile() const;
        Node *getStartPoint() const;
        Node *getEndPoint() const;
        //void saveInFile() const;
        //void readFromFile();
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