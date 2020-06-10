#pragma once

#include <future>
#include <string>
#include <fstream>
#include <functional>
#include <vector>
#include <iostream>

#include "task_range.h"

template <typename LIt, typename RIt, typename Callback>
void init_future(Range<LIt> left, Range<RIt> right, Callback func, const std::string& path);

template <typename LIt, typename RIt, typename Callback>
class Worker {
public:
    Worker (TaskRange<LIt, RIt>, Callback, const std::string);
    void run();
private:
    std::future<void> future_;
};
