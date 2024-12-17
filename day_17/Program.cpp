#include "Program.hpp"

int64_t Program::getCombo(int combo) {
    switch (combo) {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return A;
        case 5:
            return B;
        case 6:
            return C;
        case 7:
            break;
        default:
            break;
    }

    return -1;
}

int Program::instructionAt(int i) {
    return (i % 2 == 0 ? instructions[i/2].first : instructions[i/2].second);
}


void Program::processInstruction() {
    const auto &[opcode, combo] = instructions[idx++];
    
    // cout << "Processing opcode " << opcode << " with combo " << combo << endl;

    int64_t comboValue = getCombo(combo);

    switch (opcode) {
        case 0: // adv
            A = (A / pow(2, comboValue));
            break;

        case 1: // bxl
            B = B ^ combo;
            break;

        case 2: // bst
            B = comboValue % 8;
            break;

        case 3: // jnz
            if (A == 0) break;
            idx = combo;
            break;

        case 4: // bxt
            B = B ^ C;
            break;

        case 5: // out
            out.push_back(comboValue % 8);
            break;

        case 6: // bdv
            B = (A / pow(2, comboValue));
            break;

        case 7: // cdv
            C = (A / pow(2, comboValue));
            break;

        default:
            break;
    }
}

void Program::processAllInstructions() {
    while (idx < instructions.size()) {
        processInstruction();
    }
}

int64_t Program::findCopy() {
    int size = instructions.size() * 2;

    int64_t k = pow(8, size-1);
    int64_t delta = pow(8, size-1);
    int goodNumbers = 0;
    vector<int> attempts(size, 0);

    Program cpy = *this;

    while (goodNumbers < size) {
        cpy.out = {};
        cpy.A = k;
        cpy.B = 0;
        cpy.C = 0;
        cpy.idx = 0;
        cpy.processAllInstructions();        

        if (cpy.out[size - 1 - goodNumbers] == instructionAt(size - 1 - goodNumbers)) {
            ++goodNumbers;
            delta /= 8;
            if (goodNumbers == size) break;
            attempts[size - 1 - goodNumbers] = 0;
        } else {
            while (attempts[size - 1 - goodNumbers] == 8) { // Backtrack if the current delta didn't provide a result in 8 iterations
                attempts[size - 1 - goodNumbers] = 0;
                --goodNumbers;
                delta *= 8;
                k -= delta;
            }
            ++attempts[size - 1 - goodNumbers];
            k += delta;
        }
    }

    return k;
}