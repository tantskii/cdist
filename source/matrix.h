#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

namespace matrix {
enum class MatrixError {
    INCORRECT_COLUMN_NUMBER,
    INCORRECT_ROW_NUMBER,
    FILE_NOT_FOUND,
    OK
};

template <typename T>
class Matrix
{
public:
    using It = typename std::vector<std::vector<T>>::iterator;
    
    Matrix (size_t n_row = 0, size_t n_columns = 0);
    Matrix (std::vector<std::vector<T>>);
    Matrix (Matrix<T>&&);
    
    Matrix<T>& operator= (Matrix<T>&&);
    Matrix<T>& operator= (const Matrix<T>&);
    
    
    std::vector<T>& operator[] (size_t i);
    const std::vector<T>& operator[] (size_t i) const;
    
    MatrixError load_txt (const std::string& path);
    MatrixError save_txt (const std::string& path);
    
    It begin();
    It end();
    
    size_t getRowsCount   ();
    size_t getColumnCount ();
    
private:
    size_t nRows_;
    size_t nColumns_;
    std::vector<std::vector<T>> data_;
};
}



