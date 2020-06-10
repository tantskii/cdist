#pragma once

#include "matrix.h"

#include <future>
#include <string>
#include <iostream>

namespace matrix {

template <typename T>
Matrix<T> load (std::string path);

template <typename T>
class Loader {
public:
    Loader (const std::string& path);
    Matrix<T> load();
private:
    std::future<Matrix<T>> future_;
    std::string path_;
};

}

