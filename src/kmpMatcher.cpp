#include "kmpMatcher.h"

int* kmpMatcher::computeLspTable(std::string pattern) {
    int *lsp = new int[pattern.length()];
    lsp[0] = 0;  // Base case
    for (int i = 1; i < pattern.length(); i++) {
        // Start by assuming we're extending the previous LSP
        int j = lsp[i - 1];
        while (j > 0 && pattern[i] != pattern[j])
            j = lsp[j - 1];
        if (pattern[i] == pattern[j])
            j++;
        lsp[i] = j;
    }
    return lsp;
}

bool kmpMatcher::matches(std::string text, std::string pattern) {
    kmpMatcher matcher;

    std::transform(text.begin(), text.end(), text.begin(), ::toupper);
    std::transform(pattern.begin(), pattern.end(), pattern.begin(), ::toupper);

    int* lsp = matcher.computeLspTable(pattern);

    int j = 0;  // Number of chars matched in pattern
    for (int i = 0; i < text.length(); i++) {
        while (j > 0 && text[i] != pattern[j]) {
            // Fall back in the pattern
            j = lsp[j - 1];  // Strictly decreasing
        }
        if (text[i] == pattern[j]) {
            // Next char matched, increment position
            j++;
            if (j == pattern.length())
                return true;
        }
    }

    return false;  // Not found
}

