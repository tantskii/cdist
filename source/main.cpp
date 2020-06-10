#include <iostream>
#include <algorithm>
#include <iomanip>

#include "task_range.h"
#include "matrix.h"
#include "matrix_loader.h"
#include "dist.h"
#include "config.h"
#include "profile.h"
#include "task_manager.h"

using dtype = double;
using MatIt = matrix::Matrix<dtype>::It;
using MatRow = std::vector<dtype>;
using Callback = std::function<dtype (const MatRow&, const MatRow&)>;

int main(int argc, const char * argv[]) {
//    if (argc != 6) {
//        cout << "Argument Error: To few arguments (got " << argc << ", but expected 6)" << endl;
//        exit(3);
//    }
//
//    InputParams params = {
//        .left_matrix_path   = argv[1],
//        .right_matrix_path  = argv[2],
//        .output_dir         = argv[3],
//        .normalize          = static_cast<bool>(stoi(argv[4])),
//        .n_workers          = static_cast<size_t>(stoi(argv[5])),
//    };
//    
    InputParams params = {
        .left_matrix_path   = "/Users/tihonsergienko/Work/tmp/lm_1k.txt",
        .right_matrix_path  = "/Users/tihonsergienko/Work/tmp/rm_1k.txt",
        .output_dir         = "/Users/tihonsergienko/Work/tmp/output",
        .normalize          = true,
        .n_workers          = 4,
    };
    params.print(cout);
    
    matrix::Matrix<dtype> l_matrix;
    matrix::Matrix<dtype> r_matrix;
    matrix::Loader<dtype> l_matrix_loader(params.left_matrix_path);
    matrix::Loader<dtype> r_matrix_loader(params.right_matrix_path);
    {
        LOG_DURATION("Loading matrix");
        l_matrix = l_matrix_loader.load();
        r_matrix = r_matrix_loader.load();
    }
    
    if (params.normalize) {
        LOG_DURATION("Normalization");
        std::for_each(l_matrix.begin(), l_matrix.end(), dist::normalize<dtype>);
        std::for_each(r_matrix.begin(), r_matrix.end(), dist::normalize<dtype>);
    }
    
    TaskRange task_range(l_matrix.begin(), l_matrix.end(), r_matrix.begin(), r_matrix.end());
    Callback callback = [] (const MatRow& lhs, const MatRow& rhs) {
        return dist::euclidian<dtype>(lhs, rhs);
    };
    TaskManager<MatIt, MatIt, Callback> tm(task_range, params.output_dir, params.n_workers, callback);

    {
        LOG_DURATION("Calculating distances");
        tm.run();
    }
    
    return 0;
}
