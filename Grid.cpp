#include "Grid.h"

Grid::Grid(int unitSize, int screenWidth, int screenHeight) 
    : Matrix(screenHeight / unitSize, screenWidth / unitSize) {

    int lines = screenHeight / unitSize;
    int columns = screenWidth / unitSize;
    this->unitSize = unitSize;
    setWidth(screenWidth);
    setHeight(screenHeight);
}

Grid::~Grid() {
    cout << "Grid destructor" << endl;
}

void Grid::setUnitSize(int unitSize) {
    this->unitSize = unitSize;
}

void Grid::setWidth(int width) {
    this->width = width;
}

void Grid::setHeight(int height) {
    this->height = height;
}

void Grid::setStartPoint(Node *start) {
    this->start = start;
}

void Grid::setEndPoint(Node *end) {
    this->end = end;
}

int Grid::getWidth() const {
    return this->width;
}

Node *Grid::getStartPoint() const {
    return this->start;
}

Node *Grid::getEndPoint() const {
    return this->end;
}

int Grid::getHeight() const {
    return this->height;
}

int Grid::getUnitSize() const {
    return this->unitSize;
}

/**
 * @details Generate matrix of nodes
 */
void Grid::initGrid() {
    for (int i = 0; i < getLines(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            Node *node = new Node(j*unitSize, i*unitSize, false);
            add(node, i, j);
        }
    }
}

/**
 * @details Draw lines and nodes to the window
 */
void Grid::drawTo(sf::RenderWindow &window) const {
    cout << "draw to" << endl;
    /* DRAW NODES */
    for (int i = 0; i < getLines(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            Node *node = at(i, j);
            sf::RectangleShape rect;
            rect.setSize({(float) unitSize, (float) unitSize});
            rect.setPosition({(float)node->getX(), (float)node->getY()});
            if (node->isWall()) { 
                rect.setFillColor(sf::Color::Black);          
            } else {
                rect.setFillColor(sf::Color::Green);
            } 
           window.draw(rect);
        }
    } 

    /* DRAW LINES */
    sf::RectangleShape horizontalLine;
    for (int i = 0; i < getLines(); i++) {
        horizontalLine.setSize({(float) getWidth(), 1.0});
        horizontalLine.setPosition(0, i*unitSize);
        window.draw(horizontalLine);
    }

    sf::RectangleShape verticalLine;
    for(int i = 0; i < getColumns(); i++) {
        verticalLine.setSize({1.0,(float) getHeight()});
        verticalLine.setPosition({(float)i*unitSize, 0.0});
        window.draw(verticalLine);
    }

    //last vertical line
    verticalLine.setPosition({(float) window.getSize().x - 1, 1.0});
    window.draw(verticalLine);

    //last horizontal line
    horizontalLine.setPosition({0, (float) window.getSize().y - 1});
    window.draw(horizontalLine);

}

void Grid::setWall(int line, int column) {
    Node *node = at(line, column);
    if (node != nullptr) {
        node->setIsWall(true);
    } 
}

void Grid::setWalkable(int line, int column) {
    Node *node = at(line, column);
    if (node != nullptr) {
        node->setIsWall(false);
    }
}

void Grid::print() const {
    cout << "lines: " << getLines() << " Columns: " << getColumns() << endl;
    for (int i = 0; i < getLines(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            cout << "X:" << at(i,j)->getX() << ",Y:" << at(i,j)->getY();
            cout << " | ";
        }
        cout << endl;
    }
}

Node *Grid::getNodeFromWorldPoint(int x, int y) const {
    int column = x / unitSize;
    int line = y / unitSize;
    return at(line, column);
}