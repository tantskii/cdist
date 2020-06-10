#pragma once

#include <algorithm>

template <typename It>
class Range {
public:
    Range(It first, It last) : first(first), last(last) {
    }

    It begin() const {
        return first;
    }

    It end() const {
        return last;
    }

    size_t size() const {
        return last - first;
    }

private:
    It first, last;
};

template <typename Container>
auto head(Container& c, int top) {
    return Range(c.begin(), std::next(c.begin(), std::min<size_t>(std::max(top, 0), c.size())));
}
