#include "Grid.h"

Grid::Grid(int unitSize, int screenSize) {
    int lines = screenSize / unitSize;
    int columns = screenSize / unitSize;

    this->nodes = new Matrix<Node *>(lines, columns);
    this->unitSize = unitSize;
}

Grid::~Grid() {
    delete nodes;
    cout << "" << endl;
}

void Grid::setUnitSize(int unitSize) {
    this->unitSize = unitSize;
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

void Grid::initGrid() {
    for (int i = 0; i < this->getLines(); i++) {
        for (int j = 0; j < this->getColumns(); j++) {
            Node *node = new Node(i*unitSize, j*unitSize, false);
            nodes->add(node, i, j);
        }
    }
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