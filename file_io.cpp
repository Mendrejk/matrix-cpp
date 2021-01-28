#include <optional>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace file_io {
    template<typename T>
    std::optional<std::vector<std::vector<T>>> LoadMatrix2D(std::string file_name) {
        std::vector<std::vector<T>> out;
        std::ifstream file(file_name);

        std::string row;
        while (std::getline(file, row)) {
            std::vector<T> temp_vector;
            std::istringstream stream(row);

            T temp_value;
            while (stream >> temp_value) {
                temp_vector.push_back(temp_value);
            }
            out.push_back(temp_vector);
        }

        // FIXME this check probably should not be here
        // check if it's a rectangle
        if (out.size() > 0 && out[0].size() > 0) {
            int size_x = out[0].size();
            for (int i = 1; i < out.size(); i++) {
                if (out[i].size() != size_x) {
                    return {};
                }
            }
            return out;
        } else {
            return {};
        }
    }
}