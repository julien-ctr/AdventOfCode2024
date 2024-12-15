#include "../FileLoading.hpp"
#include "InputProcessing.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main(){
    auto text = loadFile("test.txt");
    
    auto start = chrono::high_resolution_clock::now();

    pair<uint64_t, uint64_t> stars = countStars(text);
    uint64_t firstStar = stars.first;
    uint64_t secondStar = stars.second;

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::microseconds>(end - start);
    double elapsed_ms = elapsed.count() / 1000.0;

    cout << "First star : " << std::fixed << std::setprecision(0) << firstStar << endl;
    cout << "Second star : " << std::fixed << std::setprecision(0) << secondStar << endl;
    cout << "Time : " << std::fixed << std::setprecision(3) << elapsed_ms << "ms" << std::endl;

    return 0;
}