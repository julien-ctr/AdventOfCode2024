#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

// Function declarations
vector<pair<pair<int, int>, bool>> processInput(vector<string> &fileContent);
pair<int, int> addMultiplications(vector<pair<pair<int, int>, bool>> &values);