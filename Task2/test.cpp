#include <gtest/gtest.h>
#include <chrono>
#include "matrix.h" 
#include <random>    // Добавлено для генерации случайных чисел
#include <algorithm>
// Функция для генерации случайной плотной матрицы
Matrix<double> generateDenseMatrix(size_t rows, size_t cols) {
    Matrix<double> mat(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            mat(i, j) = static_cast<double>(rand()) / RAND_MAX; // Заполнение случайными числами
        }
    }
    return mat;
}

// Функция для генерации случайной CSR-матрицы
CSRMatrix<double> generateCSRMatrix(size_t rows, size_t cols, size_t nonZeros) {
    std::map<std::pair<size_t, size_t>, double> data;
    for (size_t i = 0; i < nonZeros; ++i) {
        size_t row = rand() % rows;
        size_t col = rand() % cols;
        data[{row, col}] = static_cast<double>(rand()) / RAND_MAX; // Заполнение случайными числами
    }
    return CSRMatrix<double>(data, cols, rows);
}
template <class T>
std::vector<T> generateVector(size_t length,  size_t nonZeroCount) {
    

    // Создаем вектор с нулями
    std::vector<T> vec(length, 0);

    // Устанавливаем ненулевые элементы
    for (size_t i = 0; i < nonZeroCount; ++i) {
        vec[i] = 1; // Можно использовать любое ненулевое значение
    }

    // Перемешиваем вектор, чтобы расположение ненулевых элементов было случайным
    std::random_device rd; // Получаем случайное число от устройства
    std::mt19937 g(rd()); // Инициализируем генератор случайных чисел
    std::shuffle(vec.begin(), vec.end(), g);

    return vec;
}

TEST(MatrixMultiplicationTest, CompareDenseAndCSR5_5) {
    size_t rows = 5;
    size_t cols = 5;
    Matrix<double> denseMatrix = generateDenseMatrix(rows, cols);
    CSRMatrix<double> csrMatrix = generateCSRMatrix(rows, cols, 12);
    
    for (size_t nonZeros : {1,2, 3 , 4, 5}) {
        
        std::vector<double> vec = generateVector<double>(cols, nonZeros);
        //print(vec);

        // Умножение плотной матрицы на вектор
        auto startDense = std::chrono::high_resolution_clock::now();
        auto denseResult = denseMatrix * vec; 
        auto endDense = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationDense = endDense - startDense;

        // Умножение CSR-матрицы на вектор
        auto startCSR = std::chrono::high_resolution_clock::now();
        auto csrResult = csrMatrix * vec;
        auto endCSR = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationCSR = endCSR - startCSR;

        // Вывод результатов
        std::cout << "Non-zeros: " << nonZeros << ", Dense time: " << durationDense.count() << "s, CSR time: " << durationCSR.count() << "s" << std::endl;
    }
}
TEST(MatrixMultiplicationTest, CompareDenseAndCSR25_25) {
    size_t rows = 25;
    size_t cols = 25;
    Matrix<double> denseMatrix = generateDenseMatrix(rows, cols);
    CSRMatrix<double> csrMatrix = generateCSRMatrix(rows, cols, 312);
    
    for (size_t nonZeros : {1, 5, 7, 10, 15, 20, 24}) {
        
        std::vector<double> vec = generateVector<double>(cols, nonZeros);
        //print(vec);

        // Умножение плотной матрицы на вектор
        auto startDense = std::chrono::high_resolution_clock::now();
        auto denseResult = denseMatrix * vec; 
        auto endDense = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationDense = endDense - startDense;

        // Умножение CSR-матрицы на вектор
        auto startCSR = std::chrono::high_resolution_clock::now();
        auto csrResult = csrMatrix * vec;
        auto endCSR = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationCSR = endCSR - startCSR;

        // Вывод результатов
        std::cout << "Non-zeros: " << nonZeros << ", Dense time: " << durationDense.count() << "s, CSR time: " << durationCSR.count() << "s" << std::endl;
    }
}
TEST(MatrixMultiplicationTest, CompareDenseAndCSR100_100) {
    size_t rows = 100;
    size_t cols = 100;
    Matrix<double> denseMatrix = generateDenseMatrix(rows, cols);
    CSRMatrix<double> csrMatrix = generateCSRMatrix(rows, cols, 5000);
    
    for (size_t nonZeros : {10, 20, 40, 60, 80, 99}) {
        
        std::vector<double> vec = generateVector<double>(cols, nonZeros);
        //print(vec);

        // Умножение плотной матрицы на вектор
        auto startDense = std::chrono::high_resolution_clock::now();
        auto denseResult = denseMatrix * vec; 
        auto endDense = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationDense = endDense - startDense;

        // Умножение CSR-матрицы на вектор
        auto startCSR = std::chrono::high_resolution_clock::now();
        auto csrResult = csrMatrix * vec;
        auto endCSR = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationCSR = endCSR - startCSR;

        // Вывод результатов
        std::cout << "Non-zeros: " << nonZeros << ", Dense time: " << durationDense.count() << "s, CSR time: " << durationCSR.count() << "s" << std::endl;
    }
}
TEST(MatrixMultiplicationTest, CompareDenseAndCSR1000_1000) {
    size_t rows = 1000;
    size_t cols = 1000;
    Matrix<double> denseMatrix = generateDenseMatrix(rows, cols);
    CSRMatrix<double> csrMatrix = generateCSRMatrix(rows, cols, 500000);
    
    for (size_t nonZeros : {100, 200, 500, 700, 999}) {
        
        std::vector<double> vec = generateVector<double>(cols, nonZeros);
        //print(vec);

        // Умножение плотной матрицы на вектор
        auto startDense = std::chrono::high_resolution_clock::now();
        auto denseResult = denseMatrix * vec; 
        auto endDense = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationDense = endDense - startDense;

        // Умножение CSR-матрицы на вектор
        auto startCSR = std::chrono::high_resolution_clock::now();
        auto csrResult = csrMatrix * vec;
        auto endCSR = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationCSR = endCSR - startCSR;

        // Вывод результатов
        std::cout << "Non-zeros: " << nonZeros << ", Dense time: " << durationDense.count() << "s, CSR time: " << durationCSR.count() << "s" << std::endl;
    }
}

// Тест для сравнения скорости умножения
TEST(MatrixMultiplicationTest, CompareDenseAndCSR) {
    size_t rows = 1000;
    size_t cols = 1000;
    
    for (size_t nonZeros : {100, 1000, 5000, 10000,20000, 50000, 75000,100000}) {
        // Генерация матриц
        Matrix<double> denseMatrix = generateDenseMatrix(rows, cols);
        CSRMatrix<double> csrMatrix = generateCSRMatrix(rows, cols, nonZeros);
        
        // Генерация вектора
        std::vector<double> vec(cols);
        for (size_t i = 0; i < cols; ++i) {
            vec[i] = static_cast<double>(rand()) / RAND_MAX; // Заполнение случайными числами
        }

        // Умножение плотной матрицы на вектор
        auto startDense = std::chrono::high_resolution_clock::now();
        auto denseResult = denseMatrix * vec; // Предполагается, что у вас есть перегруженный оператор *
        auto endDense = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationDense = endDense - startDense;

        // Умножение CSR-матрицы на вектор
        auto startCSR = std::chrono::high_resolution_clock::now();
        auto csrResult = csrMatrix * vec;
        auto endCSR = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> durationCSR = endCSR - startCSR;

        // Вывод результатов
        std::cout << "Non-zeros: " << nonZeros << ", Dense time: " << durationDense.count() << "s, CSR time: " << durationCSR.count() << "s" << std::endl;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
