#include <iostream>
#include "Cli.h"
#include "GarbageManagement.h"
#include "Parser.h"

int main (int argc, char* argv[]) {
    GarbageManagement management = GarbageManagement();

    std::cout << "Read stored map ?" << std::endl;
    if(readConfirmation()){
        //read files
        loadNodes(management);
        loadEdges(management);
        loadEdgesInfo(management);
    }

    //menu

    std::cout << "Save map ?" << std::endl;
    if(readConfirmation()){
        saveNodes(management);
        saveEdges(management);
        saveEdgesInfo(management);
    }

    return 0;
}
