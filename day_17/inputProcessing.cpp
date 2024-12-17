#include "InputProcessing.hpp"

using namespace std;

void loadData(const vector<string> &text, Program &prog) {
    unsigned int i;
    for (i = 0; i < 3; ++i) {
        string line = text[i];
        unsigned int colonPos = line.find(":");
        if (colonPos == string::npos) return;
        string data = line.substr(colonPos + 1);
        stringstream sstream(data);

        int64_t num;
        sstream >> num;
        if (i == 0) prog.A = num;
        if (i == 1) prog.B = num;
        if (i == 2) prog.C = num;
    }

    ++i;

    string line = text[i];
    unsigned int colonPos = line.find(":");
    if (colonPos == string::npos) return;
    string data = line.substr(colonPos + 1);
    stringstream sstream(data);

    int64_t fst, scd;
    while (sstream >> fst) {
        if (sstream.peek() == ',') sstream.ignore();
        sstream >> scd;
        prog.instructions.emplace_back(fst, scd);
        if (sstream.peek() == ',') sstream.ignore();
    }
}

pair<string, uint64_t> countStars(const vector<string> &text) {
    pair<string, uint64_t> stars = make_pair("",0);

    Program prog;
    
    loadData(text, prog);

    Program cpy = prog;
    prog.processAllInstructions();

    stars.first = to_string(prog.out[0]);
    for (unsigned int i = 1; i < prog.out.size(); ++i) {
        stars.first += "," + to_string(prog.out[i]);
    }
    stars.second = prog.findCopy();
    return stars;
}