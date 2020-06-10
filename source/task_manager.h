#pragma once

#include <algorithm>

#include "task_range.h"
#include "worker.h"

std::string get_filename(const std::string& dir, size_t index_1, size_t index_2);

template <typename LIt, typename RIt, typename Callback>
class TaskManager {
public:
    TaskManager(TaskRange<LIt, RIt>, const std::string&, size_t, Callback);
    void run();
private:
    std::vector<Worker<LIt, RIt, Callback>> workers;
    const TaskRange<LIt, RIt> range_;
    const std::string dir_;
    Callback func_;
    size_t n_workers_;
};
