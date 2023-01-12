#include "AStar.h"
#include "cmath"

AStar::AStar(Grid *grid, sf::RenderWindow *wi) {
    this->grid = grid;
    this->wi = wi;
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

bool AStar::getPathFound() const {
    return this->pathFound;
}

Node *AStar::getNodeLowestCost(int &position) const {
    if (openList.size() > 0) {
        Node *node = openList.at(0);
        position = 0;
        //cout << "openList size: " << openList.size() << endl;
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
    position = -1;
    return nullptr;
}

vector<Node *> AStar::getNeighbours(Node *current) const {
    vector<Node *> neighbours;

    //3x3 blocks
    for (int y = -1; y <= 1; y++) { //for each line
        for (int x = -1; x <= 1; x++) { // for each column
            //not include the current node
            if (!(x == 0 && y == 0)) {
                int realX = current->getX() + x*grid->getUnitSize();
                int realY = current->getY() + y*grid->getUnitSize();

                // if coordinates are not valid, then neighbour will be nullptr
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

// executed when reset key is pressed
void AStar::clearOpenClosedList() {
    for (int i = 0; i < openList.size(); i++) {
        openList.at(i)->setParent(nullptr);
    }
    for (int i = 0; i < closedList.size(); i++) {
        closedList.at(i)->setParent(nullptr);
    }
    openList.clear();
    closedList.clear();
}

int AStar::getDistance(Node *nodeA, Node *nodeB) const {
    int x, y;
    x = abs(nodeA->getX() - nodeB->getX());
    y = abs(nodeA->getY() - nodeB->getY());

    int unitSize = grid->getUnitSize();

    if (x > y) {
        //14y + 10(x-y)
        return y/unitSize * 14 + (x-y)/unitSize * 10;
    } 
    //14x + 10(y-x)
    return x/unitSize * 14 + (y-x)/unitSize * 10;
}

void AStar::reset() {
    this->pathFound = false;
    clearOpenClosedList();
}


sf::RenderWindow * AStar::getWindow() const {
    return this->wi;
}

void AStar::findPath(int startX, int startY, int endX, int endY) {
    Node *start = grid->getNodeFromWorldPoint(startX, startY);
    Node *end = grid->getNodeFromWorldPoint(endX, endY);

    /* cout << "is end a wall:" << end->isWall() << endl;
    int co;
    cin >> co; */

    /* cout << *start << endl;
    cout << *end << endl;
    int continuar;
    cout << "Continuar?" << endl;
    cin >> continuar; */

    openList.push_back(start);

    while (openList.size() > 0) {
        int position;
        Node *current = getNodeLowestCost(position);
        /* cout << "[";
        for (int i = 0; i < openList.size(); i++) {
            cout << openList.at(i)->getHCost() << ", ";
        }
        cout << "]" << endl;
        cout << "Position: " << position << endl; */
        if (position != -1) {
            openList.erase(openList.begin() + position);
        }

        closedList.push_back(current);
        this->grid->drawFindingPath(openList, closedList, *getWindow());

        if (*current == *end) {
            cout << "ENCONTROU O LOCAL---------------------------------------------" << endl;
            pathFound = true;
            break;
        }

        vector<Node *> neighbours = getNeighbours(current);
        /* cout << "Vizinhos: " << neighbours.size() << endl; */
        /* cout << "QTD VIZINHOS: " << neighbours.size() << endl;
        cout << "Current h cost: " << current->getHCost() << endl; */
        for (int i = 0; i < neighbours.size(); i++) {
            //cout << endl << "PROCESSANDO NODE " << i << endl;
            Node *neighbour = neighbours.at(i);

            if (neighbour->isWall() || nodeIsInTheList(closedList, neighbour)) {
                continue;
            }

            // calculate the new g cost if the new path to the node is shorter
            int gCostToNeighbour = current->getGCost() + getDistance(current, neighbour);
            if (!nodeIsInTheList(openList, neighbour) || gCostToNeighbour < neighbour->getGCost()) {
                neighbour->setG(gCostToNeighbour);
                neighbour->setH(getDistance(neighbour, end));
                neighbour->setParent(current);

                if (!nodeIsInTheList(openList, neighbour)) {
                    openList.push_back(neighbour);
                }
            }
        } 
    }  
    pathFound = true;
}

vector<Node *> AStar::getPath(Node *endNode) const {
    vector<Node *> path;
    vector<Node*> reversedPath;

    Node *current = endNode;
    if (endNode != nullptr) {
        current = current->getParent();
    }

    while (current != nullptr && current->getParent() != nullptr) {
        path.push_back(current);
        current = current->getParent();
    }

    for (int i = path.size() - 1; i >= 0; i--) {
        reversedPath.push_back(path.at(i));
    }

    /* cout << "getPath - fim" << endl;    */
    //cout << "Path size: " << reversedPath.size() << endl;
    return reversedPath;
}