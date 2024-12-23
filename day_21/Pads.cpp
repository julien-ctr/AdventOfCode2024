#include "Pads.hpp"

vector<pair<char,char>> getTransitions(const string &s) {
    vector<pair<char,char>> result; 
    for (unsigned int i = 0; i < s.size() - 1; ++i) {
        result.push_back({s[i], s[i+1]});
    }
    return result;
}

string NumPad::getSequence(const char from, const char to) {
    if (positions.find(from) == positions.end() || positions.find(to) == positions.end()) {
        return {};
    }

    pair<int, int> start = positions[from];
    pair<int, int> target = positions[to];

    int dx = target.second - start.second;
    int dy = target.first - start.first;

    string moves = "";

    if (dx < 0) {
        if (start.first == 3 && target.second == 0) {
            moves += string(abs(dy), (dy > 0 ? 'v' : '^'));
            moves += string(-dx, '<');
        } else {
            moves += string(-dx, '<');
            moves += string(abs(dy), (dy > 0 ? 'v' : '^'));
        }
    } else if (dy > 0) {
        if (start.second == 0 && target.first == 3) {
            moves += string(dx, '>');
            moves += string(dy, 'v');
        } else {
            moves += string(dy, 'v');
            moves += string(dx, '>');
        }
    } else {
        moves += string(-dy, '^');
        moves += string(dx, '>');
    }

    return moves + "A";
}

string DirPad::getSequence(const char from, const char to) {
    if (positions.find(from) == positions.end() || positions.find(to) == positions.end()) {
        return {};
    }

    pair<int, int> start = positions[from];
    pair<int, int> target = positions[to];

    int dx = target.second - start.second;
    int dy = target.first - start.first;

    string moves = "";

    if (dx < 0) {
        if (start.first == 0 && target.second == 0) {
            moves += string(abs(dy), (dy > 0 ? 'v' : '^'));
            moves += string(-dx, '<');
        } else {
            moves += string(-dx, '<');
            moves += string(abs(dy), (dy > 0 ? 'v' : '^'));
        }
    } else if (dy < 0) {
        if (start.second == 0 && target.first == 0) { // Can't move up, go right first
            moves += string(dx, '>');
            moves += string(-dy, '^');
        } else {
            moves += string(-dy, '^');
            moves += string(dx, '>');
        }
        
    } else {
        moves += string(dy, 'v');
        moves += string(dx, '>');
    }

    return moves + "A";
}

int64_t typePassword(const Password &p, int dirRobots) {
    NumPad numpad;
    DirPad dirpad;
    
    map<pair<char,char>,vector<pair<char,char>>> transitions;
    map<pair<char,char>,int64_t> histogram;

    for (const pair<char,char> transition : getTransitions(p.code)) {
        histogram[transition]++;
    }

    for (unsigned int robotNum = 0; robotNum <= dirRobots; ++robotNum) {
        map<pair<char,char>,int64_t> newHistogram;

        // Iterate over the histogram
        for (const auto &[key, val] : histogram) {
            if (transitions.find(key) == transitions.end()) { // First time seeing the transition
                string seq;
                if (robotNum == 0) seq = numpad.getSequence(key.first, key.second);
                else seq = dirpad.getSequence(key.first, key.second);
                seq = "A" + seq;

                for (const pair<char,char> t : getTransitions(seq)) {
                    transitions[key].push_back(t);
                }
            }

            for (const pair<char,char> t : transitions[key]) {
                newHistogram[t] += val;
            }
        }

        histogram = newHistogram;
    }

    // Compute sum of all values in histogram
    int64_t sum = 0;
    for (const auto &[key, val] : histogram) {
        sum += val;
    }

    return sum;
}
