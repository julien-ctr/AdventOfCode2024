#include "../FileLoading.hpp"
#include "InputProcessing.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main(){
    auto text = loadFile("../inputs/day_20.txt");
    
    auto start = chrono::high_resolution_clock::now();

    pair<int64_t, int64_t> stars = countStars(text);
    int64_t firstStar = stars.first;
    int64_t secondStar = stars.second;

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::microseconds>(end - start);
    double elapsed_ms = elapsed.count() / 1000.0;

    cout << "First star : " << std::fixed << std::setprecision(0) << firstStar << endl;
    cout << "Second star : " << std::fixed << std::setprecision(0) << secondStar << endl;
    cout << "Time : " << std::fixed << std::setprecision(3) << elapsed_ms << "ms" << std::endl;

    return 0;
}