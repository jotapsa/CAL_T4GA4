#include "editDistance.h"

int min3(int a, int b, int c) {
    int min = std::min(a, b);
    return std::min(min, c);
}

int editDistance::calculateDistance(std::string text, std::string pattern) {
    int i, j;

    std::vector<int> d(text.length());

    for (j = 0; j < text.size(); j++) {
        d[j] = j;
    }

    for( i = 0; i < pattern.size(); i++){
        int old = d[0]; // guard d[i-1, 0]
        d[0] = i; // init d[i,0]

        for(j = 1; j < text.size(); j++){

            int newValue;

            if (pattern[i] == text[j]){
                newValue = old;
            } else {
                newValue = 1 + min3(old, d[j], d[j-1]);
            }

            old = d[j];
            d[j] = newValue;
        }
    }

    return d[text.size()-1];
}
