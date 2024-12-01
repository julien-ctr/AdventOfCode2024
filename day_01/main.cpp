#include "../FileLoading.hpp"
#include "InputProcessing.hpp"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main(){
    // For an input of n lines :
    // loadFile = O(n)
    // processInput ~ O(n)
    // sortPairs = O(n) + O(n.log(n)) + O(n) = O(2n + n.log(n))
    // sumDistances = O(n)
    // similarityScore = O(n) + O(n) = O(2n)
    // Total : O(7n + n.log(n)) ~ O(n.log(n))

    auto text = loadFile("input.txt");
    auto pairs = processInput(text);
    sortPairs(pairs);
    int firstStar = sumDistances(pairs);
    int secondStar = similarityScore(pairs); 

    cout << "First star : " << firstStar << endl;
    cout << "Second star : " << secondStar << endl;

    return 0;
}