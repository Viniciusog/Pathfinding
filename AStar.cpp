#include "AStar.h"

AStar::AStar(Grid *grid) {
    this->grid = grid;
}

AStar::~AStar() {

}

/*
1 = openList
0 = closedList
*/
bool AStar::nodeIsInTheList(vector<Node *> &list, Node *node) const {
    for (int i = 0; i < (int) list.size(); i++) {
        if (*list.at(i) == *node) {
            return true;
        }
    }
    return false;
}

Node *AStar::getNodeLowestCost(int &position) const {
    if (openList.size() > 0) {
        Node *node = openList.at(0);
        for (int i = 1; i < openList.size(); i++) {
            // if f costs are equal, then look for the lowest h cost
            if (openList.at(i)->getFCost() < node->getFCost() || 
            openList.at(i)->getFCost() == node->getFCost() && openList.at(i)->getHCost() < node->getHCost()) {
                node = openList.at(i);
                position = i;
            }
        }
        return node;
    }
    position = NULL;
    return nullptr;
}

vector<Node *> AStar::getNeighbours(Node *current) const {
    vector<Node *> neighbours;

    //3x3 blocks
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            //not include the current node
            if (!(x == 0 && y == 0)) {
                int realX = current->getX() + x*grid->getUnitSize();
                int realY = current->getY() + y*grid->getUnitSize();

                // if coordinates is not valid, then neighbour will be nullptr
                // we can just add a verification before getting the node (future impl)
                Node *neighbour = grid->getNodeFromWorldPoint(realX, realY);
                if (neighbour != nullptr && !neighbour->isWall()) {
                    neighbours.push_back(neighbour);
                }             
            }
        }
    }
    return neighbours;
}


void AStar::findPath(int startX, int startY, int endX, int endY) {
    Node *start = grid->getNodeFromWorldPoint(startX, startY);
    Node *end = grid->getNodeFromWorldPoint(endX, endY);

    openList.push_back(start);

    while (openList.size() > 0) {
        int position;
        Node *current = getNodeLowestCost(position);
        if (position != NULL) {
            openList.erase(openList.begin() + position);
        }
        closedList.push_back(current);

        if (current == end) {
            continue;
        }

        vector<Node *> neighbours = getNeighbours(current);
        for (int i = 0; i < neighbours.size(); i++) {
            Node *neighbour = neighbours.at(i);

            // estou na dúvida se assim funciona ou se tem que passar como sendo ponteiro;
            if (neighbour->isWall() || nodeIsInTheList(openList, neighbour)) {

            }
        }
    } 
}