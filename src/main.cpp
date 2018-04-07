#include <iostream>
#include <random>
#include "Cli.h"
#include "Parser.h"
#include "RandomEngine.h"

bool loadBuildings(GarbageManagement &management){
    if(!loadContainers(management)){
        std::cout << "Failed to read containers!" << std::endl;
        return false;
    }

    if(!loadStations(management)){
        std::cout << "Failed to read stations!" << std::endl;
        return false;
    }

    if(!loadGarages(management)){
        std::cout << "Failed to read garages!" << std::endl;
        return false;
    }

    return true;
}

void saveBuildings(GarbageManagement &management){
    saveContainers(management);
    saveStations(management);
    saveGarages(management);
}

int main (int argc, char* argv[]) {
    //initializeRandomEngine();
    GarbageManagement management = GarbageManagement();

    std::cout << "Read Stored Map ?" << std::endl;
    if(readConfirmation()){
        std::cout << "Reading map..." << std::endl;
        if(!loadPlaces(management)){
            std::cout << "Failed to read places!" << std::endl;
            return 1;
        }

        if(!loadBuildings(management)){
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
        std::cout << "Saving map..." << std::endl;
        savePlaces(management);
        saveBuildings(management);
        saveEdges(management);
        saveEdgesInfo(management);
        std::cout << "Saved!" << std::endl;
    }

    return 0;
}
