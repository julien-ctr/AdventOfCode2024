#include "InputProcessing.hpp"

using namespace std;

bool isValidXMAS(const vector<string> &text, string word, unsigned int line, unsigned int col, int dx, int dy) {
    int current_line = line;
    int current_col = col;
    int num_col = text[0].size();
    int num_lines = text.size();

    for (const char c : word) {
        // Check the boundaries
        if (current_col < 0 || current_line < 0 || current_col > num_col - 1 || current_line > num_lines - 1 ) {
            return false;
        }

        // Check the character
        if (text[current_line][current_col] != c) {
            return false;
        }

        // Move the cursor
        current_line += dy;
        current_col += dx;
    }
    return true;
}

bool isValidCrossMAS(const vector<string> &text, int line, int col) {
    int num_col = text[0].size();
    int num_lines = text.size();

    // Check the boundaries
    if (col - 1 < 0 || line - 1 < 0 || col + 1 > num_col - 1 || line + 1 > num_lines - 1 ) {
        return false;
    }

    set<char> s1 = {text[line-1][col-1], text[line+1][col+1]};
    set<char> s2 = {text[line-1][col+1], text[line+1][col-1]};

    return s1.contains('M') && s1.contains('S') && s2.contains('M') && s2.contains('S');
}

pair<int, int> countXMAS(const vector<string> &text) {
    vector<pair<int, int>> directions = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
    pair<int, int> result = make_pair(0, 0);
    unsigned int i = 0, j = 0, count = 0;

    for (const string &line : text) {
        for (const char c : line){
            if (c == 'X') {
                for (const pair<int,int> &d : directions) {
                    if (isValidXMAS(text, "XMAS", i, j, d.first, d.second)) {
                        result.first++;
                    };
                }
            } else if (c == 'A') {
                if (isValidCrossMAS(text, i, j)) {
                    result.second++;
                };
            }
            j++;
        }
        i++;
        j = 0;
    }

    return result;
}
