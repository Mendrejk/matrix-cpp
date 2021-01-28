#ifndef MATRIX_CPP_MATRIX_H
#define MATRIX_CPP_MATRIX_H

#include <stdexcept>
#include <vector>
#include <sstream>
#include <optional>
#include <iomanip>
#include <iostream>

/**
 * A class representing a two-dimensional mathematical matrix.
 */
template<typename T>
class Matrix {
private:
    int size_x_;
    int size_y_;
    T** matrix_;
    bool is_vector_;

    // TODO document InitialiseMatrix(T)
    void InitialiseMatrix(T initial_value);
    // TODO document InitialiseMatrix(vec<vec<T>>)
    void InitialiseMatrix(std::vector<std::vector<T>> initial_vector);
    // TODO document AssertDimensions
    void AssertDimensions(int size_y, int size_x) const;
    // TODO document AssertAndGetWidth
    int AssertAndGetWidth(std::vector<std::vector<T>> initial_vector) const;
    // TODO document AssertAndGetHeight
    int AssertAndGetHeight(std::vector<std::vector<T>> initial_vector) const;
    // TODO document GetLongestElemLength
    [[nodiscard]] std::optional<int> GetLongestElemLength() const;
    // TODO document CopyMatrix
    void CopyMatrix(const Matrix& other);
    // TODO document
    [[nodiscard]] bool HasSameDimensions(const Matrix& other) const;

    [[nodiscard]] bool CheckIsVector() const;

    // TODO document private constructor Matrix(int size_y, int size_x)
    Matrix(int size_y, int size_x);
public:
    /**
     * Initialises a new empty Matrix sized size_y_ * size_x_ filled with
     * instances of init_value.
     * Throws an invalid_argument if either of dimensions in not positive.
     * @param size_y matrix width
     * @param size_x matrix height
     * @param init_value value to initialise matrix fields with
     */
    Matrix(int size_y, int size_x, T initial_value);

    /**
     * Initialises a new empty Matrix with values of initial_vector
     * Throws an invalid_argument if the vector's dimensions are not positive
     * or it's not a rectangle
     * @param initial_vector vector of vectors of initial values
     */
    // I opted to use a vector as opposed to a pointer here to prevent
    // undefined behaviour when given size is larger than array's length
    explicit Matrix(std::vector<std::vector<T>> initial_vector);

    // TODO document ~Matrix
    ~Matrix();

    // TODO document copy constructor
    Matrix(const Matrix& other);
    // TODO document move constructor
    Matrix(Matrix&& other) noexcept;

    // TODO document operator=()
    Matrix& operator=(const Matrix& other);

    // TODO document this
    Matrix& operator=(Matrix&& other) noexcept;

    // TODO implement operator[]

    // TODO comment ToString()
    [[nodiscard]] std::string ToString() const;

    // TODO comment Add()
    std::optional<Matrix> Add(const Matrix& other) const &;

    // TODO comment Add() &&
    std::optional<Matrix> Add(const Matrix& other) &&;

    // TODO comment Add(&&)
    std::optional<Matrix> Add(const Matrix&& other) const &;

    // TODO comment operator+()
    // TODO add version for if this or other is an rvalue
    std::optional<Matrix> operator+(const Matrix& other) const &;

    // TODO document operator+() &&
    // FIXME this does not properly use move constructor
    // FIXME because wrong Add() overload is called()
    std::optional<Matrix> operator+(const Matrix& other) &&;

    // TODO document operator+(&&) &
    std::optional<Matrix> operator+(const Matrix&& other) &;

    // TODO document operator+(&&) &&
    std::optional<Matrix> operator+(const Matrix&& other) &&;

    // TODO comment Subtract()
    std::optional<Matrix> Subtract(const Matrix& other) const &;

    // TODO document Subtract() &&
    std::optional<Matrix> Subtract(const Matrix& other) &&;

    // TODO document Subtract(&&)
    std::optional<Matrix> Subtract(const Matrix&& other) const &;

    // TODO document operator-()
    std::optional<Matrix> operator-(const Matrix& other) const &;

    // TODO document operator-() &&
    std::optional<Matrix> operator-(const Matrix& other) &&;

    // TODO document operator-(&&) &
    std::optional<Matrix> operator-(const Matrix&& other) &;

    // TODO document operator-(&&) &&
    std::optional<Matrix> operator-(const Matrix&& other) &&;

    // TODO document Multiply()
    // FIXME return type Matrix or Matrix&? same below
    Matrix Multiply(T multiplier) const &;

    // TODO document Multiply() &&
    Matrix Multiply(T multiplier) &&;

    Matrix operator*(T multiplier) const &;

    Matrix operator*(T multiplier) &&;

    // TODO document DotProduct
    // only works if this and other are vectors
    std::optional<T> DotProduct(const Matrix& other_vector) const;

    // TODO document Multiply()
    // TODO overload for MS
    std::optional<Matrix<T>> Multiply(const Matrix& other) const;

    // TODO document operator *
    // cant both calculate dot product and multiply matrices
    // ^ FAKE dont do operator dotProduct
    // TODO MS
    std::optional<Matrix<T>> operator*(const Matrix& other) const;

    // TODO document VectorFromColumn()
    std::optional<Matrix<T>> VectorFromColumn(int column_index) const;

    // TODO document VectorFromRow()
    std::optional<Matrix<T>> VectorFromRow(int row_index) const;

    // TODO MS for this
    // TODO document Transpose()
    // FIXME returning Matrix<T> crashes in toString - gets null reference
    Matrix<T> Transpose();

    // TODO document CreateMatrix
    static std::optional<Matrix<T>> CreateMatrix(const int size_y, const int size_x, const T initial_value);

    // TODO document SetValue()
    bool SetValue(int index_y, int index_x, T value);

    // TODO document GetValue()
    std::optional<T> GetValue(int index_y, int index_x);

    // TODO document operator[] get
    std::optional<T*> operator[](int index_y);

    // TODO document SetIdentityMatrix()
    std::optional<Matrix<T>> SetIdentityMatrix();

    // TODO document operator==
    bool operator==(const Matrix& other) const;
};

template<typename T>
Matrix<T>::Matrix(const int size_y, const int size_x, const T initial_value)
        : size_y_(size_y), size_x_(size_x) {
    AssertDimensions(size_y, size_x);
    InitialiseMatrix(initial_value);
    is_vector_ = CheckIsVector();

    // TODO remove/refactor this cout
    std::cout << "Parametric constructor" << std::endl;
}

template<typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> initial_vector)
        : size_y_(AssertAndGetHeight(initial_vector)),
          size_x_(AssertAndGetWidth(initial_vector)) {
    InitialiseMatrix(initial_vector);
    is_vector_ = CheckIsVector();

    // TODO remove/refactor this cout
    std::cout << "Parametric constructor" << std::endl;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
        : size_y_(other.size_y_), size_x_(other.size_x_) {
    CopyMatrix(other);
    is_vector_ = CheckIsVector();

    // TODO remove/refactor this cout
    std::cout << "Copy constructor" << std::endl;
}

template<typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept
        : size_y_(other.size_y_), size_x_(other.size_x_) {
    is_vector_ = other.is_vector_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;

    // TODO remove/refactor this cout
    std::cout << "Move constructor" << std::endl;
}

template<typename T>
Matrix<T>::~Matrix() {
    if (matrix_ != nullptr) {
        for (int i = 0; i < size_y_; i++) {
            if (matrix_[i] != nullptr) {
                delete[] matrix_[i];
            }
        }
        delete[] matrix_;
    }
}

template<typename T>
void Matrix<T>::AssertDimensions(const int size_y, const int size_x) const {
    if (size_y < 1) {
        throw std::invalid_argument("Matrix dimensions must be positive! "
                                    "Received: " + std::to_string(size_y)
                                    + " as height.");
    } else if (size_x < 1) {
        throw std::invalid_argument("Matrix dimensions must be positive! "
                                    "Received: " + std::to_string(size_x)
                                    + " as width.");
    } else if (size_y < 1 && size_x < 1) {
        throw std::invalid_argument("Matrix dimensions must be positive! "
                                    "Received:" + std::to_string(size_y)
                                    + "as height and " + std::to_string(size_x)
                                    + "as width.");
    }
}

template<typename T>
int Matrix<T>::AssertAndGetHeight(
        std::vector<std::vector<T>> initial_vector) const {
    if (initial_vector.size() < 1) {
        throw std::invalid_argument("Matrix dimensions must be positive! "
                                    "Received: "
                                    + std::to_string(initial_vector.size())
                                    + " as vector's height.");
    }
    return initial_vector.size();
}

template<typename T>
int Matrix<T>::AssertAndGetWidth(
        std::vector<std::vector<T>> initial_vector) const {
    // first we need to check if initial_vector[0] exists
    // technically it's pointless to call AssertAndGetWidth twice,
    // but arguments in initializer list don't have to be executed in order
    AssertAndGetHeight(initial_vector);

    // compare every line's size to first_width
    // If not equal then it's not a rectangle
    int first_width = initial_vector[0].size();
    if (first_width < 1) {
        throw std::invalid_argument("Matrix dimensions must be positive! "
                                    "Received: " + std::to_string(first_width)
                                    + " as vector's width.");
    }

    for (int i = 1; i < initial_vector.size(); i++) {
        if (initial_vector[i].size() != first_width) {
            throw std::invalid_argument("Matrix dimensions must be positive "
                                        " and it has to be a rectangle!"
                                        "Received: " +
                                        std::to_string(initial_vector[i].size())
                                        + " as vector's width.");
        }
    }
    return first_width;
}

template<typename T>
void Matrix<T>::InitialiseMatrix(const T initial_value) {
    matrix_ = new T*[size_y_];
    for (int i = 0; i < size_y_; i++) {
        matrix_[i] = new T[size_x_];
        for (int j = 0; j < size_x_; j++) {
            matrix_[i][j] = initial_value;
        }
    }
}

template<typename T>
void Matrix<T>::InitialiseMatrix(
        const std::vector<std::vector<T>> initial_vector) {
    matrix_ = new T*[size_y_];
    for (int i = 0; i < size_y_; i++) {
        matrix_[i] = new T[size_x_];
        for (int j = 0; j < size_x_; j++) {
            matrix_[i][j] = initial_vector[i][j];
        }
    }
}

template<typename T>
void Matrix<T>::CopyMatrix(const Matrix<T>& other) {
    matrix_ = new T*[size_y_];
    for (int i = 0; i < size_y_; i++) {
        matrix_[i] = new T[size_x_];
        for (int j = 0; j < size_x_; j++) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (&other != this) {
        for (int i = 0; i < size_y_; i++) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
    }

    size_y_ = other.size_y_;
    size_x_ = other.size_x_;
    is_vector_ = other.is_vector_;
    CopyMatrix(other);

    // TODO remove/refactor this cout
    std::cout << "operator=" << std::endl;
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept {
    for (int i = 0; i < size_y_; i++) {
        delete[] matrix_[i];
    }
    delete[] matrix_;

    size_y_ = other.size_y_;
    size_x_ = other.size_x_;
    is_vector_ = other.is_vector_;
    matrix_ = other.matrix_;

    other.matrix_ = nullptr;

    // TODO remove/refactor this cout
    std::cout << "Move operator=" << std::endl;
}

template<typename T>
std::optional<int> Matrix<T>::GetLongestElemLength() const {
    // initial value
    int longest_length = -1;
    std::stringstream elemString;

    for (int i = 0; i < size_y_; i++) {
        for (int j = 0; j < size_x_; j++) {
            elemString << matrix_[i][j];
            int tmp_length = elemString.str().size();
            if (tmp_length > longest_length) {
                longest_length = tmp_length;
            }
            elemString.str(std::string());
        }
    }

    if (longest_length > 0) {
        return longest_length;
    } else {
        return {};
    }
}

template<typename T>
std::string Matrix<T>::ToString() const {
    std::stringstream to_string;
    // FIXME magic number '4' constants.cpp file?
    int longest_length = GetLongestElemLength().value() + 4;

    for (int i = 0; i < size_y_; i++) {
        for (int j = 0; j < size_x_; j++) {
            to_string << std::right << std::setw(longest_length)
            << matrix_[i][j];
        }
        to_string << '\n';
    }
    return to_string.str();
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::Add(const Matrix<T>& other) const & {
    if (HasSameDimensions(other)) {
        Matrix<T> addition(*this);

        for (int i = 0; i < size_y_; i++) {
            for (int j = 0; j < size_x_; j++) {
                addition.matrix_[i][j] += other.matrix_[i][j];
            }
        }

        return addition;
    } else {
        return {};
    }
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::Add(const Matrix<T>& other) && {
    if (HasSameDimensions(other)) {
        for (int i = 0; i < size_y_; i++) {
            for (int j = 0; j < size_x_; j++) {
                matrix_[i][j] += other.matrix_[i][j];
            }
        }

        // TODO remove this cout
        std::cout << "rvalue add" << std::endl;
        return std::move(*this);
    } else {
        return {};
    }
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::Add(const Matrix&& other) const & {
    if (HasSameDimensions(other)) {
        for (int i = 0; i < size_y_; i++) {
            for (int j = 0; j < size_x_; j++) {
                other.matrix_[i][j] += matrix_[i][j];
            }
        }

        // TODO remove this cout
        std::cout << "other rvalue add" << std::endl;
        return std::move(other);
    } else {
        return {};
    }
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::operator+(const Matrix<T> &other) const & {
    return Add(other);
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::operator+(const Matrix<T>& other) && {
    return Add(other);
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::operator+(const Matrix<T>&& other) & {
    return Add(other);
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::operator+(const Matrix<T>&& other) && {
    return Add(other);
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::Subtract(const Matrix<T> &other) const & {
    if (HasSameDimensions(other)) {
        Matrix subtraction(*this);

        for (int i = 0; i < size_y_; i++) {
            for (int j = 0; j < size_x_; j++) {
                subtraction.matrix_[i][j] -= other.matrix_[i][j];
            }
        }

        return subtraction;
    } else {
        return {};
    }
}


template<typename T>
std::optional<Matrix<T>> Matrix<T>::Subtract(const Matrix<T> &other) &&{
    if (HasSameDimensions(other)) {
        for (int i = 0; i < size_y_; i++) {
            for (int j = 0; j < size_x_; j++) {
                matrix_[i][j] -= other.matrix_[i][j];
            }
        }

        return *this;
    } else {
        return {};
    }
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::Subtract(const Matrix<T> &&other) const &{
    if (HasSameDimensions(other)) {
        for (int i = 0; i < size_y_; i++) {
            for (int j = 0; j < size_x_; j++) {
                other.matrix_[i][j] -= matrix_[i][j];
            }
        }

        return other;
    } else {
        return {};
    }
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::operator-(const Matrix<T> &other) const & {
    return Subtract(other);
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::operator-(const Matrix<T> &other) &&{
    return Subtract(other);
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::operator-(const Matrix<T> &&other) &{
    return Subtract(other);
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::operator-(const Matrix<T> &&other) &&{
    return Subtract(other);
}

template<typename T>
Matrix<T> Matrix<T>::Multiply(const T multiplier) const &{
    Matrix multiplication(*this);

    for (int i = 0; i < size_y_; i++) {
        for (int j = 0; j < size_x_; j++) {
            multiplication.matrix_[i][j] *= multiplier;
        }
    }
    return multiplication;
}

template<typename T>
Matrix<T> Matrix<T>::Multiply(const T multiplier) &&{
    for (int i = 0; i < size_y_; i++) {
        for (int j = 0; j < size_x_; j++) {
            matrix_[i][j] *= multiplier;
        }
    }
    return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T multiplier) const & {
    return Multiply(multiplier);
}

// FIXME should there be a const here?
template<typename T>
Matrix<T> Matrix<T>::operator*(T multiplier) &&{
    return Multiply(multiplier);
}

template<typename T>
std::optional<T> Matrix<T>::DotProduct(const Matrix<T>& other_vector) const {
    T dot_product = matrix_[0][0] * other_vector.matrix_[0][0];
    if (size_y_ == 1 && other_vector.size_y_ == 1
            && size_x_ == other_vector.size_x_) {
        for (int i = 1; i < size_x_; i++) {
            dot_product += matrix_[0][i] * other_vector.matrix_[0][i];
        }
    } else if (size_y_ == 1 && other_vector.size_x_ == 1
            && size_x_ == other_vector.size_y_) {
        for (int i = 1; i < size_x_; i++) {
            dot_product += matrix_[0][i] * other_vector.matrix_[i][0];
        }
    } else if (size_x_ == 1 && other_vector.size_x_ == 1
            && size_y_ == other_vector.size_y_) {
        for (int i = 1; i < size_y_; i++) {
            dot_product += matrix_[i][0] * other_vector.matrix_[i][0];
        }
    } else if (size_x_ == 1 && other_vector.size_y_ == 1
            && size_y_ == other_vector.size_x_) {
        for (int i = 1; i < size_y_; i++) {
            dot_product += matrix_[i][0] * other_vector.matrix_[0][i];
        }
    } else {
        return {};
    }
    return dot_product;
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::Multiply(const Matrix<T>& other) const {
    if (is_vector_ && other.is_vector_) {
        // can't multiply two vectors to return a matrix/vector
        return {};
    } else if (size_x_ == other.size_y_) {
        Matrix result(size_y_, other.size_x_);
        for (int i = 0; i < result.size_y_; i++) {
            for (int j = 0; j < result.size_x_; j++) {
                result.matrix_[i][j] = VectorFromRow(i).value().DotProduct(other.VectorFromColumn(j).value()).value();
            }
        }
        return result;
    } else if (is_vector_ && size_y_ == other.size_y_) {
        Matrix result(size_x_, other.size_x_);
        for (int i = 0; i < result.size_y_; i++) {
            for (int j = 0; j < result.size_x_; j++) {
                result.matrix_[i][j] = VectorFromColumn(i).value().DotProduct(other.VectorFromColumn(j).value()).value();
            }
        }
        return result;
    } else if (other.is_vector_ && size_x_ == other.size_x_) {
        Matrix result(size_y_, other.size_y_);
        for (int i = 0; i < result.size_y_; i++) {
            for (int j = 0; j < result.size_x_; j++) {
                result.matrix_[i][j] = VectorFromRow(i).value().DotProduct(other.VectorFromRow(j).value()).value();
            }
        }
        return result;
    } else {
        // incompatible dimensions
        return {};
    }
}


template<typename T>
Matrix<T>::Matrix(const int size_y, const int size_x)
        : size_y_(size_y), size_x_(size_x), is_vector_(CheckIsVector()) {
            matrix_ = new T*[size_y];
            for (int i = 0; i < size_y; i++) {
                matrix_[i] = new T[size_x];
            }
        }

template<typename T>
std::optional<Matrix<T>> Matrix<T>::operator*(const Matrix &other) const {
    return Multiply(other);
}

template<typename T>
bool Matrix<T>::HasSameDimensions(const Matrix<T> &other) const {
    return (size_x_ == other.size_x_ && size_y_ == other.size_y_);
}

template<typename T>
bool Matrix<T>::CheckIsVector() const{
    return (size_y_ == 1 || size_x_ == 1);
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::VectorFromColumn(int column_index) const {
    if (column_index < size_x_) {
        Matrix column_vector(size_y_, 1);
        for (int i = 0; i < size_y_; i++) {
            column_vector.matrix_[i][0] = matrix_[i][column_index];
        }
        return column_vector;
    } else {
        return {};
    }
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::VectorFromRow(int row_index) const {
    if (row_index < size_y_) {
        Matrix row_vector(1, size_x_);
        for (int i = 0; i < size_x_; i++) {
            row_vector.matrix_[0][i] = matrix_[row_index][i];
        }
        return row_vector;
    } else {
        return {};
    }
}

template<typename T>
Matrix<T> Matrix<T>::Transpose() {
    Matrix transposition(size_x_, size_y_);
    for (int i = 0; i < size_y_; i++) {
        for (int j = 0; j < size_x_; j++) {
            transposition.matrix_[j][i] = matrix_[i][j];
        }
    }
    return transposition;
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::CreateMatrix(const int size_y, const int size_x, const T initial_value) {
    return Matrix(size_y, size_x, initial_value);
}

template<typename T>
bool Matrix<T>::SetValue(int index_y, int index_x, T value) {
    if (index_y < size_y_ && index_x < size_x_) {
        matrix_[index_y][index_x] = value;
        return true;
    } else {
        return false;
    }
}

template<typename T>
std::optional<T> Matrix<T>::GetValue(int index_y, int index_x) {
    if (index_y < size_y_ && index_x < size_x_) {
        return matrix_[index_y][index_x];
    } else {
        return {};
    }
}

template<typename T>
std::optional<T*> Matrix<T>::operator[](int index_y) {
    if (index_y < size_y_) {
        return matrix_[index_y];
    } else {
        return {};
    }
}

template<typename T>
std::optional<Matrix<T>> Matrix<T>::SetIdentityMatrix() {
    if (size_y_ == size_x_) {
        for (int i = 0 ; i < size_y_; i++) {
            for (int j = 0; j < size_x_; j++) {
                if (i == j) {
                    matrix_[i][j] = 1;
                } else {
                    matrix_[i][j] = 0;
                }
            }
        }
        return *this;
    } else {
        return {};
    }
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
    if (size_y_ == other.size_y_ && size_x_ == other.size_x_) {
        for (int i = 0; i < size_y_; i++) {
            for (int j = 0; j < size_x_; j++) {
                if (matrix_[i][j] != other.matrix_[i][j]) {
                    return false;
                }
            }
        }
        return true;
    } else {
        return false;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream &strm, const Matrix<T> &matrix) {
    return strm << matrix.ToString();
}

#endif //MATRIX_CPP_MATRIX_H