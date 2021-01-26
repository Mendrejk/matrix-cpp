#include <iostream>
#include "matrix.h"
#include <vector>

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

    std::cout << test_initial_vector.Add(test_copy).value() << std::endl;
    return 0;
}
