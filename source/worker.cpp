#include "worker.h"
#include "matrix.h"

using T = double;
using LIt = matrix::Matrix<T>::It;
using RIt = matrix::Matrix<T>::It;
using MatRow = std::vector<T>;
using Callback = std::function<T (const MatRow&, const MatRow&)>;

template <>
void init_future(Range<LIt> left, Range<RIt> right, Callback func, const std::string& path)
{
    std::ofstream file(path, std::ios_base::out);
    try {
        if (file.is_open()) {
            for (const auto& left_elem : left) {
                for (const auto& right_elem : right) {
                    file << func(left_elem, right_elem) << ' ';
                }
                file << '\n';
            }
            file.close();
        } else {
            std::cerr << "FileNotFound: can't create " << path << std::endl;
            exit(2);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(2);
    }
}

template <>
Worker<LIt, RIt, Callback>::Worker(TaskRange<LIt, RIt> range, Callback func, const std::string path)
    : future_(std::async(init_future<LIt,  RIt, Callback>,
              range.left(), range.right(), func, path))
{
}

template <>
void Worker<LIt, RIt, Callback>::run() {
    future_.get();
}

