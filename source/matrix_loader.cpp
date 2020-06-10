#include "matrix_loader.h"

using T = double;

namespace matrix {
template<>
Matrix<T> load(std::string path) {
    std::ifstream infile(path);
    std::string line;
    size_t n_cols = 0;
    std::vector<std::vector<T>> data;
    
    for (size_t i = 0; std::getline(infile, line); i++) {
        std::istringstream iss(line);
        std::vector<T> row;
        row.reserve(n_cols);
        T value;

        for (size_t j = 0; iss >> value; j++) {
            row.push_back(value);
        }
        
        if (i == 0) {
            n_cols = row.size();
        } else if (row.size() != n_cols) {
            std::cerr << "MatrixError::INCORRECT_COLUMN_NUMBER in ";
            std::cerr << path << std::endl;
            exit(1);
        }
        data.push_back(std::move(row));
    }
    
    return Matrix<T>(std::move(data));
}


template<>
Loader<T>::Loader(const std::string& path)
: future_(async(matrix::load<T>, path))
, path_(path)
{
}

template<>
Matrix<T> Loader<T>::load() {
    return future_.get();
}

}
