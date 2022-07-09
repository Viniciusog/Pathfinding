#ifndef STAR_H
#define STAR_H

#include <SFML/Graphics.hpp>
#include "iostream"
#include <vector>
#include <stdlib.h>
#include "Grid.h"
#include "windows.h"
#include "Node.h"
using namespace std;

class AStar
{
public:
    AStar(Grid *grid, sf::RenderWindow *w);
    ~AStar();
    bool nodeIsInTheList(vector<Node *> &list, Node *node) const;
    Node *getNodeLowestCost(int &position) const;
    vector<Node *> getNeighbours(Node *current) const;
    int getDistance(Node *nodeA, Node *nodeB) const;
    void reset();
    void clearOpenClosedList();
    void findPath(int startX, int startY, int endX, int endY);
    vector<Node *>getPath(Node *endNode) const;
    bool getPathFound() const;
    sf::RenderWindow* getWindow() const;

private:
    bool pathFound;
    Grid *grid;
    vector<Node *> openList;
    vector<Node *> closedList;
    sf::RenderWindow *wi;
};

#endif