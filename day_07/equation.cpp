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

bool endsWith(int64_t x, int64_t y) {
    if (y == 0) return x == 0;

    int numDigits = log10(y) + 1;

    int64_t divisor = pow(10, numDigits);

    return x % divisor == y;
}

int64_t cut(int64_t x, int64_t y) {
    int numDigits = log10(y) + 1;
    return x / (pow(10, numDigits));
}

bool recSolveBack(vector<int64_t> &numbers, unsigned int idx, int64_t currentResult, int64_t target, bool canConcat) {
    if (idx == 0) {
        return currentResult == numbers[0];
    }

    if (currentResult < target) {
        return false;
    }   

    if (currentResult % numbers[idx] == 0) {
        if (recSolveBack(numbers, idx - 1, currentResult / numbers[idx], target, canConcat)) {
            return true;
        }
    }

    if (canConcat && endsWith(currentResult, numbers[idx])) {
        if (recSolveBack(numbers, idx - 1, cut(currentResult, numbers[idx]), target, canConcat)) {
            return true;
        }
    }  

    if (recSolveBack(numbers, idx - 1, currentResult - numbers[idx], target, canConcat)) {
        return true;
    } 

    return false;

}

bool Equation::solvable(bool concat) {
    // return concat ? recSolve(numbers, 1, numbers[0], result, true) : recSolve(numbers, 1, numbers[0], result, false);
    return concat ? recSolveBack(numbers, numbers.size()-1, result, 0, true) : recSolveBack(numbers, numbers.size()-1, result, 0, false);
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