#include "InputProcessing.hpp"

using namespace std;

void loadData(const vector<string> &text, Onsen &myOnsen) {
    stringstream availablePatterns(text[0]);
    string towel = "";
    char token;
   
    while (availablePatterns >> token) {
        if (token != ',') {
            towel += token;
        } else {
            myOnsen.available.insert(towel);
            if (towel.size() > myOnsen.maxSize) myOnsen.maxSize = towel.size();
            
            towel = "";
        }
    }

    myOnsen.available.insert(towel);
    if (towel.size() > myOnsen.maxSize) myOnsen.maxSize = towel.size();

    for (unsigned int lineNum = 2; lineNum < text.size(); ++lineNum) {
        myOnsen.toMake.push_back(text[lineNum]);
    }
}

pair<int64_t, int64_t> countStars(const vector<string> &text) {
    pair<int64_t, int64_t> stars = make_pair(0, 0);

    Onsen myOnsen;

    loadData(text, myOnsen);
    stars = myOnsen.countPossible();
    
    return stars;
}