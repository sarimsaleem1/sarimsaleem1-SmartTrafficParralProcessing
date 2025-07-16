#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <chrono>

void test_sort(const std::string& method, void (*sort_func)(std::vector<int>&), std::vector<int> data) {
    auto start = std::chrono::high_resolution_clock::now();
    sort_func(data);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    
    std::cout << method << " sort time: " << duration.count() << " seconds" << std::endl;
}

void sequential_sort(std::vector<int>& data) {
    std::sort(data.begin(), data.end());
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
    std::ifstream infile("traffic_data.txt");
    int num;
    
    while (infile >> num) {
        data.push_back(num);
    }
    
    // Warm-up run
    std::vector<int> warmup = data;
    parallel_sort(warmup);
    
    // Performance tests
    std::cout << "Performance Comparison (1M elements):\n";
    test_sort("Sequential", sequential_sort, data);
    test_sort("Parallel", parallel_sort, data);
    
    return 0;
}