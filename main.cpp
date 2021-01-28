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

    std::cout << test_initial_vector.Add(test_copy).value()
                 .Add(test_copy).value() << std::endl;
    std::cout << ((test_initial_vector - test_copy).value()
                 - test_copy).value() << std::endl;

    ((test_initial_vector + test_copy).value() + test_copy).value();

    std::cout << test_initial_vector * -3 << std::endl;

    std::vector<std::vector<int>> v_0 =
        {
            {2},
            {3},
            {-4},
            {-5}
        };
    std::vector<std::vector<int>> v_1 =
        {
            {-3, 6, -10, 12}
        };
    Matrix<int> test_vector_zero(v_0);
    Matrix<int> test_vector_one(v_1);
    std::cout << test_vector_zero.DotProduct(test_vector_one).value() << std::endl;

    // test mult matrix
    std::vector<std::vector<int>> m_0 =
        {
            {1, 2, 3},
            {4, 5, 6}
        };
    std::vector<std::vector<int>> m_1 =
        {
            {7, 8},
            {9, 10},
            {11, 12}
        };
    Matrix<int> test_m_0(m_0);
    Matrix<int> test_m_1(m_1);
    std::cout << test_m_1.VectorFromRow(1).value() << std::endl;
    std::cout << test_m_0.Multiply(test_m_1).value() << std::endl;

    // v * m
    std::vector<std::vector<int>> v_vtm =
        {
            {3, 4, 2}
        };
    std::vector<std::vector<int>> m_vtm =
        {
            {13, 9, 7, 15},
            {8, 7, 4, 6},
            {6, 4, 0, 3}
        };
    Matrix<int> m_v_vtm(v_vtm);
    Matrix<int> m_m_vtm(m_vtm);
    std::cout << (m_v_vtm * m_m_vtm).value() << std::endl;
    std::cout << std::endl;

    std::cout << test_initial_vector.Transpose() << std::endl;

    Matrix<int> test_create = Matrix<int>::CreateMatrix(3, 3, 2).value();
    std::cout << test_create[0].value()[1] << std::endl;
    test_create[1].value()[1] = -17;
    std::cout << test_create << std::endl;
    std::cout << test_create.SetIdentityMatrix().value() << std::endl;

    return 0;
}
