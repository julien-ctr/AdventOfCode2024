#include "equation.hpp"

using namespace std;

Equation::Equation() :
    result(0),
    numbers({}) {
}

Equation::Equation(int64_t x):
    result(x),
    numbers({}) {
}

void Equation::addNumber(int64_t x) {
    numbers.push_back(x);
}

int64_t concatenate(int64_t i, int64_t j) {
    int64_t n = j;
    int k = 1;
    while (n > 0) {
        n /= 10;
        k *= 10;
    }
    return k*i+j;
}

bool recSolve(vector<int64_t> &numbers, unsigned int idx, int64_t currentResult, int64_t target, bool canConcat) {
    if (idx == numbers.size()) {
        return currentResult == target;
    }

    if (currentResult > target) {
        return false;
    }

    if (recSolve(numbers, idx + 1, currentResult + numbers[idx], target, canConcat)) {
        return true;
    } 

    if (recSolve(numbers, idx + 1, currentResult * numbers[idx], target, canConcat)) {
        return true;
    }

    if (canConcat) {
        if (recSolve(numbers, idx + 1, concatenate(currentResult, numbers[idx]), target, canConcat)) {
            return true;
        }
    }  

    return false;

}

bool Equation::solvable(bool concat) {
    return concat ? recSolve(numbers, 1, numbers[0], result, true) : recSolve(numbers, 1, numbers[0], result, false);
}

int64_t Equation::getResult() const {
    return result;
};

void Equation::log() {
    cout << result << ": ";
    for (int64_t x : numbers) {
        cout << x << " ";
    }
    cout << endl;
}