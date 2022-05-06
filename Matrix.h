#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>
class Matrix {
    public:
        Matrix(int lines, int columns);
        ~Matrix();
        T at(int line, int column) const;
        void add(T element, int line, int column);
        virtual void print() const;
        void realocate(int lines, int columns);
        int getLines() const;
        int getColumns() const;
    private:
        T** matrix;
        int lines;
        int columns;
        void deleteMatrix();
        bool lineAndColValid(int line, int column) const;

};

template<class T>
Matrix<T>::Matrix(int lines, int columns) {
    this->lines = lines;
    this->columns = columns;

    matrix = new T*[lines];
    for (int i = 0; i < lines; i++) {
        matrix[i] = new T[columns];
    }
}

template<class T>
Matrix<T>::~Matrix() {
    deleteMatrix();
}

template<class T>
void Matrix<T>::print() const {
    for (int i = 0; i < lines; i++) {
        for ( int j = 0; j < columns; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

template<class T>
void Matrix<T>::add(T element, int line, int column) {
    if (lineAndColValid(line, column)) {
        matrix[line][column] = element;
    }
}

template<class T>
T Matrix<T>::at(int line, int column) const {
    if (lineAndColValid(line, column)) {
        return matrix[line][column];
    }
    return nullptr;   
}

template<class T>
void Matrix<T>::deleteMatrix() {
    for (int i = 0; i < lines; i++) {
        delete [] matrix[i];
    }
    delete [] this->matrix;
}

template <class T>
void Matrix<T>::realocate(int l, int c) {
    deleteMatrix();

    this->lines = l;
    this->columns = c;

    this->matrix = new T*[l];
    for (int i = 0; i < l; i++) {
        this->matrix[i] = new T[c];
    }
}

template<class T>
int Matrix<T>::getLines() const {
    return this->lines;
}

template<class T>
int Matrix<T>::getColumns() const {
    return this->columns;
}

template<class T>
bool Matrix<T>::lineAndColValid(int line, int column) const {
    return line >= 0 && line < this->lines && column >= 0 && column < this->getColumns();
}

#endif