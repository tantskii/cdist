#pragma once

#include <vector>
#include <cmath>

namespace dist {
template <typename T>
T euclidian(const std::vector<T>& lhs, const std::vector<T>& rhs);

template <typename T>
T euclidian(const std::vector<T>& lhs, const T& value);

template <typename T>
T euclidian(const T& value, const std::vector<T>& rhs);

template <typename T>
void normalize(std::vector<T>& row);
}
