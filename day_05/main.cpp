#include "../FileLoading.hpp"
#include "InputProcessing.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

int main(){
    // For an input of n rules, and m updates :
    // loadFile = O(n) + O(m)
    // loadData ~ O(n + m)
    // For an average of k elements in an update, and r elements in rule[val] :
    // isValidUpdate ~ O(k.r)
    // sortUpdate ~ O(k.log(k).r)
    // countStars ~ O(m. (k.r + k.log(k) + r)) ~ O(m.k.r.log(k))
    // Total ~ O(m.k.r.log(k))

    auto text = loadFile("input.txt");
    
    auto start = chrono::high_resolution_clock::now();
    unordered_map<int, vector<int>> myMap;
    vector<vector<int>> myV;
    loadData(text, myMap, myV);

    pair<int, int> stars = countStars(myMap, myV);
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