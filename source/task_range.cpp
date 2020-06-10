#include "task_range.h"
#include "matrix.h"

using T = double;
using LIt = matrix::Matrix<T>::It;
using RIt = matrix::Matrix<T>::It;

template <>
TaskRange<LIt, RIt>::TaskRange(LIt lfirst, LIt llast, RIt rfirst, RIt rlast)
: lrange_(lfirst, llast)
, rrange_(rfirst, rlast)
{
}

template <>
Range<LIt> TaskRange<LIt, RIt>::left() const
{
    return lrange_;
}

template <>
Range<RIt> TaskRange<LIt, RIt>::right() const
{
    return rrange_;
}

