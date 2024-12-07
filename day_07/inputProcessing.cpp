#include "InputProcessing.hpp"

using namespace std;

void loadData(const vector<string> &text, vector<Equation> &eqList) {
    for (const string line : text) {
        istringstream lineStream(line);
        int64_t res;
        lineStream >> res;
        Equation eq(res);
        lineStream.ignore(1, ':');

        int64_t number;
        while (lineStream >> number) {
            eq.addNumber(number);
        }

        eqList.push_back(eq);
    }
}

pair<int64_t, int64_t> countStars(const vector<string> &text) {
    pair<int64_t, int64_t> stars = make_pair(0,0);

    vector<Equation> eqList;

    loadData(text, eqList);

    for (Equation eq : eqList) {
        if (eq.solvable()) {
            stars.first += eq.getResult();
            stars.second += eq.getResult();
        }
        else if (eq.solvable(true)) {
            stars.second += eq.getResult();
           
        };
    }

    return stars;
}