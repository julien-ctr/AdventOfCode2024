#include "InputProcessing.hpp"

using namespace std;

void loadData(const vector<string> &text, unordered_map<int, vector<int>> &map, vector<vector<int>> &v) {
    unsigned int line_num = 0;

    while (!text[line_num].empty()) {
        int key, val;
        istringstream lineStream(text[line_num]);

        lineStream >> key;
        lineStream.ignore(1, '|');
        lineStream >> val;

        if (map.contains(key)) {
            map[key].push_back(val);
        } else {
            map[key] = {val};
        }
        line_num++;
    } 

    line_num++;

    while (line_num < text.size()) {
        vector<int> update;
        int num;
        istringstream lineStream(text[line_num]);
        while (lineStream >> num) {
            update.push_back(num);
            lineStream.ignore(1, ',');
        }

        v.push_back(update);

        line_num++;
    }
}

bool isValidUpdate(unordered_map<int, vector<int>> &rules, const vector<int> &update) {
    set<int> unseen(update.begin(), update.end());

    for (auto it = update.rbegin(); it != update.rend(); ++it) {

        int val = *it;
        vector<int> following = rules[val];

        for (int el : following) {
            if (unseen.contains(el)) return false;
        }
        unseen.erase(val);
    }

    return true;
}

void sortUpdate(unordered_map<int, vector<int>> &rules,vector<int> &update) {
    sort(update.begin(), update.end(), [&rules](int a, int b) {
        vector<int> rule = rules[a];
        return find(rule.begin(), rule.end(), b) == rule.end();
    });
}

pair<int, int> countStars(unordered_map<int, vector<int>> &rules, const vector<vector<int>> &updates) {
    pair<int, int> stars = make_pair(0,0);
    for (auto update : updates) {
        if (isValidUpdate(rules, update)) {
            stars.first += update[update.size()/2];
        } else {
            sortUpdate(rules, update);
            stars.second += update[update.size()/2];
        }
    }

    return stars;
}