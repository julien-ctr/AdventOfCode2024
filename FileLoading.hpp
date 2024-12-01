#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> loadFile(string fileName) {
    ifstream file(fileName);
    string line;
    vector<string> result;

    if (file.is_open()) {
        while (getline(file, line)) {
            result.push_back(line);
        }
    } else {
        cout << "Input file didn't open properly :(" << endl;
    }

    return result;
}