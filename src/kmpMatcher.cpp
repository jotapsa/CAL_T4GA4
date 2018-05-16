#include "kmpMatcher.h"

std::vector<int> kmpMatcher::computePrefixFunction(std::string p) {

    std::vector<int> pi(p.size());
    int k = 0;

    for (int q = 1; q < p.size(); q++) {
        char target = p[q];

        while (k > 0 && p[k] != target) {
            k = pi[k - 1];
        }

        if (p[k + 1] == target) {
            k++;
        }

        pi[q] = k;
    }

    return pi;
}

bool kmpMatcher::matches(std::string t, std::string p) {
    kmpMatcher matcher;

    //Convert both strings to Upper Case
    std::transform(p.begin(), p.end(), p.begin(), ::toupper);
    std::transform(t.begin(), t.end(), t.begin(), ::toupper);

    int q = 0; // number of characters matched

    for (int i = 1; i <= t.size(); i++) {

        while (q > 0 && p[q + 1] != t[i]) {
            q = 0;
            q = matcher.computePrefixFunction(p)[q];
        }

        if (p[q + 1] == t[i])
            q = q + 1;

        if (q == p.size()) {
            return true;

            q = matcher.computePrefixFunction(p)[q];
        }
    }

    return false;
}

