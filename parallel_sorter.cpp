#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <chrono>

void read_data(const std::string& filename, std::vector<int>& data) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }

    int num;
    while (infile >> num) {
        data.push_back(num);
    }
}

void write_data(const std::string& filename, const std::vector<int>& data) {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }

    for (const auto& num : data) {
        outfile << num << "\n";
    }
}

void parallel_sort(std::vector<int>& data) {
    #pragma omp parallel
    {
        #pragma omp single nowait
        std::sort(data.begin(), data.end());
    }
}

int main() {
    std::vector<int> data;
    
    // Read input data
    read_data("traffic_data.txt", data);
    
    // Time parallel sorting
    auto start = std::chrono::high_resolution_clock::now();
    parallel_sort(data);
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calculate duration
    std::chrono::duration<double> duration = end - start;
    
    // Write sorted data
    write_data("sorted_data.txt", data);
    
    std::cout << "Parallel sorting completed in " << duration.count() << " seconds" << std::endl;
    std::cout << "Using " << omp_get_max_threads() << " threads" << std::endl;
    
    return 0;
}