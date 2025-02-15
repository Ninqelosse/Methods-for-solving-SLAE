#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <vector>
#include <utility>
#include <map>
template <class T> 
class Matrix {
    private:
        size_t nx_;
        size_t ny_;
        std::vector<T> m_; // m_.size() == nx_ * ny_
    public:
        Matrix(size_t nx, size_t ny) : nx_(nx), ny_(ny), m_(nx * ny) {}
        Matrix(){
            nx_ = 0;
            ny_ = 0;
        }
        Matrix(size_t nx, size_t ny, std::vector<T> a){
            nx_ = nx;
            ny_ = ny;
            m_.resize(nx_*ny_);
            m_ = a;
        }
        T operator()(size_t i, size_t j) const {
            return m_[i * ny_ + j];
        }      
        T& operator()(size_t i, size_t j) {
            return m_[i * ny_ + j];
        }
        size_t cols ()const{
            return ny_;
        }
        size_t rows()const {
            return nx_;
        }
        void print(){
            for (size_t i=0; i< m_.size(); i++){
                std::cout << m_[i] << " ";
            }
            std::cout << std::endl;
        }
};
template <class T>
class CSRMatrix {
    private:
        std::vector<T> vals_;
        std::vector<size_t> cols_;
        std::vector<size_t> rows_;
        size_t rows__;
        size_t cols__;
    public:
        CSRMatrix(){}
        CSRMatrix(std::map<std::pair <size_t, size_t>,T> Map, size_t cols, size_t rows){
            if(Map.empty()==false){
                //raws.append(0);
                size_t N = Map.size();
                vals_.resize(N);
                cols_.resize(N);
                rows_.resize(rows+1,0);
                rows__ = rows;
                cols__ = cols;
                rows_[0] = 0;
                size_t index = 0;
                for (const auto& it : Map) {
                    vals_[index] = it.second;                     // Значение
                    cols_[index] = it.first.second;               // Номер столбца
                    rows_[it.first.first + 1] += 1;               // Увеличиваем счетчик ненулевых элементов в строке
                    ++index;
                }
    
                // Преобразуем ымассив rows_ в префиксные суммы
                for (size_t i = 1; i <= rows__; ++i) {
                    rows_[i] += rows_[i - 1];
                }
            }else {
               // Если карта пуста, инициализируем все массивы пустыми значениями
                rows_.resize(rows + 1, 0);
            }
            
        }
        T get(size_t row, size_t col) const {
            if (row >= rows__ || col >= cols__) {
                throw std::out_of_range("Index out of range");
            }
    
            // Находим начало и конец строки в массиве vals_ и cols_
            size_t start = rows_[row];
            size_t end = rows_[row + 1];
    
            // Ищем нужный элемент в пределах этой строки
            for (size_t i = start; i < end; ++i) {
                if (cols_[i] == col) {
                    return vals_[i]; // Возвращаем значение, если нашли
                }
            }
    
            return T(); // Возвращаем значение по умолчанию, если элемент не найден (для T это будет 0)
        }
        void print (){
            for (size_t i = 0; i<vals_.size();i++){
                std::cout << vals_[i] << " ";
            }
            std::cout << std::endl;
            for (size_t i = 0; i<cols_.size();i++){
                std::cout << cols_[i] << " ";
            }
            std::cout << std::endl;
            for (size_t i = 0; i<rows_.size();i++){
                std::cout << rows_[i] << " ";
            }
            std::cout << std::endl;
        }
        std::vector<T> operator*(const std::vector<T>& vec) const {
            if (vec.size() != cols__) {
                throw std::invalid_argument("Vector size must match the number of columns in the matrix.");
            }
    
            std::vector<T> result(rows__, T()); // Результирующий вектор инициализируем нулями
    
            for (size_t i = 0; i < rows__; ++i) {
                size_t start = rows_[i];
                size_t end = rows_[i + 1];
    
                for (size_t j = start; j < end; ++j) {
                    result[i] += vals_[j] * vec[cols_[j]]; // Умножаем ненулевое значение на соответствующий элемент вектора
                }
            }
    
            return result;
        }
};

template <typename T>
std::vector<T> operator+(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    // Проверяем, что размеры векторов одинаковые
    if (lhs.size() != rhs.size()) {
        throw std::invalid_argument("Vectors must be of the same size");
    }

    std::vector<T> result(lhs.size()); // Создаем вектор для хранения результата

    // Складываем соответствующие элементы
    for (size_t i = 0; i < lhs.size(); ++i) {
        result[i] = lhs[i] + rhs[i];
    }

    return result; // Возвращаем результат
}
template <typename T>
std::vector<T> operator-(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    // Проверяем, что размеры векторов одинаковые
    if (lhs.size() != rhs.size()) {
        throw std::invalid_argument("Vectors must be of the same size");
    }

    std::vector<T> result(lhs.size()); // Создаем вектор для хранения результата

    // Складываем соответствующие элементы
    for (size_t i = 0; i < lhs.size(); ++i) {
        result[i] = lhs[i] - rhs[i];
    }

    return result; // Возвращаем результат
}
template <class T>
T operator*(const std::vector<T>& lhs, const std::vector<T>& rhs) {
    // Проверяем, что размеры векторов одинаковые
    if (lhs.size() != rhs.size()) {
        throw std::invalid_argument("Vectors must be of the same size");
    }

    T result = 0;

    // Складываем соответствующие элементы
    for (size_t i = 0; i < lhs.size(); ++i) {
        result += lhs[i]*rhs[i];
    }

    return result; // Возвращаем результат
}
template <typename T>
std::vector<T> operator*(const std::vector<T>& lhs, const T a) {
    // Проверяем, что размеры векторов одинаковые
    std::vector<T> result(lhs.size()); // Создаем вектор для хранения результата

    // Складываем соответствующие элементы
    for (size_t i = 0; i < lhs.size(); ++i) {
        result[i] = lhs[i]*a;
    }

    return result; // Возвращаем результат
}
template < class T>
std::vector<T> operator*(const T a, const std::vector<T>& lhs) {
    // Проверяем, что размеры векторов одинаковые
    std::vector<T> result(lhs.size()); // Создаем вектор для хранения результата

    // Складываем соответствующие элементы
    for (size_t i = 0; i < lhs.size(); ++i) {
        result[i] = lhs[i]*a;
    }

    return result; // Возвращаем результат
}
template <class T>
std::vector<T> operator*(const Matrix <T> A,const std::vector<T>& rhs) {
    // Проверяем, что размеры векторов одинаковые
    //std::cout << A.cols();
    if (A.cols() != rhs.size()) {
        throw std::invalid_argument("Vectors must be of the same size");
    }

    std::vector<T> result(rhs.size()); // Создаем вектор для хранения результата

    // Складываем соответствующие элементы

    for (size_t i = 0; i < A.rows(); i++) { 
        T sum = 0;
        for (size_t j = 0; j< A.cols();j++){
            sum+=rhs[j]*A(i,j);
        }
        result[i] = sum;
    }

    return result; // Возвращаем результат
}
template <class T>
void print(std::vector <T> a){
    for (size_t i = 0; i<a.size(); i++){
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

#endif // MYCLASS_H