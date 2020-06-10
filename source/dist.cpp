#include "dist.h"

using T = double;

namespace dist {
template <>
T euclidian(const std::vector<T>& lhs, const std::vector<T>& rhs)
{
    // TODO throw exception if len(lhs) != len(rhs)
    T distance = 0;
    for (size_t i = 0; i < lhs.size(); i++) {
        T difference = lhs[i] - rhs[i];
        distance += difference * difference;
    }
    
    return sqrt(distance);
}

template <>
T euclidian(const std::vector<T>& lhs, const T& value)
{
    // TODO throw exception if len(lhs) != len(rhs)
    T distance = 0;
    for (size_t i = 0; i < lhs.size(); i++) {
        T difference = lhs[i] - value;
        distance += difference * difference;
    }
    
    return sqrt(distance);
}

template <>
T euclidian(const T& value, const std::vector<T>& rhs)
{
    // TODO throw exception if len(lhs) != len(rhs)
    return euclidian(rhs, value);
}

template <>
void normalize(std::vector<T>& row) {
    T norm = euclidian(row, static_cast<T>(0));
    if (norm > 0) {
        for (size_t i = 0; i < row.size(); i++) {
            row[i] /= norm;
        }
    }
}
}
