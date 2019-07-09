#include <iostream>
#include <vector>
#include <cassert>

template<class T>
class MatrixIterator;

template<class T>
class ConstMatrixIterator;

template<class T>
class Matrix {
private:
    std::vector<std::vector<T>> matrix;
    size_t M, N;

public:
    explicit Matrix(const std::vector<std::vector<T>>& input) {
        matrix = input;
        M = matrix.size();
        if (M > 0)
            N = matrix[0].size();
        else
            N = 0;
    }

    std::vector<T>& operator[] (size_t i) {
        return matrix[i];
    }

    const std::vector<T>& operator[] (size_t i) const {
        return matrix[i];
    }

    std::pair<size_t, size_t> size() const {
        return {M, N};
    }

    Matrix& operator += (const Matrix& other) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                matrix[i][j] += other.matrix[i][j];
            }
        }
        return *this;
    }

    Matrix operator + (const Matrix& other) const {
        return Matrix(matrix) += other;
    }

    template<class Scalar>
    Matrix& operator *= (const Scalar& t) {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                matrix[i][j] *= t;
            }
        }
        return *this;
    }

    template<class Scalar>
    Matrix operator * (const Scalar& t) const {
        return Matrix(matrix) *= t;
    }

    Matrix& transpose() {
        std::vector<std::vector<T>> temp(N, std::vector<T>(M));

        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; ++j) {
                temp[j][i] = matrix[i][j];
            }
        }

        matrix = temp;
        std::swap(N, M);
        return *this;
    }

    Matrix transposed() const {
        Matrix ans = *this;
        return ans.transpose();
    }

    Matrix& operator *=(const Matrix& other) {
        assert(N == other.M);
        Matrix temp(std::vector<std::vector<T>>(M, std::vector<T>(other.N)));
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < other.N; ++j) {
                for (size_t k = 0; k < N; ++k) {
                    temp.matrix[i][j] += (matrix[i][k] * other.matrix[k][j]);
                }
            }
        }
        *this = temp;
        return *this;
    }

    Matrix operator * (const Matrix& other) const {
        assert(N == other.M);
        Matrix temp(std::vector<std::vector<T>>(M, std::vector<T>(other.N)));
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < other.N; ++j) {
                for (size_t k = 0; k < N; ++k) {
                    temp.matrix[i][j] += (matrix[i][k] * other.matrix[k][j]);
                }
            }
        }
        return temp;
    }

    MatrixIterator<T> begin()  {
        return MatrixIterator<T>(this, 0, 0);
    }

    MatrixIterator<T> end() {
        return MatrixIterator<T>(this, M, 0);
    }

    ConstMatrixIterator<T> begin() const {
        return ConstMatrixIterator<T>(this, 0, 0);
    }

    ConstMatrixIterator<T> end() const {
        return ConstMatrixIterator<T>(this, M, 0);
    }
};

template<class T>
class MatrixIterator {
private:
    Matrix<T>* matrix;
    size_t row, column;

public:
    explicit MatrixIterator(Matrix<T>* mat, size_t _row, size_t _column) :
        matrix(mat),
        row(_row),
        column(_column) {}

    bool operator == (MatrixIterator other) const {
        return (row == other.row) && (column == other.column);
    }

    bool operator != (MatrixIterator other) const {
        return !((*this) == other);
    }

    T& operator * () {
        return (*matrix)[row][column];
    }

    MatrixIterator& operator++() {
        ++column;
        if (column == (*matrix).size().second) {
            column = 0;
            ++row;
        }
        return *this;
    }
};

template<class T>
class ConstMatrixIterator {
private:
    const Matrix<T>* matrix;
    size_t row, column;

public:
    explicit ConstMatrixIterator(const Matrix<T>* mat, size_t _row, size_t _column) :
            matrix(mat),
            row(_row),
            column(_column) {}

    bool operator == (ConstMatrixIterator other) const {
        return (row == other.row) && (column == other.column);
    }

    bool operator != (ConstMatrixIterator other) const {
        return !((*this) == other);
    }

    T operator * () {
        return (*matrix)[row][column];
    }

    ConstMatrixIterator& operator++() {
        ++column;
        if (column == (*matrix).size().second) {
            column = 0;
            ++row;
        }
        return *this;
    }
};

template<class T>
std::ostream& operator << (std::ostream& out, const Matrix<T>& mat) {
    auto[m, n] = mat.size();
    for (size_t i = 0; i < m; ++i) {
        out << mat[i][0];
        for (size_t j = 1; j < n; ++j) {
            out << "\t" << mat[i][j];
        }
        if (i != m - 1)
            out << "\n";
    }
    return out;
}
