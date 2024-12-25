#include "InputProcessing.hpp"

using namespace std;

void loadData(const vector<string> &text, unordered_map<string,int> &values, unordered_map<string, vector<string>> &gates) {
    ParsingState ps = VALUES;
    for (const string &line : text) {
        switch (ps) {
            case VALUES: {
                if (line.empty()) {
                    ps = GATES;
                    break;
                }

                string wire = line.substr(0,3);
                int state = stoi(line.substr(5));
                values[wire] = state;

                break;
            }

            case GATES: {
                stringstream sstream(line);
                string part;
                vector<string> components;

                while (sstream >> part) {
                    components.push_back(part);
                }

                gates[components[4]] = {components[0], components[2], components[1]}; // Z => X, Y, OP
                break;
            }

            default:
                break;
        }
    }
}

void solve(unordered_map<string,int> &values, const unordered_map<string, vector<string>> &gates, const string &toSolve, int depth) {
    string leftOperand = gates.at(toSolve)[0];
    string rightOperand = gates.at(toSolve)[1];

    if (!values.count(leftOperand)) solve(values, gates, leftOperand, depth + 1);
    if (!values.count(rightOperand)) solve(values, gates, rightOperand, depth + 1);

    string operation = gates.at(toSolve)[2];

    if (operation == "AND") {
        values[toSolve] = values[leftOperand] && values[rightOperand];
    } else if (operation == "OR") {
        values[toSolve] = values[leftOperand] || values[rightOperand];
    } else if (operation == "XOR") {
        values[toSolve] = values[leftOperand] ^ values[rightOperand];
    } else {
        cerr << "Unknown operation: " << operation << endl;
    }

    // for (int i = 0; i < depth; ++i) cout << "  ";
    // cout << leftOperand << " " << operation << " " << rightOperand << " = " << toSolve << endl;
}

vector<string> fixErrors(unordered_map<string,int> &values, unordered_map<string, vector<string>> &gates) {
    /*
    Iterate through all zXX gates.
    Identify : 
        - The carry (xXX-1 AND yXX-1) OR (xXX-1 XOR yXX-1 AND carry - 1)
        - The result of the calculation without carry (xXX XOR yXX)

    We should have zXX = carry XOR result.

    If not, two scenarios :
        1. Everything but one operand is good
            => Find which one and switch it
        2. Else, zXX is not associated with the right gate
            => Find the expected gate (carry XOR result), then switch
    */

    int bitCount = 1;
    string bit = string("z") + (bitCount < 10 ? "0" : "") + to_string(bitCount); // Format zXX
    string xXX = string("x") + (bitCount < 10 ? "0" : "") + to_string(bitCount);
    string yXX = string("y") + (bitCount < 10 ? "0" : "") + to_string(bitCount);
    string carry;
    string partialResult;
    vector<string> switched;

    while (gates.count(bit)) {
        if (bitCount == 1) { // Initial carry
            for (const auto &[key, val] : gates) {
                if ((val[0] == "x00" || val[0] == "y00") && 
                    (val[1] == "x00" || val[1] == "y00") &&
                    (val[2] == "AND")) {
                        carry = key;
                        break;
                    };
            }
        } else { // Carries are a combination of two AND gates and an OR gate
            string temp;
            for (const auto &[key, val] : gates) {
                if ((val[0] == carry || val[1] == carry) && 
                    (val[2] == "AND")) {
                        temp = key;
                        break;
                    };
            }

            for (const auto &[key, val] : gates) {
                if ((val[0] == temp || val[1] == temp) && 
                    (val[2] == "OR")) {
                        carry = key;
                        break;
                    };
            }

        }

        for (const auto &[key, val] : gates) { // Partial result = xXX XOR yXX
            if ((val[0] == xXX || val[0] == yXX) && 
                (val[1] == xXX || val[1] == yXX) &&
                (val[2] == "XOR")) {
                    partialResult = key;
                    break;
                };
        }

        if (gates[bit][2] != "XOR" ||
            (gates[bit][0] != carry && gates[bit][0] != partialResult) ||
            (gates[bit][1] != carry && gates[bit][1] != partialResult)) { // If the line involving zXX is not the one expected, find out why

                if (gates[bit][2] == "XOR" &&
                    ((gates[bit][0] == carry ^ gates[bit][1] == partialResult) ||
                    (gates[bit][1] == carry ^ gates[bit][0] == partialResult))) { // The gate is the right one, one of the operand is not the right one
                        // Switch faulty operand and expected one
                        if (gates[bit][0] == carry && gates[bit][1] != partialResult) {
                            vector<string> t = gates[partialResult];
                            gates[partialResult] = gates[gates[bit][1]];
                            gates[gates[bit][1]] = t;
                            switched.push_back(partialResult);
                            switched.push_back(gates[bit][1]);
                        } 
                        else if (gates[bit][1] == carry && gates[bit][0] != partialResult) {
                            vector<string> t = gates[partialResult];
                            gates[partialResult] = gates[gates[bit][0]];
                            gates[gates[bit][0]] = t;
                            switched.push_back(partialResult);
                            switched.push_back(gates[bit][0]);
                        } 
                        else if (gates[bit][0] != carry && gates[bit][1] == partialResult) {
                            vector<string> t = gates[partialResult];
                            gates[carry] = gates[gates[bit][0]];
                            gates[gates[bit][0]] = t;
                            switched.push_back(carry);
                            switched.push_back(gates[bit][0]);
                        } 
                        else if (gates[bit][1] != carry && gates[bit][0] == partialResult) {
                            vector<string> t = gates[partialResult];
                            gates[carry] = gates[gates[bit][1]];
                            gates[gates[bit][1]] = t;
                            switched.push_back(carry);
                            switched.push_back(gates[bit][1]);
                        }
                } else {
                    for (const auto &[key, val] : gates) {
                        if ((val[0] == carry || val[0] == partialResult) && 
                            (val[1] == carry || val[1] == partialResult) &&
                            (val[2] == "XOR")) {
                                vector<string> t = gates[bit];
                                gates[bit] = val;
                                gates[key] = t;

                                switched.push_back(bit);
                                switched.push_back(key);
                                break;
                            }
                    }
                }
            }

        ++bitCount;
        bit = string("z") + (bitCount < 10 ? "0" : "") + to_string(bitCount); // Format zXX
        xXX = string("x") + (bitCount < 10 ? "0" : "") + to_string(bitCount);
        yXX = string("y") + (bitCount < 10 ? "0" : "") + to_string(bitCount);
    }


    sort(switched.begin(), switched.end());
    return switched;
}

pair<int64_t, string> countStars(const vector<string> &text) {
    pair<int64_t, string> stars = make_pair(0,"");

    unordered_map<string,int> values;
    unordered_map<string, vector<string>> gates;

    loadData(text, values, gates);
    
    int bitCount = 0;
    string bit = string("z") + (bitCount < 10 ? "0" : "") + to_string(bitCount); // Format zXX
    int64_t result = 0;
    while (gates.count(bit)) {
        solve(values,gates, bit);
        result += pow(2, bitCount) * values[bit];

        ++bitCount;
        bit = string("z") + (bitCount < 10 ? "0" : "") + to_string(bitCount); // Format zXX
    }

    vector<string> switches = fixErrors(values,gates);
    
    stars.first = result;
    stars.second = switches[0];
    for (unsigned int i = 1; i < switches.size(); ++i) stars.second += "," + switches[i];
    return stars;
}