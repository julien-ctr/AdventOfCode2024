#include "InputProcessing.hpp"

using namespace std;

pair<int64_t, int64_t> countStars(const vector<string> &text) {
    pair<int64_t, int64_t> stars = make_pair(0,0);

    for (const string &line : text) {
        Password password(line);
        int64_t sizeSeq = typePassword(password, 2);
        stars.first += sizeSeq * password.getNumericPart();

        sizeSeq = typePassword(password, 25);
        stars.second += sizeSeq * password.getNumericPart();

    }

    return stars;
}