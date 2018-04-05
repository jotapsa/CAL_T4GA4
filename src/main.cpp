#include <iostream>
#include "Cli.h"
#include "GarbageManagement.h"
#include "Parser.h"

int main (int argc, char* argv[]) {
    GarbageManagement management = GarbageManagement();

    std::cout << "Read Stored Map ?" << std::endl;
    if(readConfirmation()){
        //read files
        if(!loadNodes(management)){
            std::cout << "Failed to read nodes!" << std::endl;
            return 1;
        }

        if(!loadBuildings(management)){
            std::cout << "Failed to read buildings!" << std::endl;
            return 1;
        }

        if(!loadEdges(management)){
            std::cout << "Failed to read edges!" << std::endl;
            return 1;
        }

        if(!loadEdgesInfo(management)){
            std::cout << "Failed to read edges info!" << std::endl;
            return 1;
        };
    }

    mainMenu(management);

    std::cout << "Save Map ?" << std::endl;
    if(readConfirmation()){
        saveNodes(management);
        saveEdges(management);
        saveEdgesInfo(management);
    }

    return 0;
}
