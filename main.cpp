#include <iostream>
#include "matrix.h"
#include <vector>

int main() {
    std::cout << "Hello, World!" << std::endl;
    Matrix<int> test_initial_value(2, 1, 0);
    std::vector<std::vector<int>> test_vector =
        {
            {1, 24781237, 3},
            {4, 5, 6},
            {7, 8, 9},
            {9, -43141, 71}
        };
    Matrix<int> test_initial_vector(test_vector);
    std::cout << test_initial_vector << std::endl;
    return 0;
}
