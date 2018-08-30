//
// Created by marco on 21/07/18.
//

#ifndef MATRICI_MATRIX_H
#define MATRICI_MATRIX_H


#include <iostream>

template<typename T>
class Matrix {
public:
    Matrix(int m, int n) : m(m), n(n), buffer(new T[m * n]) {}

    virtual ~Matrix() {
        delete[] buffer;
    }

    T &element(int i, int j) const {
        return buffer[i * n + j];
    }

    void print() const;

    Matrix(const Matrix &original);

    Matrix<T> &operator=(const Matrix &right);

    int getM() const {
        return m;
    }

    int getN() const {
        return n;
    }

    bool operator==(const Matrix &right) const;

    bool operator!=(const Matrix &right) const {
        return !(*this == right);
    }

    Matrix<T> operator+(const Matrix &right) const;

    Matrix<T> operator+=(const Matrix &right) {
        return *this = *this + right;
    }

    Matrix<T> operator*(T scalar) const;

    Matrix<T> operator*=(T scalar) {
        return *this = *this * scalar;
    }

    Matrix<T> operator-() const {
        return *this * -1;
    }

    Matrix<T> operator-(const Matrix &right) const {
        return *this + -right;
    }

    Matrix<T> operator-=(const Matrix &right) {
        return *this = *this - right;
    }

    Matrix<T> operator*(const Matrix &right) const;

    Matrix<T> operator*=(const Matrix &right) {
        return *this = *this * right;
    }

    Matrix<T> slice(int iMin, int jMin, int iMax, int jMax) const;

    Matrix<T> trasposta() const;

private:
    int m, n;
    T *buffer;

    void copy(const Matrix &that);
};

template<typename T>
void Matrix<T>::print() const {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << element(i, j) << " ";
        std::cout << std::endl;
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix &original) : Matrix(original.m, original.n) {
    copy(original);
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &right) {
    delete[] buffer;
    m = right.m;
    n = right.n;
    buffer = new T(m * n);
    copy(right);
    return *this;
}

template<typename T>
void Matrix<T>::copy(const Matrix &that) {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            element(i, j) = that.element(i, j);
}

template<typename T>
bool Matrix<T>::operator==(const Matrix &right) const {
    if (m != right.m || n != right.n)
        return false;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (element(i, j) != right.element(i, j))
                return false;
    return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &right) const {
    Matrix ans(m, n);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            ans.element(i, j) = element(i, j) + right.element(i, j);
    return ans;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const {
    Matrix ans(m, n);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            ans.element(i, j) = scalar * element(i, j);
    return ans;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &right) const {
    Matrix ans(m, right.n);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < right.n; ++j) {
            ans.element(i, j) = 0;
            for (int k = 0; k < n; ++k)
                ans.element(i, j) += element(i, k) * right.element(k, j);
        }
    return ans;
}

template<typename T>
Matrix<T> Matrix<T>::slice(int iMin, int jMin, int iMax, int jMax) const {
    //i min sono compresi, i max no
    Matrix ans(iMax - iMin, jMax - jMin);
    for (int i = 0; i < ans.m; ++i)
        for (int j = 0; j < ans.n; ++j)
            ans.element(i, j) = element(iMin + i, jMin + j);
    return ans;
}

template<typename T>
Matrix<T> Matrix<T>::trasposta() const {
    Matrix ans(n, m);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            ans.element(j, i) = element(i, j);
    return ans;
}


#endif //MATRICI_MATRIX_H
