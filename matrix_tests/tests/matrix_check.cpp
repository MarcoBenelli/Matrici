//
// Created by marco on 05/09/18.
//

#include "gtest/gtest.h"

#include "Matrix.h"

class MatrixTest : public ::testing::Test {
protected:
    MatrixTest() : ::testing::Test(), M1(2, 3), M2(2, 3), M3(3, 2) {
        for (int i = 0; i < M1.getM(); ++i)
            for (int j = 0; j < M1.getN(); ++j) {
                M1.element(i, j) = i + j;
                M2.element(i, j) = i - j;
            }

        for (int i = 0; i < M3.getM(); ++i)
            for (int j = 0; j < M3.getN(); ++j)
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
    Matrix<int> expectedResult(M1.getM(), M1.getN());
    for (int i = 0; i < M1.getM(); ++i)
        for (int j = 0; j < M1.getN(); ++j) {
            expectedResult.element(i, j) = M1.element(i, j) + M2.element(i, j);
        }
    EXPECT_EQ(M1 + M2, expectedResult);
}

TEST_F(MatrixTest, ScalarMultiplication) {
    Matrix<int> expectedResult(M1.getM(), M1.getN());
    for (int i = 0; i < M1.getM(); ++i)
        for (int j = 0; j < M1.getN(); ++j) {
            expectedResult.element(i, j) = 2 * M1.element(i, j);
        }
    EXPECT_EQ(M1 * 2, expectedResult);
}

TEST_F(MatrixTest, Multiplication) {
    Matrix<int> expectedResult(M1.getM(), M3.getN());
    for (int i = 0; i < M1.getM(); ++i)
        for (int j = 0; j < M3.getN(); ++j) {
            expectedResult.element(i, j) = 0;
            for (int k = 0; k < M1.getN(); ++k)
                expectedResult.element(i, j) += M1.element(i, k) * M3.element(k, j);
        }
    EXPECT_EQ(M1 * M3, expectedResult);
}

TEST_F(MatrixTest, Trasposta) {
    Matrix<int> trasp(M1.getN(), M1.getM());
    trasp = M1.trasposta();
    for (int i = 0; i < M1.getM(); ++i)
        for (int j = 0; j < M1.getN(); ++j)
            EXPECT_EQ(M1.element(i, j), trasp.element(j, i));
}