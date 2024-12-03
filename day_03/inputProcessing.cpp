#include "InputProcessing.hpp"

using namespace std;

vector<pair<pair<int, int>, bool>> processInputRegex(vector<string> &fileContent) {
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

vector<pair<pair<int, int>, bool>> processInputStateMachine(vector<string> &fileContent) {
    vector<pair<pair<int, int>, bool>> result;
    MulState mulState = MUL_START;
    DoState doState = DO_START;
    DontState dontState = DONT_START;
    bool counting = true;

    for (string line : fileContent) {
        int x = 0, y = 0;
        string numBuffer;
        for (char c : line) {
            switch (mulState) {
                case MUL_START:
                    if (c == 'm') mulState = MUL_M;
                    break;
                case MUL_M:
                    mulState = (c == 'u') ? MUL_MU : MUL_START;
                    break;
                case MUL_MU:
                    mulState = (c == 'l') ? MUL_MUL : MUL_START;
                    break;
                case MUL_MUL:
                    mulState = (c == '(') ? MUL_OPEN_PARENTHESIS : MUL_START;
                    break;
                case MUL_OPEN_PARENTHESIS:
                    if (isdigit(c)) {
                        numBuffer += c;
                        mulState = MUL_NUMBER_1;
                    } else {
                        mulState = MUL_START;
                    }
                    break;
                case MUL_NUMBER_1:
                    if (isdigit(c)) {
                        numBuffer += c;
                    } else if (c == ',') {
                        x = stoi(numBuffer);
                        numBuffer.clear();
                        mulState = MUL_COMMA;
                    } else {
                        numBuffer.clear();
                        mulState = MUL_START;
                    }
                    break;
                case MUL_COMMA:
                    if (isdigit(c)) {
                        numBuffer += c;
                        mulState = MUL_NUMBER_2;
                    } else {
                        mulState = MUL_START;
                    }
                    break;
                case MUL_NUMBER_2:
                    if (isdigit(c)) {
                        numBuffer += c;
                    } else if (c == ')') {
                        y = stoi(numBuffer);
                        numBuffer.clear();
                        mulState = MUL_START;
                        result.push_back(make_pair(make_pair(x,y), counting));
                    } else {
                        numBuffer.clear();
                        mulState = MUL_START;
                    }
                    break;
                default:
                    mulState = MUL_START;
                    break;
            }
            switch (doState) {
                case DO_START:
                    if (c == 'd') doState = DO_D;
                    break;
                case DO_D:
                    doState = (c == 'o') ? DO_DO : DO_START;
                    break;
                case DO_DO:
                    doState = (c == '(') ? DO_OPEN_PARENTHESIS : DO_START;
                    break;
                case DO_OPEN_PARENTHESIS:
                    if (c == ')') counting = true;
                    doState = DO_START;
                    break;
                default:
                    doState = DO_START;
                    break;
            }
            switch (dontState) {
                case DONT_START:
                    if (c == 'd') dontState = DONT_D;
                    break;
                case DONT_D:
                    dontState = (c == 'o') ? DONT_DO : DONT_START;
                    break;
                case DONT_DO:
                    dontState = (c == 'n') ? DONT_DON : DONT_START;
                    break;
                case DONT_DON:
                    dontState = (c == '\'') ? DONT_DON_ : DONT_START;
                    break;
                case DONT_DON_:
                    dontState = (c == 't') ? DONT_DON_T : DONT_START;
                    break;
                case DONT_DON_T:
                    dontState = (c == '(') ? DONT_OPEN_PARENTHESIS : DONT_START;
                    break;
                case DONT_OPEN_PARENTHESIS:
                    if (c == ')') counting = false;
                    dontState = DONT_START;
                    break;
                default:
                    dontState = DONT_START;
                    break;
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

