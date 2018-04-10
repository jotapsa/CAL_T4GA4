#include <iostream>
#include <random>
#include "Cli.h"
#include "Parser.h"
#include "RandomEngine.h"

void loadBuildings(GarbageManagement &management){
    if(!loadContainers(management)){
        std::cout << "Failed to read containers!" << std::endl;
    }

    if(!loadStations(management)){
        std::cout << "Failed to read stations!" << std::endl;
    }

    if(!loadGarages(management)){
        std::cout << "Failed to read garages!" << std::endl;
    }
}

void saveBuildings(GarbageManagement &management){
    saveContainers(management);
    saveStations(management);
    saveGarages(management);
}

int main (int argc, char* argv[]) {
    initRandomEngine();
    GarbageManagement management = GarbageManagement();

    if(askMap(management)){
        management.initGraphViewer();

        std::cout << std::endl << "Reading map..." << std::endl;
        if(!loadPlaces(management)){
            std::cout << "Failed to read places!" << std::endl;
            return 1;
        }

        if(!loadVehicles(management)){
            std::cout << "Failed to read vehicles!" << std::endl;
        }

        loadBuildings(management);

        if(!loadEdgesInfo(management)){
            std::cout << "Failed to read edgesInfo!" << std::endl;
            return 1;
        };

        if(!loadEdges(management)){
            std::cout << "Failed to read edges!" << std::endl;
            return 1;
        }
    }
    else{
        management.initGraphViewer();
    }

    mainMenu(management);

    std::cout << std::endl << "Save Map ?" << std::endl;
    if(readConfirmation()){
        std::cout << "Saving map..." << std::endl;

        if(!saveMap(management)){
            return 1;
        }

        savePlaces(management);
        saveVehicles(management);
        saveBuildings(management);
        saveEdges(management);
        saveEdgesInfo(management);
    }

    management.closeWindow();

    return 0;
}
