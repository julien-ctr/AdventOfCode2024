#include "InputProcessing.hpp"

using namespace std;

void parseData(const vector<string> &text, vector<int> &memory) {
    for (const string &line : text) {
        for (const char c : line) {
            memory.push_back((int) c - '0');
        }
    }
}

uint64_t orderMemory(vector<int> &memory) {
    /*
    That's a mess but it works
    */

    unsigned int i = 0;
    int j = memory.size() - 1;
    int capacity = 0, remaining = 0, iFinal = 0;
    uint64_t count = 0;
    remaining = memory[j];

    while (i < j) {
        if (i % 2 == 0) { // Memory block
            int blockId = i/2;
            capacity = memory[i];
            for (int k = 0 ; k < capacity; ++k) { // Add values one by one
                count += blockId * iFinal++;
            }
            ++i;

        } else { // Empty space
            capacity = memory[i];
            int blockId = j/2;
            while (capacity > 0) { // Fill the empty space
               
                while (remaining == 0) { // Move the cursor until finding a non-empty block
                    j -= 2;
                    remaining = memory[j]; 
                    blockId = j/2;
                    if (j < i) break; // Early exit, the initial while condition isn't satisfied anymore
                }

                if (remaining > 0 && j > i) { // Check if a valid block was found
                    count += blockId * iFinal++;
                    --remaining;
                }
                --capacity;
            }
            ++i;
        }
    }

    if (j >= i){ // If we got out of the loop while some values weren't processed, we process them
        while (remaining > 0) {
            count += (j/2) * iFinal++;
            --remaining;
        }
    }
    return count;
}

uint64_t orderMemoryBis(vector<int> &memory) {
    uint64_t count = 0;
    uint64_t iFinal = 0;
    vector<bool> movedBlocks(memory.size()/2, false);

    for (unsigned int i = 0; i < memory.size(); ++i) { // Loop through the blocks from the left
        if (i%2==0) { // Even => Block, just add to the count and move on
            if (!movedBlocks[i/2]) {
                for (unsigned int k = 0; k < memory[i]; ++k) {
                    count += (i/2) * iFinal++;
                }
            } else {
                iFinal += memory[i];
            }
        } else { // Odd => empty space
            unsigned int capacity = memory[i];
            while (capacity > 0) {
                unsigned int j;
                for (j = memory.size()-1; j > i ; j -= 2) { // Loop backwards until finding a fitting block
                    unsigned int analyzedBlockId = j/2;
                    if (!movedBlocks[analyzedBlockId] && memory[j] <= capacity) {
                        unsigned int n = memory[j]; // Size of the analyzed block
                        count += analyzedBlockId * (n * (iFinal + iFinal + n - 1))/2; // Formula to sum consecutive integers
                        movedBlocks[analyzedBlockId] = true;
                        iFinal += n;
                        capacity -= n;
                        break; // No need to look for another block
                    }
                }
                if (j <= i) {  // None of the remaining blocks fit in the current space
                    iFinal += capacity;
                    break;
                }
            }
        }
    }
    return count;
}

pair<uint64_t, uint64_t> countStars(const vector<string> &text) {
    pair<uint64_t, uint64_t> stars = make_pair(0,0);

    vector<int> memory;
    parseData(text, memory);
    
    stars.first = orderMemory(memory);
    stars.second = orderMemoryBis(memory);

    return stars;
}