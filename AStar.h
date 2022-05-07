#ifndef STAR_H
#define STAR_H

#include <SFML/Graphics.hpp>
#include "iostream"
#include <vector>
#include <stdlib.h>
#include "Grid.h"
#include "Node.h"
using namespace std;

class AStar
{
public:
    AStar(Grid *grid);
    ~AStar();
    Node *getNodeLowestCost() const;
    void findPath(int startX, int startY, int endX, int endY);

private:
    Grid *grid;
    vector<Node *> openList;
    vector<Node *> closedList;
};

#endif