#include <iostream>
#include <vector>
#include "matrix.h"
#include "file_io.cpp"
#include "matrix_test.cpp"

int main() {
    Matrix<int> test_initial_value(4, 3, -1);
    std::vector<std::vector<int>> test_vector =
        {
            {1, 24781237, 3},
            {4, 5, 6},
            {7, 8, 9},
            {9, -43141, 71}
        };
    Matrix<int> test_initial_vector(test_vector);
    std::cout << test_initial_vector << std::endl;
    Matrix<int> test_copy(test_initial_vector);
    test_copy = test_initial_value;
    std::cout << test_copy << std::endl;

    std::cout << test_initial_vector.Add(test_copy).value()
                 .Add(test_copy).value() << std::endl;
    std::cout << ((test_initial_vector - test_copy).value()
                 - test_copy).value() << std::endl;

    ((test_initial_vector + test_copy).value() + test_copy).value();

    // TESTS
    std::cout << matrix_test::TestAdd() << " - TestAdd()\n" << std::endl;
    std::cout << matrix_test::TestSubtract() << " - TestSubtract()\n" << std::endl;
    std::cout << matrix_test::TestMultiplyNumber() << " - TestMultiplyNumber()\n" << std::endl;
    std::cout << matrix_test::TestMultiplyMatrixMatrix() << " - TestMultiplyMatrixMatrix()\n" << std::endl;
    std::cout << matrix_test::TestMultiplyVectorMatrix() << " - TestMultiplyVectorMatrix()\n" << std::endl;
    std::cout << matrix_test::TestDotProduct() << " - TestDotProduct()\n" << std::endl;
    std::cout << matrix_test::TestTranspose() << " - TestTranspose()\n" << std::endl;
    std::cout << matrix_test::TestReadFromFile() << " - TestReadFromFile()\n" << std::endl;
    std::cout << matrix_test::TestGetValue() << " - TestGetValue()\n" << std::endl;
    std::cout << matrix_test::TestSetValue() << " - TestSetValue()\n" << std::endl;
    std::cout << matrix_test::TestVectorFromColumn() << " - TestVectorFromColumn()\n" << std::endl;
    std::cout << matrix_test::TestIdentityMatrix() << " - TestIdentityMatrix()\n" << std::endl;

    return 0;
}
