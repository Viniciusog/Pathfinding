#include "AStar.h"

AStar::AStar(Grid *grid) {
    this->grid = grid;
}

AStar::~AStar() {

}

Node *AStar::getNodeLowestCost() const {
    if (openList.size() > 0) {
        Node *node = openList.at(0);
        for (int i = 1; i < openList.size(); i++) {
            if (openList.at(i)->getFCost() < node->getFCost()) {
                node = openList.at(i);
            }
        }
        return node;
    }
    return nullptr;
}

void AStar::findPath(int startX, int startY, int endX, int endY) {
    Node *start = grid->getNodeFromWorldPoint(startX, startY);
    Node *end = grid->getNodeFromWorldPoint(endX, endY);

    closedList.push_back(start);
    Node *current = getNodeLowestCost();
    //percorrer todos os vizinhos e adicionar na lista openList os vizinhos que não são paredes e que não estão em closedList;
    //pegar o node com o menor custo
    //Node *current =    
}