#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdint>
#include "Program.hpp"

using namespace std;

// Function declarations
void loadData(const vector<string> &text, Program &prog);
pair<string, uint64_t> countStars(const vector<string> &text);