#include <gtest/gtest.h>
#include "../Matrix/Matrix.hpp"

// struct Tests : public ::testing::Test
// {
//     virtual void SetUp() override
//     {
//         std::cout << "Setting Test Up!\n";
//     }
//     virtual void TearDown() override
//     {
//         std::cout << "Tearing Test Down!\n";
//     }
// };

TEST(Matrix_Tests, Constructor_test_1)
{
    // Default constructor
    {
        Matrix<double> matr;
        EXPECT_EQ(matr.height(), 0);
        EXPECT_EQ(matr.width(), 0);
    }

    // With basic value
    {
        Matrix<double> matr(2, 4, 2.5);
        EXPECT_EQ(matr.height(), 2);
        EXPECT_EQ(matr.width(), 4);
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < 4; ++j)
                EXPECT_DOUBLE_EQ(matr.at(i, j), 2.5);
    }
}

TEST(Matrix_Tests, Constructor_test_2)
{
    // Constructor from 2D array
    {
        double m[4][4] = {
            {5, -2, 2, 7},
            {1, 0, 0, 3},
            {-3, 1, 5, 0},
            {3, -1, -9, 4}
        };

        Matrix<double> matr(m);
        EXPECT_EQ(matr.height(), 4);
        EXPECT_EQ(matr.width(), 4);
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                EXPECT_EQ(matr.at(i, j), m[i][j]);
    }

    // Copy constructor
    {
        Matrix<double> mtr1(2, 3, 3.0);
        Matrix<double> mtr2(mtr1);
        mtr2.at(1, 1) = 4.0;
        EXPECT_EQ(mtr1.height(), mtr2.height());
        EXPECT_EQ(mtr1.width(), mtr2.width());

        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < 3; ++j)
                if(i != 1 || j != 1)
                    EXPECT_EQ(mtr1.at(i, j), mtr2.at(i, j));

        EXPECT_NE(mtr1.at(1, 1), mtr2.at(1, 1));
    }
}

TEST(Matrix_Tests, Transpose_test)
{
    double m[3][5] = {
        { 4, 6, 9, 2, 3 },
        { 4, 6, 4, 5, 8 },
        { 3, 8, 6, 3, 9 }
    };

    Matrix<double> base(m);
    Matrix<double> transposed = base.transpose();

    EXPECT_EQ(base.height(), transposed.width());
    EXPECT_EQ(base.width(), transposed.height());

    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 5; ++j)
            EXPECT_EQ(base.at(i, j), transposed.at(j, i));
}

TEST(Matrix_Tests, Submatrix_test)
{
    double m[3][5] = {
        { 4, 6, 9, 2, 3 },
        { 4, 6, 4, 5, 8 },
        { 3, 8, 6, 3, 9 }
    };
    
    Matrix<double> base(m);

    // No ecxeption call
    {
        double m_res[2][4] = {
            { 4, 9, 2, 3 },
            { 3, 6, 3, 9 }
        };

        Matrix<double> res = base.submatrix(1, 1);

        EXPECT_EQ(res, Matrix(m_res));
    }

    // Exception call
    {
        EXPECT_ANY_THROW(base.submatrix(15, 15));
    }
}

TEST(Matrix_Tests, Clear_test)
{
    double m[3][5] = {
        { 4, 6, 9, 2, 3 },
        { 4, 6, 4, 5, 8 },
        { 3, 8, 6, 3, 9 }
    };

    Matrix<double> res(m);
    res.clear();
    EXPECT_EQ(res, Matrix<double>());
}

TEST(Matrix_Tests, Determinant_test)
{
    // Exception call (non-square matrix)
    {
        double m[3][5] = {
            { 4, 6, 9, 2, 3 },
            { 4, 6, 4, 5, 8 },
            { 3, 8, 6, 3, 9 }
        };
        Matrix<double> base(m);

        EXPECT_ANY_THROW(base.determinant());
    }

    // No exception call
    {
        double m[4][4] = {
            {5, -2, 2, 7},
            {1, 0, 0, 3},
            {-3, 1, 5, 0},
            {3, -1, -9, 4}
        };
        Matrix<double> base(m);

        double res = base.determinant();
        EXPECT_EQ(res, 88.0);
    }
}

TEST(Matrix_Tests, Inverse_test)
{
    // Exception call (non-square matrix)
    {
        double m[3][5] = {
            { 4, 6, 9, 2, 3 },
            { 4, 6, 4, 5, 8 },
            { 3, 8, 6, 3, 9 }
        };
        Matrix<double> base(m);

        EXPECT_ANY_THROW(base.inverse());
    }

    // Exception call (zero-determinant matrix)
    {
        double m[3][3] = {
            { 1, 2, 1 },
            { 2, 4, -1 },
            { 3, 6, 0 }
        };
        Matrix<double> base(m);

        EXPECT_ANY_THROW(base.inverse());
    }

    // No exception call
    {
        double m[4][4] = {
            {5, -2, 2, 7},
            {1, 0, 0, 3},
            {-3, 1, 5, 0},
            {3, -1, -9, 4}
        };
        Matrix<double> base(m);

        Matrix<double> unary({
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        });

        EXPECT_EQ(base * base.inverse(), unary);
    }
}

TEST(Matrix_Tests, Sum_and_Diff_test)
{
    // Exception call (diff sizes)
    {
        Matrix<double> A({
            { 4, 6, 9, 2, 3 },
            { 4, 6, 4, 5, 8 },
            { 3, 8, 6, 3, 9 }
        });

        Matrix<double> B({
            { 1, 2, 1 },
            { 2, 4, -1 },
            { 3, 6, 0 }
        });

        EXPECT_ANY_THROW(A + B);
        EXPECT_ANY_THROW(A - B);
    }

    // No exception call
    {
        Matrix<double> A({
            {5, -2, 2, 7},
            {1, 0, 0, 3},
            {-3, 1, 5, 0},
            {3, -1, -9, 4}
        });

        Matrix<double> B1({
            {4, -2, 2, 7},
            {1, -1, 0, 3},
            {-3, 1, 4, 0},
            {3, -1, -9, 3}
        });

        Matrix<double> B2({
            {-4, 2, -2, -7},
            {-1, 1, 0, -3},
            {3, -1, -4, 0},
            {-3, 1, 9, -3}
        });


        Matrix<double> res({
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        });

        EXPECT_EQ(A - B1, res);
        EXPECT_EQ(A + B2, res);
    }
}

TEST(Matrix_Tests, Multiplication_test)
{
    // Exception call (size problem :))
    {
        Matrix<double> A({
            { 4, 6, 9, 2, 3 },
            { 4, 6, 4, 5, 8 },
            { 3, 8, 6, 3, 9 }
        });

        Matrix<double> B({
            { 1, 2, 1 },
            { 2, 4, -1 },
            { 3, 6, 0 }
        });

        EXPECT_ANY_THROW(A * B);
    }


    // No exception call
    {
        Matrix<double> A({
            { 1, 2, 1 },
            { 2, 4, -1 },
            { 3, 6, 0 }
        });

        Matrix<double> B({
            { 4, 6, 9, 2, 3 },
            { 4, 6, 4, 5, 8 },
            { 3, 8, 6, 3, 9 }
        });

        Matrix<double> res({
            { 15, 26, 23, 15, 28 },
            { 21, 28, 28, 21, 29 },
            { 36, 54, 51, 36, 57 }
        });

        EXPECT_EQ(A * B, res);
    }
}