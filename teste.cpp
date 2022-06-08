#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Matrix.h"
using namespace std;

vector<string> split(string str, string separator) {
    int indexStart = 0;
    int indexChar;
    indexChar = str.find(separator);

    // just not to search always the same char in the string
    string charToReplace = separator == "|" ? "." : "|";

    vector<string> list;
    while (indexChar != std::string::npos) {
        string part = str.substr(indexStart, indexChar-indexStart);
        cout << part << endl;
        list.push_back(part);
        indexStart = indexChar + 1;
        str.replace(indexChar, 1, charToReplace);
        indexChar = str.find(separator);
    }

    string lastPart = str.substr(indexStart);
    cout << lastPart << endl;
    list.push_back(lastPart);
    return list;
}

void save(int **&matrix, int lines, int columns) {
    ofstream file("saida.txt");
    int value;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            value = matrix[i][j];
            if (j == columns - 1) {
               file << value;  
            } else {
                file << value << ",";
            } 
        }
        file << endl;
    }
}
/* 
void save(Matrix<int> &matrix) {
    for (int i = 0; i < matrix.getLines(); i++) {
        for (int j = 0; j < matrix.getColumns(); j++) {
            if (matrix.at(i, j) != NULL) {
                int valor = matrix.at(i, j);
            }
        }
    }
} */

int main() {

    int **matrix = new int*[4];
    for (int i = 0; i < 4; i++) {
        matrix[i] = new int[4];
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = j % 2 == 0 ? 1 : 0;
        }
    }

    save(matrix, 4, 4);


    ifstream myFile("saida.txt");
    std::string myLine;
    int indexChar;
    int indexStart = 0;
    while (myFile.good()) {
        myFile >> myLine;
        //getline(myFile, myLine);
        
        vector<string> list = split(myLine, ",");
    }
}