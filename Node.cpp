#include "Node.h"

Node::Node(int x, int y, bool isWall) {
    this->x = x;
    this->y = y;
    this->wall = isWall;
}

Node::~Node() {
    delete parent;
}

void Node::setX(const int x) {
    this->x =x;
}

void Node::setY(const int y) {
    this->y = y;
}

void Node::setParent(Node *parent) {
    this->parent = parent;
}

void Node::setG(const int g) {
    this->g = g;
}

void Node::setH(const int h) {
    this->h  = h;
}

void Node::setIsWall(bool isWall) {
    this->wall = isWall;
}

int Node::getX() const {
    return x;
}

int Node::getY() const {
    return y;
}

int Node::getF() const {
    //tem um outro or para ser considerado
    return g + h;
}

Node* Node::getParent() const {
    return this->parent;
}

bool Node::isWall() const {
    return wall;
}     