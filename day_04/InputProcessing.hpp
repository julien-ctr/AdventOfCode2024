#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <regex>

using namespace std;

// Function declarations
bool isValidXMAS(const vector<string> &text, string word, unsigned int line, unsigned int col, int dx, int dy);
bool isValidCrossMAS(const vector<string> &text, int line, int col);
pair<int, int> countXMAS(const vector<string> &text);
