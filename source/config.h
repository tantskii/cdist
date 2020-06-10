#pragma once

#include <cstddef>
#include <stdexcept>
#include <strstream>
#include <string>
#include <filesystem>

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>


struct InputParams {
    std::string left_matrix_path;
    std::string right_matrix_path;
    std::string output_dir;
    bool normalize;
    size_t n_workers;
    
    std::vector<std::string> msg = {
        "Left matrix path", "Right matrix path", "Output directory",
        "Normalization", "Number of workers"
    };
    
    void print(std::ostream& os);
};

void InputParams::print(std::ostream& os) {
    os << msg[0] << ": " << left_matrix_path  << std::endl;
    os << msg[1] << ": " << right_matrix_path << std::endl;
    os << msg[2] << ": " << output_dir << std::endl;
    os << msg[3] << ": " << normalize << std::endl;
    os << msg[4] << ": " << n_workers << std::endl;
}


