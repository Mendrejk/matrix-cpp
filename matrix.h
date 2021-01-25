#ifndef MATRIX_CPP_MATRIX_H
#define MATRIX_CPP_MATRIX_H

#include <stdexcept>
#include <vector>
#include <sstream>
#include <optional>
#include <iomanip>

/**
 * A class representing a two-dimensional mathematical matrix.
 */
template<typename T>
class Matrix {
private:
    const int kSizeX;
    const int kSizeY;
    T** matrix_;

    // TODO document this all
    void InitialiseMatrix(T initial_value);
    void InitialiseMatrix(std::vector<std::vector<T>> initial_vector);
    void AssertDimensions(int size_y, int size_x);
    int AssertAndGetWidth(std::vector<std::vector<T>> initial_vector);
    int AssertAndGetHeight(std::vector<std::vector<T>> initial_vector);
    // TODO document GetLongestElemLength()
    std::optional<T> GetLongestElemLength() const;
public:
    /**
     * Initialises a new empty Matrix sized size_y * size_x filled with
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
    Matrix(std::vector<std::vector<T>> initial_vector);

    // TODO implement copy constructor
    Matrix(const Matrix& other);
    // TODO implement move constructor
    Matrix(Matrix&& other);
    // TODO document this
    std::string ToString() const;
};

template<typename T>
Matrix<T>::Matrix(const int size_y, const int size_x, const T initial_value)
        : kSizeY(size_y), kSizeX(size_x) {
    // throws an invalid_argument if dimensions are not positive.
    AssertDimensions(size_y, size_x);
    InitialiseMatrix(initial_value);
}

template<typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> initial_vector)
        : kSizeY(AssertAndGetHeight(initial_vector)),
        kSizeX(AssertAndGetWidth(initial_vector)) {
    InitialiseMatrix(initial_vector);
}

template<typename T>
void Matrix<T>::AssertDimensions(const int size_y, const int size_x) {
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
int Matrix<T>::AssertAndGetHeight(std::vector<std::vector<T>> initial_vector) {
    if (initial_vector.size() < 1) {
        throw std::invalid_argument("Matrix dimensions must be positive! "
                                    "Received: "
                                    + std::to_string(initial_vector.size())
                                    + " as vector's height.");
    }
    return initial_vector.size();
}

template<typename T>
int Matrix<T>::AssertAndGetWidth(std::vector<std::vector<T>> initial_vector) {
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
    matrix_ = new T*[kSizeY];
    for (int i = 0; i < kSizeY; i++) {
        matrix_[i] = new T[kSizeX];
        for (int j = 0; j < kSizeX; j++) {
            matrix_[i][j] = initial_value;
        }
    }
}

template<typename T>
void Matrix<T>::InitialiseMatrix(
        const std::vector<std::vector<T>> initial_vector) {
    matrix_ = new T*[kSizeY];
    for (int i = 0; i < kSizeY; i++) {
        matrix_[i] = new T[kSizeX];
        for (int j = 0; j < kSizeX; j++) {
            matrix_[i][j] = initial_vector[i][j];
        }
    }
}

template<typename T>
std::optional<T> Matrix<T>::GetLongestElemLength() const {
    // initial value
    int longest_length = -1;
    std::stringstream elemString;

    for (int i = 0; i < kSizeX; i++) {
        for (int j = 0; j < kSizeY; j++) {
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
    int longest_length = GetLongestElemLength().value() + 4;

    for (int i = 0; i < kSizeY; i++) {
        for (int j = 0; j < kSizeX; j++) {
            to_string << std::right << std::setw(longest_length)
            << matrix_[i][j];
        }
        to_string << '\n';
    }
    return to_string.str();
}

template<typename T>
std::ostream& operator<<(std::ostream &strm, const Matrix<T> &matrix) {
    return strm << matrix.ToString();
}

#endif //MATRIX_CPP_MATRIX_H
