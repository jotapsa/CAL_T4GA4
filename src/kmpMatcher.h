#ifndef CAL_T4GA4_KMPMATCHER_H
#define CAL_T4GA4_KMPMATCHER_H

#include <iostream>
#include <vector>

class kmpMatcher {

    public:

    int* computeLspTable(std::string pattern);

    static bool matches(std::string text, std::string pattern);

};

#endif
