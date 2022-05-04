#include "Node.h"
using namespace std;
#include <iostream>
#include "Matrix.h"
#include "Grid.h"

int main() {
/*     Grid g(60, 600);
    g.initGrid();
    g.print();
 */ 
    int lines = 5;
    int columns = 5;

    Grid g(60, 600);
    g.initGrid();
    g.print();
    
    /*Matrix<int> matrix(lines, columns);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            matrix.add(i*j, i, j);
        }
    }

    matrix.print();
    cout << endl;

    lines = 8;
    columns = 8;

    matrix.realocate(lines, columns);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            matrix.add(i * j, i, j);
        }
    }

    matrix.print();
    */
}