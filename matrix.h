#ifndef MATRIX_CPP_MATRIX_H
#define MATRIX_CPP_MATRIX_H

#include <stdexcept>
#include <vector>

/**
 * A class representing a two-dimensional mathematical matrix.
 */
template<typename T>
class Matrix {
private:
    const int kSizeX;
    const int kSizeY;
    T** matrix_;

    // TODO document this
    void InitialiseMatrix(T initial_value);
    // TODO and this
    void AssertDimensions(int size_y, int size_x);
public:
    /**
     * Initialises a new empty Matrix sized size_y * size_x filled with
     * instances of init_value.
     * An exception is thrown if either of dimensions in not positive.
     * @param size_y matrix width
     * @param size_x matrix height
     * @param init_value value to initialise matrix fields with
     */
    Matrix(int size_y, int size_x, T initial_value);

    /**
     * Initialises a new empty Matrix with values of initial_vector
     * An exception is thrown if the vector is empty or it's not a rectangle
     * @param initial_vector vector of vectors of initial values
     */
     // I opted to use a vector as opposed to a pointer here to prevent
     // undefined behaviour when given size is larger than array's length
     // TODO implement vector constructor
    Matrix(std::vector<std::vector<T>> initial_vector);
    // TODO implement copy constructor
    Matrix(const Matrix& other);
    // TODO implement move constructor
    Matrix(Matrix&& other);
};

template<typename T>
Matrix<T>::Matrix(const int size_y, const int size_x, const T initial_value)
  : kSizeY(size_y), kSizeX(size_x) {
    // throws an invalid_argument if dimensions are not positive.
    AssertDimensions(size_y, size_x);

    InitialiseMatrix(initial_value);
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
void Matrix<T>::InitialiseMatrix(const T initial_value) {
    matrix_ = new T*[kSizeY];
    for (int i = 0; i < kSizeY; i++) {
        matrix_[i] = new T[kSizeX];
        for (int j = 0; j < kSizeX; j++) {
            matrix_[i][j] = initial_value;
        }
    }
}

#endif //MATRIX_CPP_MATRIX_H
