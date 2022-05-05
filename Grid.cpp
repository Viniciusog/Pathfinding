#include "Grid.h"

Grid::Grid(int unitSize, int screenWidth, int screenHeight) {
    int lines = screenHeight / unitSize;
    int columns = screenWidth / unitSize;

    this->nodes = new Matrix<Node *>(lines, columns);
    this->unitSize = unitSize;
    setWidth(screenWidth);
    setHeight(screenHeight);
}

Grid::~Grid() {
    delete nodes;
    cout << "" << endl;
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

int Grid::getWidth() const {
    return this->width;
}

int Grid::getHeight() const {
    return this->height;
}

int Grid::getColumns() const {
    return nodes->getColumns();
}

int Grid::getLines() const {
    return nodes->getLines();
}

int Grid::getUnitSize() const {
    return this->unitSize;
}

/**
 * @details Generate matrix of nodes
 */
void Grid::initGrid() {
    for (int i = 0; i < this->getLines(); i++) {
        for (int j = 0; j < this->getColumns(); j++) {
            Node *node = new Node(i*unitSize, j*unitSize, false);
            nodes->add(node, i, j);
        }
    }
}

/**
 * @details Draw lines and nodes to the window
 */
void Grid::drawTo(sf::RenderWindow &window) const {
    /* DRAW NODES */
    for (int i = 0; i < getLines(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            Node *node = nodes->at(i, j);
            sf::RectangleShape  rect;
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
    nodes->at(line, column)->setIsWall(true);
}


void Grid::print() const {
    cout << "lines: " << getLines() << " Columns: " << getColumns() << endl;
    for (int i = 0; i < getLines(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            cout << "X:" << nodes->at(i,j)->getX() << ",Y:" <<  nodes->at(i,j)->getY();
            cout << " | ";
        }
        cout << endl;
    }
}