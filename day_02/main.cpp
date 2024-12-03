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
    // isSafe ~ O(n)
    // isAlmostSafe ~ O(n.k²)
    // countValid ~ O(n.k)
    // countValid2 ~ O(n.k²)
    // Overall : O(n.k²)

    auto text = loadFile("input.txt");

    auto start = chrono::high_resolution_clock::now();

    auto values = processInput(text);
    unsigned int firstStar = countValid1(values);
    unsigned int secondStar = countValid2(values);

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::microseconds>(end - start);
    double elapsed_ms = elapsed.count() / 1000.0;


    cout << "First star : " << firstStar << endl;
    cout << "Second star : " << secondStar << endl;
    cout << "Time : " << elapsed_ms << "ms" << endl;

    return 0;
}