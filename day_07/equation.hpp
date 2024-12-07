#pragma once
#include <vector>
#include <iostream>
#include <cstdint>
#include <cmath>

class Equation {
    private:
        int64_t result;
        std::vector<int64_t> numbers;
    public:
        Equation();
        Equation(int64_t x);
        void addNumber(int64_t x);

        bool solvable(bool concat = false);

        int64_t getResult() const;

        void log();
};

int64_t concatenate(int64_t i, int64_t j);
bool endsWith(int64_t x, int64_t y);
int64_t cut(int64_t x, int64_t y);
bool recSolve(std::vector<int64_t> &numbers, unsigned int idx, int64_t currentResult, int64_t target, bool canConcat = false);
bool recSolveBack(std::vector<int64_t> &numbers, unsigned int idx, int64_t currentResult, int64_t target, bool canConcat = false);