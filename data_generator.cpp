#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

void generate_data(const std::string& filename, long size) {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }

    srand(static_cast<unsigned>(time(nullptr)));
    for (long i = 0; i < size; ++i) {
        outfile << rand() % 1000000 << "\n";
    }

    std::cout << "Generated " << size << " random numbers in " << filename << std::endl;
}

int main() {
    const std::string filename = "traffic_data.txt";
    const long data_size = 1000000; // 1 million entries
    
    generate_data(filename, data_size);
    return 0;
}