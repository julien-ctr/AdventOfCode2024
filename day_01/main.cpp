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

    auto start = std::chrono::steady_clock::now();

    auto pairs = processInput(text);
    sortPairs(pairs);
    int firstStar = sumDistances(pairs);
    int secondStar = similarityScore(pairs); 

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    cout << "First star : " << firstStar << endl;
    cout << "Second star : " << secondStar << endl;
    cout << "Time : " << elapsed.count() << "ms" << std::endl;

    return 0;
}