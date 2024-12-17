#pragma once
#include <cstdint>
#include <cmath>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Program {
    int64_t A, B, C;
    vector<int64_t> out;
    vector<pair<int, int>> instructions;
    unsigned int idx;

    Program() : A(0), B(0), C(0), out({}), instructions({}), idx(0) {};

    int64_t getCombo(int combo);

    int instructionAt(int i);

    void processInstruction();

    void processAllInstructions();

    int64_t findCopy();
};