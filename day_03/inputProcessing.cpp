#include "InputProcessing.hpp"

using namespace std;

vector<pair<pair<int, int>, bool>> processInput(vector<string> &fileContent) {
    static const regex regex(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))", regex_constants::optimize);
    vector<pair<pair<int, int>, bool>> result;
    bool counting = true;

    for (string line : fileContent) {
        auto begin = std::sregex_iterator(line.begin(), line.end(), regex);
        auto end = std::sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            smatch match = *it;
            if (match[0] == "do()") {
                counting = true;
            } else if  (match[0] == "don't()") {
                counting = false;
            } else {
                result.push_back(make_pair(
                    make_pair(stoi(match[1].str()), stoi(match[2].str())),
                    counting
                ));
            }
        }
    }
    return result;
}

pair<int, int> addMultiplications(vector<pair<pair<int, int>, bool>> &values) {
    pair<int, int> result = make_pair(0,0);
    for (const auto &p : values) {
        result.first += p.first.first * p.first.second;

        if (p.second) {
            result.second += p.first.first * p.first.second;
        }
    }
    return result;
}

