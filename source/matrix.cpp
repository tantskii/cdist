#include "matrix.h"

using T = double;
using MatRow = std::vector<T>;

namespace matrix {
template<>
Matrix<T>::Matrix(std::vector<MatRow> data)
: data_(std::move(data))
{
    nRows_    = data_.size();
    nColumns_ = data_[0].size();
}

template<>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) {
    std::swap(data_,     other.data_);
    std::swap(nColumns_, other.nColumns_);
    std::swap(nRows_,    other.nRows_);
    return *this;
}

template<>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    data_     = other.data_;
    nColumns_ = other.nColumns_;
    nRows_    = other.nRows_;
    return *this;
}

template<>
typename Matrix<T>::It Matrix<T>::begin()
{
    return data_.begin();
}

template<>
typename Matrix<T>::It Matrix<T>::end()
{
    return data_.end();
}

template<>
Matrix<T>::Matrix(size_t n_rows, size_t n_columns)
: nRows_    (n_rows)
, nColumns_ (n_columns)
, data_     (n_rows, std::vector<T>(n_columns))
{
}

template<>
Matrix<T>::Matrix(Matrix<T>&& other)
: nRows_    (std::move(other.nRows_))
, nColumns_ (std::move(other.nColumns_))
, data_     (std::move(other.data_))
{
}

template<>
std::vector<T>& Matrix<T>::operator[] (size_t idx)
{
    return data_[idx];
}

template<>
const std::vector<T>& Matrix<T>::operator[] (size_t idx) const
{
    return data_[idx];
}


template<>
MatrixError Matrix<T>::load_txt(const std::string& path)
{
    std::ifstream infile(path);
    std::string line;
    size_t i = 0;
    while (std::getline(infile, line)) {
        size_t j = 0;
        std::istringstream iss(line);
        std::vector<T>& row = data_[i];
        T value;

        while (iss >> value) {
            row[j] = value;
            j++;
        }

        if (j != nColumns_) {
            return MatrixError::INCORRECT_COLUMN_NUMBER;
        }
        
        i++;
    }
    
    if (i != nRows_) {
        return MatrixError::INCORRECT_ROW_NUMBER;
    }
    
    return MatrixError::OK;
}

template<>
MatrixError Matrix<T>::save_txt(const std::string& path)
{
    std::ofstream file(path, std::ios_base::app);
    if (file.is_open()) {
        for (const auto& row : data_) {
            for (const auto& value : row) {
                file << value << ' ';
            }
            file << '\n';
        }
        file.close();
        return MatrixError::OK;
    } else {
        return MatrixError::FILE_NOT_FOUND;
    }
}

template<>
size_t Matrix<T>::getRowsCount() {
    return nRows_;
}

template<>
size_t Matrix<T>::getColumnCount(){
    return nColumns_;
}

}
