#ifndef GRID_H
#define GRID_H

#include <iostream>
using namespace std;
#include <vector>
#include "Node.h"
#include "Matrix.h"

class Grid {
    public:
        Grid(int unitSize, int screenSize);
        ~Grid();
        void initGrid();
        void setUnitSize(int unitSize);
        void setLines(int lines);
        void setColumns(int columns);
        int getUnitSize() const;
        int getLines() const;
        int getColumns() const;
        void print() const;
    private:
        int unitSize;
        Matrix<Node *> *nodes;
};

#endif