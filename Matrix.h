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
        void print() const;
        void realocate(int lines, int columns);
        int getLines() const;
        int getColumns() const;
    private:
        T** matrix;
        int lines;
        int columns;
        void deleteMatrix();
};

template<class T>
Matrix<T>::Matrix(int lines, int columns) {
    this->lines = lines;
    this->columns = columns;

    matrix = new T*[columns];
    for (int i = 0; i < columns; i++) {
        matrix[i] = new T[lines];
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
            cout << matrix[j][i] << " ";
        }
        cout << endl;
    }
}

template<class T>
void Matrix<T>::add(T element, int line, int column) {
    matrix[column][line] = element;
}

template<class T>
T Matrix<T>::at(int line, int column) const {
    return matrix[column][line];
}

template<class T>
void Matrix<T>::deleteMatrix() {
    for (int i = 0; i < columns; i++) {
        delete [] matrix[i];
    }
    delete [] this->matrix;
}

template <class T>
void Matrix<T>::realocate(int l, int c) {
    deleteMatrix();

    this->lines = l;
    this->columns = c;

    this->matrix = new T*[c];
    for (int i = 0; i < c; i++) {
        this->matrix[i] = new T[l];
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

#endif