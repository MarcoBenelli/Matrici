//
// Created by marco on 21/07/18.
//

#ifndef MATRICI_MATRIX_H
#define MATRICI_MATRIX_H


#include <iostream>

#include <stdexcept>

template<typename T>
class Matrix {
public:
    Matrix(unsigned int m, unsigned int n);

    virtual ~Matrix() {
        delete[] buffer;
    }

    T &element(unsigned int i, unsigned int j) const {
        if (i >= m)
            throw std::out_of_range("i >= m");
        if (j >= n)
            throw std::out_of_range("j >= n");
        return buffer[i * n + j];
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &M) {
        for (unsigned int i = 0, j; i < M.m; ++i) {
            for (j = 0; j < M.n; ++j)
                std::cout << M.element(i, j) << " ";
            std::cout << std::endl;
        }
    }

    Matrix(const Matrix &original);

    Matrix<T> &operator=(const Matrix &right);

    unsigned int getM() const {
        return m;
    }

    unsigned int getN() const {
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

    Matrix<T> slice(unsigned int iMin, unsigned int jMin, unsigned int iMax, unsigned int jMax) const;

    Matrix<T> transpose() const;

private:
    unsigned int m, n;
    T *buffer;

    void copy(const Matrix &that);
};

template<typename T>
Matrix<T>::Matrix(unsigned int m, unsigned int n) {
    if (m <= 0)
        throw std::domain_error("m <= 0");
    if (n <= 0)
        throw std::domain_error("n <= 0");
    this->m = m;
    this->n = n;
    buffer = new T[m * n];
}

template<typename T>
//This warning is wrong
Matrix<T>::Matrix(const Matrix &original) : Matrix(original.m, original.n) {
    copy(original);
}

template<typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &right) {
    delete[] buffer;
    m = right.m;
    n = right.n;
    buffer = new T[m * n];
    copy(right);
    return *this;
}

template<typename T>
void Matrix<T>::copy(const Matrix &that) {
    for (unsigned int i = 0, j; i < m; ++i)
        for (j = 0; j < n; ++j)
            element(i, j) = that.element(i, j);
}

template<typename T>
bool Matrix<T>::operator==(const Matrix &right) const {
    if (m != right.m || n != right.n)
        return false;
    for (unsigned int i = 0, j; i < m; ++i)
        for (j = 0; j < n; ++j)
            if (element(i, j) != right.element(i, j))
                return false;
    return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &right) const {
    if (m != right.m)
        throw std::logic_error("m1 != m2");
    if (n != right.n)
        throw std::logic_error("n1 != n2");
    Matrix ans{m, n};
    for (unsigned int i = 0, j; i < m; ++i)
        for (j = 0; j < n; ++j)
            ans.element(i, j) = element(i, j) + right.element(i, j);
    return ans;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T scalar) const {
    Matrix ans{m, n};
    for (unsigned int i = 0, j; i < m; ++i)
        for (j = 0; j < n; ++j)
            ans.element(i, j) = scalar * element(i, j);
    return ans;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &right) const {
    if (n != right.m)
        throw std::logic_error("n1 != m2");
    Matrix ans{m, right.n};
    for (unsigned int i = 0, j, k; i < m; ++i)
        for (j = 0; j < right.n; ++j) {
            ans.element(i, j) = 0;
            for (k = 0; k < n; ++k)
                ans.element(i, j) += element(i, k) * right.element(k, j);
        }
    return ans;
}

template<typename T>
Matrix<T> Matrix<T>::slice(unsigned int iMin, unsigned int jMin, unsigned int iMax, unsigned int jMax) const {
    //i min sono compresi, i max no
    if (iMax > m)
        throw std::out_of_range("iMax > m");
    if (jMax > n)
        throw std::out_of_range("jMax > n");
    if (iMin >= iMax)
        throw std::logic_error("iMin >= iMax");
    if (jMin >= jMax)
        throw std::logic_error("jMin >= jMax");
    Matrix ans{iMax - iMin, jMax - jMin};
    for (unsigned int i = 0, j; i < ans.m; ++i)
        for (j = 0; j < ans.n; ++j)
            ans.element(i, j) = element(iMin + i, jMin + j);
    return ans;
}

template<typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix ans{n, m};
    for (unsigned int i = 0, j; i < m; ++i)
        for (j = 0; j < n; ++j)
            ans.element(j, i) = element(i, j);
    return ans;
}


#endif //MATRICI_MATRIX_H
