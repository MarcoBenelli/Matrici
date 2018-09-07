//
// Created by marco on 05/09/18.
//

#include "gtest/gtest.h"

#include "Matrix.h"

class MatrixTest : public ::testing::Test {
protected:
    MatrixTest() : ::testing::Test(), M1(2, 3), M2(2, 3), M3(3, 2) {
        for (unsigned int i = 0, j; i < M1.getM(); ++i)
            for (j = 0; j < M1.getN(); ++j) {
                M1.element(i, j) = i + j;
                M2.element(i, j) = i - j;
            }

        for (unsigned int i = 0, j; i < M3.getM(); ++i)
            for (j = 0; j < M3.getN(); ++j)
                M3.element(i, j) = i + j;
    }

    Matrix<int> M1;
    Matrix<int> M2;
    Matrix<int> M3;
};

/*TEST(MatrixTest, Constructor) {
    int m = 2, n = 3;
    Matrix<int> M(m, n);
    EXPECT_EQ(M.getM(), m);
    EXPECT_EQ(M.getN(), n);
}*/

TEST_F(MatrixTest, Addition) {
    Matrix<int> sum{M1 + M2};
    for (unsigned int i = 0, j; i < M1.getM(); ++i)
        for (j = 0; j < M1.getN(); ++j)
            EXPECT_EQ(sum.element(i, j), M1.element(i, j) + M2.element(i, j));
}

TEST_F(MatrixTest, ScalarMultiplication) {
    Matrix<int> scaled{M1 * 2};
    for (unsigned int i = 0, j; i < M1.getM(); ++i)
        for (j = 0; j < M1.getN(); ++j)
            EXPECT_EQ(scaled.element(i, j), 2 * M1.element(i, j));
}

TEST_F(MatrixTest, Multiplication) {
    Matrix<int> product{M1 * M3};
    for (unsigned int i = 0, j, k, s; i < M1.getM(); ++i)
        for (j = 0; j < M3.getN(); ++j) {
            s = 0;
            for (k = 0; k < M1.getN(); ++k)
                s += M1.element(i, k) * M3.element(k, j);
            EXPECT_EQ(product.element(i, j), s);
        }
}

TEST_F(MatrixTest, Transpose) {
    Matrix<int> tr{M1.transpose()};
    for (unsigned int i = 0, j; i < M1.getM(); ++i)
        for (j = 0; j < M1.getN(); ++j)
            EXPECT_EQ(M1.element(i, j), tr.element(j, i));
}