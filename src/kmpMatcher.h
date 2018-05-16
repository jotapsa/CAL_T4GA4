#ifndef CAL_T4GA4_KMPMATCHER_H
#define CAL_T4GA4_KMPMATCHER_H

#include <iostream>
#include <vector>

class kmpMatcher {

    public:

    std::vector<int> computePrefixFunction(std::string p);

    static bool matches(std::string t, std::string p);

};

#endif //CAL_T4GA4_KMPMATCHER_H
