#ifndef TDMATRIX_H
#define TDMATRIX_H
#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>
template<class T>
class TDMatrix;

template <class T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& A) {
    for (const auto& val : A) {
        stream << val << " ";
    }
    stream << std::endl;

    return stream;
}

template<class T>
std::ostream& operator<<(std::ostream& stream, const TDMatrix<T>& A) {
    stream << A.up << A.middle << A.down;

    return stream;
}

template<class T>
std::istream& operator>>(std::istream& in, TDMatrix<T>& A) {
    size_t n;
    in >> n;

    A.up.resize(n - 1);
    A.middle.resize(n);
    A.down.resize(n - 1);

    for (size_t i = 0; i < n - 1; i++) {
        in >> A.up[i];
    }
    for (size_t i = 0; i < n; i++) {
        in >> A.middle[i];
    }
    for (size_t i = 0; i < n - 1; i++) {
        in >> A.down[i];
    }

    return in;
}
template<class T>
std::vector <T> three_diag_prog(const TDMatrix<T>& A, const std::vector<T>& d) {
    int n = A.get_size();
    if (d.size() != n) {
        throw std::invalid_argument("The size of the vector d does not correspond to the size of the matrix.");
    }
    if (A.check_diag_dominance()==false) {
        throw std::runtime_error("Matrix does not satisfy diagonal dominance condition.");
    }
    std::vector <T> p(n - 1);
    std::vector <T> q(n - 1);
    std::vector <T> x(n);
    p[0] = -A.up[0] / A.middle[0];
    q[0] = d[0] / A.middle[0];

    for (size_t i = 1; i < n - 1; i++) {
        p[i] = -A.up[i] / (A.down[i - 1] * p[i - 1] + A.middle[i]);
        q[i] = (d[i] - A.down[i - 1] * q[i - 1]) / (A.down[i - 1] * p[i - 1] + A.middle[i]);
    }
    x[n - 1] = (d[n - 1] - A.down[n - 2] * q[n - 2]) / (A.down[n - 2] * p[n - 2] + A.middle[n - 1]);

    for (size_t i = n - 1; i > 0; i--) {
        x[i - 1] = p[i - 1] * x[i] + q[i - 1];
        if (std::isnan(x[i-1])) {
            throw std::runtime_error("The system has no solution: NaN occurred in the solution.");
        }
    }
    return x;
}
template <class T>
class TDMatrix {
private:
    std::vector<T> up;      // Вектор для верхней диагонали
    std::vector<T> middle;  // Вектор для главной диагонали
    std::vector<T> down;    // Вектор для нижней диагонали

public:
    template <class T1>
    friend std::ostream& operator<<(std::ostream& stream, const TDMatrix<T1>& A);
    template <class T1>
    friend std::istream& operator>>(std::istream& in, TDMatrix<T1>& A);
    template <class T1>
    friend std::vector <T1> three_diag_prog(const TDMatrix<T1>& A, const std::vector<T1>& d);

    TDMatrix(std::vector<T> up_, std::vector<T> middle_, std::vector<T> down_) {
        size_t middle_size = middle_.size();
        if (up_.size() != middle_size - 1) {
            throw std::invalid_argument("Size of 'up' must be one less than size of 'middle'");
        }
        if (down_.size() != middle_size - 1) {
            throw std::invalid_argument("Size of 'down' must be one less than size of 'middle'");
        }

        up = std::move(up_);
        middle = std::move(middle_);
        down = std::move(down_);
    }

    TDMatrix() {}


    size_t get_size() const {
        return middle.size();
    }
    bool check_diag_dominance() const{
        for (size_t i = 0;i< up.size(); i++) {
            if(abs(middle[i]) >= abs(down[i])+abs(up[i])){
                continue;
            }else {
                return false;
            }
        }
        return true;
    }

};

#endif //TDMATRIX_H
