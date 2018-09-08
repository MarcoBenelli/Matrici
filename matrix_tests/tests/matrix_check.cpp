//
// Created by marco on 05/09/18.
//

#include "gtest/gtest.h"
#include "Matrix.h"

class MatrixTest : public ::testing::Test {
protected:
    MatrixTest() : ::testing::Test(), M1(2, 3), M2(2, 3), M3(3, 4) {
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

TEST_F(MatrixTest, Addition) {
    Matrix<int> sum{M1 + M2};
    for (unsigned int i = 0, j; i < M1.getM(); ++i)
        for (j = 0; j < M1.getN(); ++j)
            EXPECT_EQ(sum.element(i, j), M1.element(i, j) + M2.element(i, j)) << "i = " << i << ", j = " << j;
}

TEST_F(MatrixTest, ScalarMultiplication) {
    Matrix<int> scaled{M1 * 2};
    for (unsigned int i = 0, j; i < M1.getM(); ++i)
        for (j = 0; j < M1.getN(); ++j)
            EXPECT_EQ(scaled.element(i, j), 2 * M1.element(i, j)) << "i = " << i << ", j = " << j;
}

TEST_F(MatrixTest, Multiplication) {
    Matrix<int> product{M1 * M3};
    for (unsigned int i = 0, j, k, s; i < M1.getM(); ++i)
        for (j = 0; j < M3.getN(); ++j) {
            s = 0;
            for (k = 0; k < M1.getN(); ++k)
                s += M1.element(i, k) * M3.element(k, j);
            EXPECT_EQ(product.element(i, j), s) << "i = " << i << ", j = " << j;
        }
}

TEST_F(MatrixTest, Transpose) {
    Matrix<int> tr{M1.transpose()};
    for (unsigned int i = 0, j; i < M1.getM(); ++i)
        for (j = 0; j < M1.getN(); ++j)
            EXPECT_EQ(M1.element(i, j), tr.element(j, i)) << "i = " << i << ", j = " << j;
}

TEST(MatrixConstructorExceptionTest, ConstructorHandles0) {
    EXPECT_THROW(Matrix<int> M1(0, 1), std::domain_error);
    EXPECT_THROW(Matrix<int> M1(1, 0), std::domain_error);
    EXPECT_THROW(Matrix<int> M1(0, 0), std::domain_error);
    EXPECT_NO_THROW(Matrix<int> M1(1, 1));
}

class MatrixExceptionTest : public ::testing::Test {
protected:
    MatrixExceptionTest() : ::testing::Test(), M1(2, 3), M2(2, 4), M3(3, 3) {}

    Matrix<int> M1, M2, M3;
};

TEST_F(MatrixExceptionTest, ElementOutside) {
    EXPECT_THROW(M1.element(M1.getM(), 0), std::out_of_range);
    EXPECT_THROW(M1.element(0, M1.getN()), std::out_of_range);
    EXPECT_NO_THROW(M1.element(M1.getM() - 1, M1.getN() - 1));
}

TEST_F(MatrixExceptionTest, Addition) {
    EXPECT_THROW(M1 + M2, std::logic_error);
    EXPECT_THROW(M1 + M3, std::logic_error);
    EXPECT_NO_THROW(M1 + M1);
}

//The errors are wrong
TEST_F(MatrixExceptionTest, Multiplication) {
    EXPECT_THROW(M1 * M2, std::logic_error);
    EXPECT_NO_THROW(M1 * M3);
}

TEST_F(MatrixExceptionTest, Slice) {
    EXPECT_THROW(M1.slice(0, 0, M1.getM() + 1, 1), std::out_of_range);
    EXPECT_THROW(M1.slice(0, 0, 1, M1.getN() + 1), std::out_of_range);
    EXPECT_THROW(M1.slice(0, 0, 0, 1), std::logic_error);
    EXPECT_THROW(M1.slice(0, 0, 1, 0), std::logic_error);
    EXPECT_NO_THROW(M1.slice(0, 0, 1, 1));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}