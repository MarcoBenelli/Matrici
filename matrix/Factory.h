//
// Created by marco on 19/08/18.
//

#ifndef MATRICI_FACTORY_H
#define MATRICI_FACTORY_H


#include "Matrix.h"

template<typename T>
class Factory {
public:
    Matrix<T> createMatrix(unsigned int m, unsigned int n) {
        Matrix<T> matrix{m, n};
        return matrix;
    }
};


#endif //MATRICI_FACTORY_H
