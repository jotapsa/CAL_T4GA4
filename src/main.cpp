#include <iostream>
#include "Cli.h"
#include "GarbageManagement.h"
#include "Parser.h"

int main (int argc, char* argv[]) {
    GarbageManagement management = GarbageManagement();

    std::cout << "Read Stored Map ?" << std::endl;
    if(readConfirmation()){
        std::cout << "Reading map..." << std::endl;
        if(!loadPlaces(management)){
            std::cout << "Failed to read places!" << std::endl;
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

        if(!loadVehicles(management)){
            std::cout << "Failed to read vehicles!" << std::endl;
            return 1;
        };
    }

    mainMenu(management);

    std::cout << "Save Map ?" << std::endl;
    if(readConfirmation()){
        std::cout << "Saving map..." << std::endl;
        saveNodes(management);
        saveEdges(management);
        saveEdgesInfo(management);
    }

    return 0;
}
