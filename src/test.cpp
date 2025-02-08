#include <gtest/gtest.h>
#include "TDMatrix.h"
#include <sstream>


TEST(TDMatrixIOTest, OutputTest) {
    TDMatrix<int> matrix({2, 3}, {10, 20, 30}, {1, 2});

    std::ostringstream oss;
    oss << matrix;

    std::string expected_output = "2 3 \n10 20 30 \n1 2 \n";
    EXPECT_EQ(oss.str(), expected_output);
}

TEST(TDMatrixIOTest, InputTest) {
    std::istringstream iss("3\n2 3\n10 20 30\n1 2\n");

    TDMatrix<int> matrix;
    iss >> matrix;
    std::ostringstream oss;
    oss << matrix;

    std::string expected_output = "2 3 \n10 20 30 \n1 2 \n";

    EXPECT_EQ(oss.str(), expected_output);

}

// Тестовый случай для проверки выброса исключения при отсутствии диагонального преобладания
TEST(ThreeDiagProgTest, NoDiagonalDominance) {
    // Создание трёхдиагональной матрицы без диагонального преобладания
    std::vector<double> up = {2.0}; // Верхняя диагональ
    std::vector<double> middle = {1.0, 1.0}; // Главная диагональ
    std::vector<double> down = {2.0}; // Нижняя диагональ

    TDMatrix<double> A(up, middle, down);
    std::vector<double> d = {3.0, 3.0}; // Правая часть

    // Проверяем, что выбрасывается исключение
    EXPECT_THROW(three_diag_prog(A, d), std::runtime_error);
}

// Тестовый случай для проверки на нулевую матрицу
TEST(ThreeDiagProgTest, ZeroMatrix) {
    // Создание трёхдиагональной матрицы с нулевыми элементами на главной диагонали
    std::vector<double> up = {1.0}; // Верхняя диагональ
    std::vector<double> middle = {0.0, 0.0}; // Главная диагональ (нулевая)
    std::vector<double> down = {1.0}; // Нижняя диагональ

    TDMatrix<double> A(up, middle, down);
    std::vector<double> d = {1.0, 1.0}; // Правая часть

    // Проверяем, что выбрасывается исключение
    EXPECT_THROW(three_diag_prog(A, d), std::runtime_error);
}

// Тестовый случай для проверки решения с отрицательными значениями
TEST(ThreeDiagProgTest, NegativeValues) {
    // Создание трёхдиагональной матрицы с отрицательными значениями
    std::vector<double> up = {-1.0, 1.0}; // Верхняя диагональ
    std::vector<double> middle = {-4.0, -4.0, -4.0}; // Главная диагональ
    std::vector<double> down = {-1.0, 1.0}; // Нижняя диагональ

    TDMatrix<double> A(up, middle, down);
    std::vector<double> d = {-5.0, -6.0, -7.0}; // Правая часть

    // Ожидаемое решение (положительное)
    std::vector<double> expected = {11/14.0, 13/7.0, 31.0/14};

    // Получаем решение
    std::vector<double> result = three_diag_prog(A, d);

    // Проверяем результат
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_NEAR(result[i], expected[i], 1e-5);
    }
}

TEST(TDMatrixTest, GetSize) {
    std::vector<int> up = {0, 1};
    std::vector<int> middle = {3, 4, 5};
    std::vector<int> down = {6, 7};

    TDMatrix<int> matrix(up, middle, down);


    EXPECT_EQ(matrix.get_size(), 3);
}


TEST(TDMatrixTest, DefaultConstructorGetSize) {
    TDMatrix<int> matrix;


    EXPECT_EQ(matrix.get_size(), 0);
}



TEST(TDMatrixTest, ValidConstructor) {
    std::vector<int> up = {2, 3};
    std::vector<int> middle = {1, 2, 3};
    std::vector<int> down = {4, 5};


    EXPECT_NO_THROW(TDMatrix<int> matrix(up, middle, down));
}


TEST(TDMatrixTest, InvalidUpSize) {
    std::vector<int> up = {2, 3, 4};
    std::vector<int> middle = {1, 2, 3};
    std::vector<int> down = {4, 5};


    EXPECT_THROW(TDMatrix<int> matrix(up, middle, down), std::invalid_argument);
}


TEST(TDMatrixTest, InvalidDownSize) {
    std::vector<int> up = {2, 3};
    std::vector<int> middle = {1, 2, 3};
    std::vector<int> down = {4, 5, 6};


    EXPECT_THROW(TDMatrix<int> matrix(up, middle, down), std::invalid_argument);
}


TEST(TDMatrixTest, InvalidMiddleSize) {
    std::vector<int> up = {2};
    std::vector<int> middle = {1};
    std::vector<int> down = {};


    EXPECT_THROW(TDMatrix<int> matrix(up, middle, down), std::invalid_argument);
}
TEST(TDProgTest, NaNInSolution) {
    TDMatrix<double> matrix({1,1},{0,0,0},{9,9});
    std::vector<double> d = {1,2,3};
    EXPECT_THROW({
        three_diag_prog(matrix,d);
    }, std::runtime_error);
}
/*
TEST(TDProgTest, RightSolution1) {
    TDMatrix<double> matrix({2,1,4},{1,1,2,1},{1,1,1});
    std::vector<double> d = {1,1,2,5};
    std::vector<double> expected = {-35,18,18,-13};

    std::vector<double> solution = three_diag_prog(matrix, d);
    double tolerance = 1e-6;
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_NEAR(solution[i], expected[i], tolerance);
  }
}*/
TEST(TDProgTest, RightSolution2) {
    TDMatrix<double> matrix({0,0,0},{1,1,1,1},{0,0,0});
    std::vector<double> d = {1,1,2,5};
    std::vector<double> expected = {1,1,2,5};

    std::vector<double> solution = three_diag_prog(matrix, d);
    double tolerance = 1e-6;
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_NEAR(solution[i], expected[i], tolerance);
    }
}

// Запуск всех тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}