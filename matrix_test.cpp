#include "matrix.h"

namespace matrix_test {
    bool TestAdd() {
        Matrix<int> matrix_base(3, 5, -4);
        Matrix<int> matrix_same_dimensions(3, 5, 6);
        Matrix<int> matrix_different_dimensions(5, 3, 4);

        std::optional<Matrix<int>> test_succeed =
            matrix_base + matrix_same_dimensions;
        std::optional<Matrix<int>> test_fail =
            matrix_base + matrix_different_dimensions;

        return test_succeed.has_value()
                && test_succeed.value()
                    == Matrix<int>(3, 5, 2)
                && !test_fail.has_value();
    }

    bool TestSubtract() {
        Matrix<int> matrix_base(3, 5, -4);
        Matrix<int> matrix_same_dimensions(3, 5, 6);
        Matrix<int> matrix_different_dimensions(5, 3, 4);

        std::optional<Matrix<int>> test_succeed =
                matrix_base - matrix_same_dimensions;
        std::optional<Matrix<int>> test_fail =
                matrix_base - matrix_different_dimensions;

        return test_succeed.has_value()
            && test_succeed.value()
                == Matrix<int>(3, 5, -10)
            && !test_fail.has_value();
    }

    bool TestMultiplyNumber() {
        Matrix<double> matrix_base(4, 3, 8);
        double multiplier = 2.5;

        return matrix_base * multiplier
            == Matrix<double>(4, 3, 20.0);
    }

    bool TestMultiplyMatrixMatrix() {
        std::vector<std::vector<int>> vector_base =
            {
                {1, 2, 3},
                {4, 5, 6}
            };
        std::vector<std::vector<int>> vector_succeed =
            {
                {7, 8},
                {9, 10},
                {11, 12}
            };
        std::vector<std::vector<int>> vector_result =
            {
                    {58, 64},
                    {139, 154}
            };
        std::vector<std::vector<int>> vector_fail =
            {
                {7, 8, 9},
                {10, 11, 12}
            };
        Matrix<int> matrix_base(vector_base);
        Matrix<int> matrix_succeed(vector_succeed);
        Matrix<int> matrix_result(vector_result);
        Matrix<int> matrix_fail(vector_fail);

        std::optional<Matrix<int>> test_succeed = matrix_base * matrix_succeed;
        std::optional<Matrix<int>> test_fail = matrix_base * matrix_fail;
        return test_succeed.has_value() && test_succeed.value() == matrix_result
            && !test_fail.has_value();
    }

    bool TestMultiplyVectorMatrix() {
        std::vector<std::vector<int>> vector_base =
            {
                {3, 4, 2}
            };
        std::vector<std::vector<int>> vector_succeed =
            {
                {13, 9, 7, 15},
                {8, 7, 4, 6},
                {6, 4, 0, 3}
            };
        std::vector<std::vector<int>> vector_result =
            {
                {83, 63, 37, 75}
            };
        std::vector<std::vector<int>> vector_fail =
            {
                {6, 8, 13},
                {4, 7, 9},
                {0, 4, 7},
                {3, 6, 15}
            };
        Matrix<int> matrix_base(vector_base);
        Matrix<int> matrix_succeed(vector_succeed);
        Matrix<int> matrix_result(vector_result);
        Matrix<int> matrix_fail(vector_fail);

        std::optional<Matrix<int>> test_succeed = matrix_base * matrix_succeed;
        std::optional<Matrix<int>> test_fail = matrix_base * matrix_fail;
        return test_succeed.has_value() && test_succeed.value() == matrix_result
            && !test_fail.has_value();
    }

    bool TestDotProduct() {
        std::vector<std::vector<int>> vector_base =
            {
                {2},
                {3},
                {-4},
                {-5}
            };
        std::vector<std::vector<int>> vector_succeed =
            {
                {-3, 6, -10, 12}
            };
        std::vector<std::vector<int>> vector_fail =
            {
                {2, 4, 8, 16},
                {32, 64, 128, 256}
            };
        Matrix<int> matrix_base(vector_base);
        Matrix<int> matrix_succeed(vector_succeed);
        Matrix<int> matrix_fail(vector_fail);

        std::optional<int> test_succeed =
            matrix_base.DotProduct(matrix_succeed);
        std::optional<int> test_fail = matrix_base.DotProduct(matrix_fail);
        return (test_succeed.has_value() && test_succeed.value() == -8
            && !test_fail.has_value());
    }

    bool TestTranspose() {
        std::vector<std::vector<float>> vector_test =
            {
                {7.1, -17.0, 37.2, 57.24, -7.7},
                {5.55, 3.33, -214.12, 3.14, -2.71}
            };
        std::vector<std::vector<float>> vector_result =
            {
                {7.1, 5.55},
                {-17.0, 3.33},
                {37.2, -214.12},
                {57.24, 3.14},
                {-7.7, -2.71}
            };
        Matrix<float> matrix_test(vector_test);
        Matrix<float> matrix_result(vector_result);

        return matrix_test.Transpose() == matrix_result;
    }

    bool TestReadFromFile() {
        std::string path_int = R"(data_int.txt)";
        std::string path_float = R"(data_float.txt)";
        std::string path_double = R"(data_double.txt)";

        std::optional<std::vector<std::vector<int>>> result_int =
            file_io::LoadMatrix2D<int>(path_int);
        std::optional<std::vector<std::vector<float>>> result_float =
            file_io::LoadMatrix2D<float>(path_float);
        std::optional<std::vector<std::vector<double>>> result_double =
            file_io::LoadMatrix2D<double>(path_double);

        std::vector<std::vector<int>> vector_int =
            {
                {116, 101, 115, 116},
                {100, 97, 116, 97},
                {104, 101, 114, 101}
            };
        std::vector<std::vector<float>> vector_float =
            {
                {2.7, 1.8},
                {2.8, 1.8},
                {2.8, 4.6},
                {-3.1, -4.1},
                {-5.9, -2.6}
            };
        std::vector<std::vector<double>> vector_double =
            {
                {1.12358132134, 4.31231853211, -1.41421356237, 1.73205080757}
            };
        return result_int.has_value() && result_int.value() == vector_int &&
            result_float.has_value() && result_float.value() == vector_float &&
            result_double.has_value() && result_double.value() == vector_double;
    }

    bool TestGetValue() {
        std::vector<std::vector<double>> vector_test =
            {
                {1.1, -3.3, 5.5, -7.7},
                {9.9, -11.11, 13.13, -15.15}
            };
        return vector_test[1][2] == 13.13;
    }

    bool TestSetValue() {
        std::vector<std::vector<double>> vector_test =
            {
                {1.1, -3.3, 5.5, -7.7},
                {9.9, -11.11, 13.13, -15.15}
            };
        vector_test[1][2] = -412.15;
        return vector_test[1][2] == -412.15;
    }

    bool TestVectorFromColumn() {
        std::vector<std::vector<int>> vector_test =
            {
                {1, 24781237, 3},
                {4, 5, 6},
                {7, 8, 9},
                {9, -43141, 71}
            };
        std::vector<std::vector<int>> vector_result =
            {
                {3},
                {6},
                {9},
                {71}
            };
        Matrix<int> matrix_test(vector_test);
        Matrix<int> matrix_result(vector_result);

        std::optional<Matrix<int>> test_succeed =
            matrix_test.VectorFromColumn(2);
        std::optional<Matrix<int>> test_fail =
            matrix_test.VectorFromColumn(3);
        return test_succeed.has_value() && test_succeed.value() == matrix_result
            && !test_fail.has_value();
    }

    bool TestIdentityMatrix() {
        std::vector<std::vector<int>> vector_succeed =
            {
                {12, 13, 14, 15},
                {16, 17, 18, 19},
                {-1, -2, -3, -4},
                {-213, 41, 1, -1}
            };
        std::vector<std::vector<int>> vector_fail =
            {
                {1, 2, 3},
                {4, 5, 6}
            };
        std::vector<std::vector<int>> vector_result =
            {
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}
            };
        Matrix<int> matrix_succeed(vector_succeed);
        Matrix<int> matrix_fail(vector_fail);
        Matrix<int> matrix_result(vector_result);

        std::optional<Matrix<int>> test_succeed =
            matrix_succeed.SetIdentityMatrix();
        std::optional<Matrix<int>> test_fail = matrix_fail.SetIdentityMatrix();
        return (test_succeed.has_value()
            && test_succeed.value() == matrix_result
            && !test_fail.has_value());
    };
}