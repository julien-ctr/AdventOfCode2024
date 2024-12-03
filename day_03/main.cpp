#include "../FileLoading.hpp"
#include "InputProcessing.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main(){
    // For an input of n lines, each containing an average of m characters :
    // loadFile = O(n)
    // processInput ~ O(n.m²)
    // addMultiplications = O(n)
    // Total : O(n.m²)

    auto text = loadFile("input.txt");

    auto start = chrono::high_resolution_clock::now();

    auto values = processInput(text);

    auto stars = addMultiplications(values);
    int firstStar = stars.first;
    int secondStar = stars.second;

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::microseconds>(end - start);
    double elapsed_ms = elapsed.count() / 1000.0;

    cout << "First star : " << firstStar << endl;
    cout << "Second star : " << secondStar << endl;
    cout << "Time : " << elapsed_ms << "ms" << std::endl;

    return 0;
}