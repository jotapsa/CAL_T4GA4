#include <iostream>
#include <iomanip>
#include "GarbageManagement.h"
#include "Cli.h"

void garbageServiceMenu(GarbageManagement &management);

bool readConfirmation() {
    std::string temp;
    do{
        std::cout << "[Y/n]: ";
        getline(std::cin, temp);
    }while(temp != "Y" &&
           temp !="y" &&
           temp != "N" &&
           temp != "n");

    if(temp == "Y" || temp == "y"){
        return true;
    }
    else{
        return false;
    }
}

double parseDouble (std::string str) {

    //TODO (Use João Sá library to validate user input)
    double number;

    do {
        std::cout << str;
        std::cin >> number;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n'); //clean input buffer
            continue;
        }
        else {
            std::cin.clear();
            std::cin.ignore(1000,'\n'); //clean input buffer
            return number;
        }
    }while(true);
}

unsigned int nextUnsignedInt(std::string str, unsigned int ceilling){
    unsigned int number;
    do{
        std::cout << str;
        std::cin >> number;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n'); //clean input buffer
            continue;
        }
        else if(number > ceilling){
            continue;
        }
        std::cin.clear();
        std::cin.ignore(1000,'\n'); //clean input buffer
        return number;
    }while(true);
}

unsigned int getUnsignedInt(std::string str) {
    unsigned int number;
    do{
        std::cout << str;
        std::cin >> number;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n'); //clean input buffer
            continue;
        }
        std::cin.clear();
        std::cin.ignore(1000,'\n'); //clean input buffer
        return number;
    }while(true);
}

unsigned int settingsMenuDialog() {

    std::cout << "Settings Menu" << std::endl;
    std::cout << "1 - Set Garage" << std::endl;
    std::cout << "2 - Set Container" << std::endl;
    std::cout << "3 - Set Station" << std::endl;
    std::cout << "4 - Fill Container" << std::endl;
    std::cout << "5 - Clear Container" << std::endl;
    std::cout << "6 - Find Container" << std::endl;
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Option: ", 6);
}

void settingsMenu(GarbageManagement &management) {
    switch (settingsMenuDialog()) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 0:
            mainMenu(management);
        break;
        default:
            break;
    }
}

unsigned int vehicleMenuDialog(){
    std::cout << "Vehicle Menu" << std::endl;
    std::cout << "1 - Create Vehicle" << std::endl;
    std::cout << "2 - Remove Vehicle" << std::endl;
    std::cout << "3 - Add Vehicle type" << std::endl;
    std::cout << "4 - Remove Vehicle type" << std::endl;
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Option: ", 4);
}

void vehicleMenu(GarbageManagement &management){
    switch(vehicleMenuDialog()){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 0:
            mainMenu(management);
        break;
        default:
            break;
    }
}

unsigned int edgeMenuDialog(){
    std::cout << "Edge Menu" << std::endl;
    std::cout << "1 - Create Edge" << std::endl;
    std::cout << "2 - Remove Edge" << std::endl;
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Option: ", 2);
}

void edgeMenu(GarbageManagement &management) {

    switch(edgeMenuDialog()) {
        case 1:
            break;
        case 2:
            break;
        case 0:
            mainMenu(management);
        break;
        default:
            break;
    }
}

std::pair<double, double> askForLocation() {

    double lat = parseDouble("\tInsert Latitude: ");
    double lon = parseDouble("\tInsert Longitude: ");

    return std::make_pair(lat, lon);
};

void createSimpleLocation(GarbageManagement &management) {
//TODO (Check if added garage is inside map window)

    //management.addPlace(new Place(Place::getUnusedId(), askForLocation()));
    //management.rearrange();
}

void createGarage(GarbageManagement &management) {
//TODO (Check if added garage is inside map window)

    std::cout << "Insert location for garage:\n";

    std::pair<double,double> garageCoordinates = askForLocation();

    //management.addGarage(new Garage(Place::getUnusedId(), garageCoordinates));
    //management.rearrange();
}

//Container and Station both use the same parameters
void createContainerOrStation(GarbageManagement &management, std::string buildingType) {

    std::cout << "Insert location for " << buildingType << ": \n";

    std::pair<double,double> containerCoordinates = askForLocation();

    unsigned int garbageTypeIndex = selectGarbageTypeMenu();

    if(garbageTypeIndex == 0){
        return;
    }

    double capacity = parseDouble("Insert " + buildingType + " capacity: ");

    //TODO: switch w/ default case
    if(buildingType.compare("container") == 0){
        //management.addContainer(new Container(Place::getUnusedID(), containerCoordinates, getGarbageTypeForOption(garbageTypeIndex), capacity));
    }
    else{
        //management.addStation(new Station(Place::getUnusedID(), containerCoordinates, getGarbageTypeForOption(garbageTypeIndex), capacity));
    }
    //management.rearrange();
}

unsigned int selectGarbageTypeMenu() {

    std::cout << "Select garbage type:" << std::endl;
    std::cout << "\t1 - Glass" << std::endl;
    std::cout << "\t2 - Plastic" << std::endl;
    std::cout << "\t3 - Paper" << std::endl;
    std::cout << "\t4 - Generic" << std::endl;
    std::cout << "\t0 - Exit" << std::endl;

    return nextUnsignedInt("Option: ", 4);
}

unsigned int editNodeMenu() {
    std::cout << "Select option:" << std::endl;
    std::cout << "\t1 - Edit location" << std::endl;
    std::cout << "\t2 - Edit" << std::endl;
    return 1;
}

void editNode(unsigned long nodeID) {
//TODO(Edits node based on user option and input)
    std::cout << "Edit info\n";
}

void listGarages(GarbageManagement &management) {

    unsigned int selectedID;

    std::cout << std::setfill('-') << std::setw(MAX_ULONG_WITH + MAX_DOUBLE_WITH) << " Garages ";
    std::cout << std::setfill('-') << std::setw(MAX_DOUBLE_WITH + MAX_DOUBLE_WITH) << "-"<< endl;

    do {
        std::cout << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << "Node ID";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Longitude";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Latitude";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH)  << "#Vehicles" << std::endl;

        for(auto garage : management.getGarages()) {

            std::cout << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << garage->getPlace()->getID();
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << garage->getPlace()->getCoordinates().first;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << garage->getPlace()->getCoordinates().second;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH)  << garage->getNumberOfVehicles() << std::endl;
        }

        selectedID = getUnsignedInt("Insert node ID to edit garage, 0 to leave: ");

        if(management.getPlace(selectedID) != nullptr){
            editNode(selectedID);
        }

    }while(selectedID != 0);
}

void listContainers(GarbageManagement &management) {

    unsigned int selectedID;

    std::cout << std::setfill('-') << std::setw(MAX_ULONG_WITH + MAX_DOUBLE_WITH + MAX_DOUBLE_WITH) << " Containers ";
    std::cout << std::setfill('-') << std::setw(MAX_DOUBLE_WITH + MAX_DOUBLE_WITH) << "-"<< endl;

    do {
        std::cout << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << "Node ID";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Longitude";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Latitude";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Type";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Capacity" << std::endl;

        for(auto container : management.getContainers()) {

            std::cout << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << container->getPlace()->getID();
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << container->getPlace()->getCoordinates().first;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << container->getPlace()->getCoordinates().second;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH)  << getGarbageType(container->getType());
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << container->getCapacity() << std::endl;
        }

        selectedID = getUnsignedInt("Insert node ID to edit container, 0 to leave: ");

        if(management.getPlace(selectedID) != nullptr){
            editNode(selectedID);
        }

    }while(selectedID != 0);
}

void listStations(GarbageManagement &management) {

    unsigned int selectedID;

    std::cout << std::setfill('-') << std::setw(MAX_ULONG_WITH + MAX_DOUBLE_WITH + MAX_DOUBLE_WITH) << " Stations ";
    std::cout << std::setfill('-') << std::setw(MAX_DOUBLE_WITH + MAX_DOUBLE_WITH) << "-"<< endl;

    do {
        std::cout << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << "Node ID";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Longitude";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Latitude";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Type";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Capacity" << std::endl;

        for(auto station : management.getStations()) {

            std::cout << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << station->getPlace()->getID();
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << station->getPlace()->getCoordinates().first;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << station->getPlace()->getCoordinates().second;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << getGarbageType(station->getGarbageType());
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << station->getCapacity() << std::endl;
        }

        selectedID = getUnsignedInt("Insert node ID to edit station, 0 to leave: ");

        if(management.getPlace(selectedID) != nullptr){
            editNode(selectedID);
        }

    }while(selectedID != 0);
}

void removeBuilding(GarbageManagement &management, std::string type) {

    unsigned long nodeId = getUnsignedInt("Insert " + type + " ID to remove: ");

    //TODO(Test this function)

    switch(type.at(0)) {
        case 's':
            if(management.getStation(nodeId) == nullptr) {
                std::cout << "There is no " + type + " with " << nodeId << " as ID!\n";
            }
            else {
                management.removeStation(nodeId);
                std::cout << type << " removed with success " << nodeId << " as ID!\n";
            }
            break;
        case 'g':
            if(management.getGarage(nodeId) == nullptr) {
                std::cout << "There is no " + type + " with " << nodeId << " as ID!\n";
            }
            else {
                management.removeGarage(nodeId);
                std::cout << type << " removed with success " << nodeId << " as ID!\n";
            }
            break;
        case 'c':
            if(management.getContainer(nodeId) == nullptr) {
                std::cout << "There is no " + type + " with " << nodeId << " as ID!\n";
            }
            else {
                management.removeContainer(nodeId);
                std::cout << type << " removed with success " << nodeId << " as ID!\n";
            }
            break;
        case 'p':
            if(management.getPlace(nodeId) == nullptr) {
                std::cout << "There is no " + type + " with " << nodeId << " as ID!\n";
            }
            else {
                management.removeEmptyPlace(nodeId);
                std::cout << type << " removed with success " << nodeId << " as ID!\n";
            }
            break;
        default:
            break;
    }
}

unsigned int nodeMenuDialog() {
    std::cout << "\nNode Menu" << std::endl;
    std::cout << "1  - Create location" << std::endl;
    std::cout << "2  - Create garage" << std::endl;
    std::cout << "3  - Create container" << std::endl;
    std::cout << "4  - Create station" << std::endl;
    std::cout << "5  - List garages" << std::endl;
    std::cout << "6  - List containers" << std::endl;
    std::cout << "7  - List stations" << std::endl;
    std::cout << "8  - Remove garage" << std::endl;
    std::cout << "9  - Remove container" << std::endl;
    std::cout << "10 - Remove station" << std::endl;
    std::cout << "11 - Remove place" << std::endl;
    std::cout << "0  - Back" << std::endl;

    return nextUnsignedInt("Option: ", 11);
}

void nodeMenu(GarbageManagement &management){
    switch(nodeMenuDialog()) {
        case 1:
            createSimpleLocation(management);
            break;
        case 2:
            createGarage(management);
            break;
        case 3:
            createContainerOrStation(management, "container");
            break;
        case 4:
            createContainerOrStation(management, "station");
            break;
        case 5:
            listGarages(management);
            break;
        case 6:
            listContainers(management);
            break;
        case 7:
            listStations(management);
            break;
        case 8:
            removeBuilding(management, "garage");
            break;
        case 9:
            removeBuilding(management, "container");
            break;
        case 10:
            removeBuilding(management, "station");
            break;
        case 11:
            removeBuilding(management, "place");
            break;
        case 0:
            mainMenu(management);
            break;
        default:
            break;
    }
    mainMenu(management);
}

unsigned int mainMenuDialog(){
    std::cout << "Main Menu" << std::endl;
    std::cout << "1 - Node Menu" << std::endl;
    std::cout << "2 - Edge Menu" << std::endl;
    std::cout << "3 - Vehicle Menu" << std::endl;
    std::cout << "4 - Settings Menu" << std::endl;
    std::cout << "5 - Collect Garbage" << std::endl;
    std::cout << "6 - Evaluate Connectivity" << std::endl;
    std::cout << "7 - Stress test" << std::endl;
    std::cout << "0 - Exit" << std::endl;

    return nextUnsignedInt("Option: ", 7);
}

void mainMenu(GarbageManagement &management) {
    switch (mainMenuDialog()) {
        case 1:
            nodeMenu(management);
        break;
        case 2:
            edgeMenu(management);
        break;
        case 3:
            vehicleMenu(management);
        break;
        case 4:
            settingsMenu(management);
            break;
        case 5:
            garbageServiceMenu(management);
            break;
        case 6:
            management.evalCon();
            break;
        case 7:
            break;
        case 0:
            break;
        default:
            break;
    }
}

unsigned int garbageService(){
    std::cout << "Garbage Service Menu" << std::endl;
    std::cout << "1 - Undifferentiated trash & Unlimited capacity" << std::endl;
    std::cout << "2 - Differentiated trash & Unlimited capacity" << std::endl;
    std::cout << "3 - Differentiated trash & Limited capacityu" << std::endl;
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Option: ", 3);
}

void garbageServiceMenu(GarbageManagement &management) {
    switch (mainMenuDialog()) {
        case 1:
//            management.dosomething();
            break;
        case 2:
//            management.dosomething();
            break;
        case 3:
//            management.dosomething();
            break;
        case 0:
            mainMenu(management);
            break;
        default:
            break;
    }
}
