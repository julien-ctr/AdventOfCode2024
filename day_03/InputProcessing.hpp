#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

enum MulState {
    MUL_START,
    MUL_M,
    MUL_MU,
    MUL_MUL,
    MUL_OPEN_PARENTHESIS,
    MUL_NUMBER_1,
    MUL_COMMA,
    MUL_NUMBER_2,
    MUL_CLOSE_PARENTHESIS,
    MUL_FOUND
};

enum DoState {
    DO_START,
    DO_D,
    DO_DO,
    DO_OPEN_PARENTHESIS,
    DO_CLOSE_PARENTHESIS,
    DO_FOUND
};

enum DontState {
    DONT_START,
    DONT_D,
    DONT_DO,
    DONT_DON,
    DONT_DON_,
    DONT_DON_T,
    DONT_OPEN_PARENTHESIS,
    DONT_CLOSE_PARENTHESIS,
    DONT_FOUND
};

// Function declarations
vector<pair<pair<int, int>, bool>> processInputRegex(vector<string> &fileContent);
vector<pair<pair<int, int>, bool>> processInputStateMachine(vector<string> &fileContent);
pair<int, int> addMultiplications(vector<pair<pair<int, int>, bool>> &values);