#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>

using namespace std;

// Function declarations
pair<vector<int>, vector<int>> processInput(vector<string> &fileContent);
void sortPairs(pair<vector<int>, vector<int>> &pairs);
int sumDistances(pair<vector<int>, vector<int>> &pairs);
int similarityScore(pair<vector<int>, vector<int>> &pairs);