#include "../FileLoading.hpp"
#include "InputProcessing.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main(){
    // For an input of n lines :
    // loadFile = O(n)
    // processInput ~ O(n)
    // sortPairs = 2.O(n.log(n))
    // sumDistances = O(n)
    // similarityScore = O(n) + O(n) = O(2n)
    // Total : O(5n + 2.n.log(n)) ~ O(n.log(n))

    auto text = loadFile("input.txt");

    auto start = chrono::high_resolution_clock::now();

    auto pairs = processInput(text);
    sortPairs(pairs);
    int firstStar = sumDistances(pairs);
    int secondStar = similarityScore(pairs); 

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<std::chrono::microseconds>(end - start);
    double elapsed_ms = elapsed.count() / 1000.0;

    cout << "First star : " << firstStar << endl;
    cout << "Second star : " << secondStar << endl;
    cout << "Time : " << elapsed_ms << "ms" << endl;

    return 0;
}