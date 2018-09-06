#include "matrix/Matrix.h"
#include "matrix/Factory.h"

int main() {
    /*
    int m1, n1;
    m1 = 2;
    n1 = 3;
    Matrix<int> M1(m1, n1);
    for (int i = 0; i < m1; ++i)
        for (int j = 0; j < n1; ++j)
            M1.element(i, j) = 1;
    Matrix<int> M2(m1, n1);
    for (int i = 0; i < m1; ++i)
        for (int j = 0; j < n1; ++j)
            M2.element(i, j) = 2;
    M1.print();
    M2.print();
    Matrix<int> M3(M1);
    M3.print();
    M2 = M1;
    M2.print();
    M3 = M1 + M2;
    std::cout << std::endl;
    M3.print();
    (M1 * 2).print();
    std::cout << std::endl;
    std::cout << "prodotto" << std::endl;
    int m2, n2;
    m2 = 3;
    n2 = 2;
    Matrix<int> M4(m2, n2);
    M4.element(0, 0) = 1;
    M4.element(0, 1) = 2;
    M4.element(1, 0) = 3;
    M4.element(1, 1) = 4;
    M4.element(2, 0) = 5;
    M4.element(2, 1) = 6;
    M1.print();
    std::cout << std::endl;
    M4.print();
    std::cout << std::endl;
    auto M5 = M4 * M1;
    M5.print();
    std::cout << std::endl << "trasposta" << std::endl;
    M4.trasposta().print();
    std::cout << std::endl << "meno" << std::endl;
    M1 = -M4;
    M4.print();
    M1.print();
    (M4 - M1).print();
    M1 += M4;
    M1.print();
     */
    Factory<float> factory1;
    Matrix<float> M2(factory1.createMatrix(5, 6));
    float k = 0;
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 6; ++j)
            M2.element(i, j) = ++k;
    M2.print();
    Matrix<float> M3(M2.slice(1, 1, 3, 4));
    M3.print();
    (-M3).print();
    return 0;
}