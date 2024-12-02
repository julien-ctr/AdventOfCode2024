#include "../FileLoading.hpp"
#include "InputProcessing.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main(){
    // For an input of n lines, each containing k numbers :
    // loadFile = O(n)
    // processInput ~ O(n)
    // calculateDiffs ~ O(n.k)
    // countValid ~ O(n.k)
    // countValid2 ~ O(n.k²)
    // Overall : O(n.k²)

    auto text = loadFile("input.txt");

    auto start = std::chrono::steady_clock::now();

    auto values = processInput(text);
    auto diff = calculateDiffs(values);
    unsigned int firstStar = countValid1(diff);
    unsigned int secondStar = countValid2(values, diff);
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    cout << "First star : " << firstStar << endl;
    cout << "Second star : " << secondStar << endl;
    cout << "Time : " << elapsed.count() << "ms" << std::endl;

    return 0;
}