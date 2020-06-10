#include "matrix.h"
#include "task_manager.h"

using T = double;
using LIt = matrix::Matrix<T>::It;
using RIt = matrix::Matrix<T>::It;
using MatRow = std::vector<T>;
using Callback = std::function<T (const MatRow&, const MatRow&)>;

template <>
TaskManager<LIt, RIt, Callback>::TaskManager(TaskRange<LIt, RIt> range,
                                             const std::string& dir,
                                             size_t n_workers,
                                             Callback func)
: range_(range)
, dir_(dir)
, func_(func)
, n_workers_(n_workers)
{
    workers.reserve(n_workers_);
    Range<LIt> left = range_.left();
    Range<RIt> right = range_.right();
    size_t step = left.size() / n_workers_ + 1;
    
    for (size_t i = 0; i < left.size(); i += step) {
        size_t curr_index = i;
        size_t next_index = std::min<size_t>(i + step, left.size());
        
        LIt first = std::next(left.begin(), curr_index);
        LIt last  = std::next(left.begin(), next_index);
        
        TaskRange task(first, last, right.begin(), right.end());
        
        std::string filename = get_filename(dir_, curr_index, next_index);
        
        Worker<LIt, RIt, Callback> worker(task, func_, filename);
        workers.push_back(std::move(worker));
    }
}

template <>
void TaskManager<LIt, RIt, Callback>::run() {
    for (auto& worker : workers) {
        worker.run();
    }
}


std::string get_filename(const std::string& dir, size_t index_1, size_t index_2) {
    return dir + "/" + std::to_string(index_1) + "_" + std::to_string(index_2) + ".txt";
}
