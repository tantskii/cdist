#pragma once

#include "range.h"

template <typename LeftIt, typename RightIt>
class TaskRange {
public:
    TaskRange(LeftIt lfirst, LeftIt llast, RightIt rfirst, RightIt rlast);
    Range<LeftIt> left() const;
    Range<RightIt> right() const;
private:
    const Range<LeftIt>  lrange_;
    const Range<RightIt> rrange_;
};
