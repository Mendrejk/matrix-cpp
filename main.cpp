#include <iostream>
#include "matrix.h"
#include <vector>

int main() {
    std::cout << "Hello, World!" << std::endl;
    Matrix<int> test_initial_value(2, 1, 0);
    std::vector<std::vector<int>> test_vector =
        {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };
    Matrix<int> test_initial_vector(test_vector);
    return 0;
}
