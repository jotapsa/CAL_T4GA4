#include <iostream>
#include <iomanip>
#include "GarbageManagement.h"
#include "Cli.h"
#include "GarbageType.h"
#include "Algorithm.h"

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

    return temp == "Y" || temp == "y";
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

unsigned long int getUnsignedInt(std::string str) {
    unsigned long int number;
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
    std::cout << "1 - List Vehicles" << std::endl;
    std::cout << "2 - Create Vehicle" << std::endl;
    std::cout << "3 - Remove Vehicle" << std::endl;
    std::cout << "4 - Add Vehicle type" << std::endl; //TODO only change Type ?
    std::cout << "5 - Remove Vehicle type" << std::endl; //TODO only change Type ?
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Option: ", 4);
}

void listAllVehicles(GarbageManagement &management) {

    for(auto garage: management.getGarages()) {
        std::cout << "\nGarage: " << garage->getPlace()->getID() << " #Vehicles: " << garage->getNumberOfVehicles() << std::endl;
        std::cout << std::endl << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH)  << "Vehicle ID";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << " Plate ";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Garbage Type";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Capacity";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Free Space" << std::endl;

        for(auto vehicle: garage->getVehicles()) {

            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << vehicle->getID();
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << vehicle->getPlate();
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << vehicle->getTypesString();
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << vehicle->getCapacityString();
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << vehicle->getFreeSpaceString() << std::endl;
        }
    }

    std::cout << std::endl << "Leave? ";

    if(!readConfirmation())
        listAllVehicles(management);
}

void vehicleMenu(GarbageManagement &management){
    switch(vehicleMenuDialog()){
        case 1:
            listAllVehicles(management);
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

    vehicleMenu(management);
}

unsigned int edgeMenuDialog() {
    std::cout << "Edge Menu" << std::endl;
    std::cout << "1 - Create Edge"  << std::endl;
    std::cout << "2 - Remove Edge"  << std::endl;
    std::cout << "3 - List streets" << std::endl;
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Option: ", 3);
}

void listAllStreets(GarbageManagement &management) {

    unsigned int maxStreetLength = 0;

    std::vector<std::pair<unsigned long, std::string>> allStreets = management.getAllStreetNames();

    for(auto street : allStreets){
        street.second.length() > maxStreetLength ? maxStreetLength = street.second.length() : maxStreetLength = maxStreetLength;
    }

    std::cout << std::left << std::endl << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH)   << "Street ID";

    std::cout << std::left << std::setfill(' ') << std::setw(maxStreetLength / 2)  << "Name";

    std::cout << std::right << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH)  << "Edge ID";

    for(auto street : allStreets) {

        std::cout << std::left << std::endl << std::setfill(' ') << std::setw(MAX_ULONG_WITH + 2) << street.first;

        std::cout << std::setfill(' ') << std::setw(maxStreetLength + 4) << street.second;

        std::cout << std::left << std::setfill(' ') << std::setw(MAX_ULONG_WITH + 7) << management.getStreet(street.first)->getEdgeID();
    }

    std::cout << std::endl << "Leave? ";

    if(!readConfirmation())
        listAllStreets(management);
}

void createEdge(GarbageManagement &management) {
    unsigned long destinationPlace = 0;
    unsigned long beginningPlace = 0;

    std::string streetName;

    streetName.clear();

    EdgeType isTwoWay;

    unsigned long streetID = getUnsignedInt("Insert a street ID: ");

    while(management.getPlace(beginningPlace) == nullptr) {
        beginningPlace = getUnsignedInt("Insert starting place ID: ");
    }

    while(management.getPlace(destinationPlace) == nullptr) {
        destinationPlace = getUnsignedInt("Insert destination place ID: ");
    }

    double weight = parseDouble("Insert edge weight:");

    std::cout << "Is it a two way street?";

    readConfirmation() ? isTwoWay = (EdgeType)0 : (EdgeType)1;

    while(streetName.empty()){
        std::cout << "Insert street name: ";
        std::getline(std::cin, streetName);
    }

    std::cout << "Read: " << streetName << std::endl;

    management.addEdge(weight, streetID, std::make_pair(beginningPlace, destinationPlace), isTwoWay, streetName);

    std::cout << streetName << " connecting nodes: " << beginningPlace << " -> " << destinationPlace << " with weight " <<  weight << " has been added.\n";
}

void edgeMenu(GarbageManagement &management) {

    switch(edgeMenuDialog()) {
        case 1:
            createEdge(management);
            break;
        case 2:
            management.removeEdge(getUnsignedInt("Insert Edge ID: "));
            break;
        case 3:
            listAllStreets(management);
            break;
        case 0:
            mainMenu(management);
            return;
        default:
            break;
    }

    edgeMenu(management);
}

std::pair<double, double> askForLocation() {

    double lat = parseDouble("\tInsert Latitude: ");
    double lon = parseDouble("\tInsert Longitude: ");

    return std::make_pair(lat, lon);
};

void createSimpleLocation(GarbageManagement &management) {

    std::pair<double,double> placeLocation = askForLocation();

    std::pair<int,int> windowLocation = convertToCoords(placeLocation);

    unsigned long placeID = Place::getUnusedId();

    if(!insideWindow(windowLocation)) {
        std::cout << "That Place doesn't fit the map!\n";
        return;
    }
    else {
        management.addPlace(new Place(placeID,
                                      placeLocation.first,
                                      placeLocation.second,
                                      placeLocation.first * DEG_TO_RAD,
                                      placeLocation.second * DEG_TO_RAD,
                                      windowLocation));

        management.rearrange();

        std::cout << "Place added with success with ID: " << placeID << std::endl;
    }

}

void createGarage(GarbageManagement &management) {

    std::cout << "Insert location for Garage:\n";

    std::pair<double,double> garageCoordinates = askForLocation();

    std::pair<int,int> windowLocation = convertToCoords(garageCoordinates);

    unsigned long garageID;

    if(!insideWindow(windowLocation)) {
        std::cout << "That location doesn't fit the map!\n";
        return;
    }
    else {
        garageID = Place::getUnusedId();

        management.addGarage(new Garage(new Place(garageID,
                                                  garageCoordinates.first,
                                                  garageCoordinates.second,
                                                  garageCoordinates.first * DEG_TO_RAD,
                                                  garageCoordinates.second * DEG_TO_RAD,
                                                  windowLocation)));

        management.rearrange();

        std::cout << "Garage added with success with ID: " << garageID << std::endl;
    }
}

unsigned int selectGarbageTypeMenu() {

    std::cout << "Select garbage type:" << std::endl;
    std::cout << "\t1 - Glass" << std::endl;
    std::cout << "\t2 - Plastic" << std::endl;
    std::cout << "\t3 - Paper" << std::endl;
    std::cout << "\t4 - Generic" << std::endl;
    std::cout << "\t5 - Exit" << std::endl;

    return nextUnsignedInt("Option: ", 5);
}

unsigned int selectAlgorithMenu() {

    std::cout << "Select the algorithm to calculate paths:" << std::endl;
    std::cout << "\t1 - Dijkstra" << std::endl;
    std::cout << "\t2 - A*" << std::endl;
    std::cout << "\t3 - Floyd Warshall" << std::endl;
    std::cout << "\t4 - Exit" << std::endl;

    return nextUnsignedInt("Option: ", 4);
}

//Container and Station both use the same parameters
void createContainerOrStation(GarbageManagement &management, std::string buildingType) {

    std::cout << "Insert location for " << buildingType << ": \n";

    std::pair<double, double> buildingCoordinates = askForLocation();

    std::pair<int, int> windowLocation = convertToCoords(buildingCoordinates);

    if(!insideWindow(windowLocation)) {
        std::cout << "That location doesn't fit the map!\n";
        return;
    }

    unsigned long buildingID = Place::getUnusedId();

    unsigned int garbageTypeIndex = selectGarbageTypeMenu() - 1;

    if(garbageTypeIndex == 5) {
        return;
    }

    Place *newPlace = new Place(buildingID,
                                buildingCoordinates.first,
                                buildingCoordinates.second,
                                buildingCoordinates.first * DEG_TO_RAD,
                                buildingCoordinates.second * DEG_TO_RAD,
                                windowLocation);

    double capacity = 0;

    while(capacity <= 0) {

        capacity = parseDouble("Insert " + buildingType + " capacity: ");

        if(capacity <= 0) {
            std::cout << "Capacity must be a positive value!\n";
        }
    }

    switch (buildingType.at(0)) {
        case 'c':
            management.addContainer(new Container(newPlace, (GarbageType)garbageTypeIndex, capacity));
            break;
        case 's':
            management.addStation(new Station(newPlace));
            break;
        default:
            std::cout << "Failed to create Station!\n"; //TODO distinguir ?
            return;
    }

    management.rearrange();

    std::cout << buildingType << " added with success, with ID: " << buildingID << std::endl;
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
    std::cout << std::setfill('-') << std::setw(MAX_DOUBLE_WITH + MAX_DOUBLE_WITH) << "-"<< std::endl;

    do {
        std::cout << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << "Node ID";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Longitude";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Latitude";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH)  << "#Vehicles" << std::endl;

        for(auto garage : management.getGarages()) {

            std::cout << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << garage->getPlace()->getID();
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << garage->getPlace()->getLongitudinalCoordinates().first;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << garage->getPlace()->getLongitudinalCoordinates().second;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH)  << garage->getNumberOfVehicles() << std::endl;
        }

        selectedID = getUnsignedInt("Insert node ID to edit Garage, 0 to leave: ");

        if(management.getPlace(selectedID) != nullptr){
            editNode(selectedID);
        }

    }while(selectedID != 0);
}

void listContainers(GarbageManagement &management) {

    unsigned int selectedID;

    std::cout << std::setfill('-') << std::setw(MAX_ULONG_WITH + MAX_DOUBLE_WITH + MAX_DOUBLE_WITH) << " Containers ";
    std::cout << std::setfill('-') << std::setw(MAX_DOUBLE_WITH + MAX_DOUBLE_WITH) << "-"<< std::endl;

    do {
        std::cout << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << "Node ID";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Longitude";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Latitude";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Type";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Capacity" << std::endl;

        for(auto container : management.getContainers()) {

            std::cout << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << container->getPlace()->getID();
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << container->getPlace()->getLongitudinalCoordinates().first;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << container->getPlace()->getLongitudinalCoordinates().second;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH)  << getGarbageType(container->getType());
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << container->getCapacity() << std::endl;
        }

        selectedID = getUnsignedInt("Insert node ID to edit Container, 0 to leave: ");

        if(management.getPlace(selectedID) != nullptr){
            editNode(selectedID);
        }

    }while(selectedID != 0);
}

void listStations(GarbageManagement &management) {

    unsigned int selectedID;

    std::cout << std::setfill('-') << std::setw(MAX_ULONG_WITH + MAX_DOUBLE_WITH + MAX_DOUBLE_WITH) << " Stations ";
    std::cout << std::setfill('-') << std::setw(MAX_DOUBLE_WITH + MAX_DOUBLE_WITH) << "-"<< std::endl;

    do {
        std::cout << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << "Node ID";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Longitude";
        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Latitude" << std::endl;

        for(auto station : management.getStations()) {

            std::cout << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << station->getPlace()->getID();
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << station->getPlace()->getLongitudinalCoordinates().first;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << station->getPlace()->getLongitudinalCoordinates().second << std::endl;
        }

        selectedID = getUnsignedInt("Insert node ID to edit Station, 0 to leave: ");

        if(management.getPlace(selectedID) != nullptr){
            editNode(selectedID);
        }

    }while(selectedID != 0);
}

void removeBuilding(GarbageManagement &management, std::string type) {

    unsigned long nodeId = getUnsignedInt("Insert " + type + " ID to remove: ");

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
    std::cout << "1  - Create Place" << std::endl;
    std::cout << "2  - Create Garage" << std::endl;
    std::cout << "3  - Create Container" << std::endl;
    std::cout << "4  - Create Station" << std::endl;
    std::cout << "5  - List Garages" << std::endl;
    std::cout << "6  - List Containers" << std::endl;
    std::cout << "7  - List Stations" << std::endl;
    std::cout << "8  - Remove Garage" << std::endl;
    std::cout << "9  - Remove Container" << std::endl;
    std::cout << "10 - Remove Station" << std::endl;
    std::cout << "11 - Remove Place" << std::endl;
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

    nodeMenu(management);
}

unsigned int mainMenuDialog(){
    std::cout << "Main Menu" << std::endl;
    std::cout << "1 - Node Menu" << std::endl;
    std::cout << "2 - Edge Menu" << std::endl;
    std::cout << "3 - Vehicle Menu" << std::endl;
    std::cout << "4 - Settings Menu" << std::endl;
    std::cout << "5 - Garbage Service" << std::endl;
    std::cout << "6 - Evaluate Connectivity" << std::endl;
    std::cout << "7 - Stress Test" << std::endl;
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
    std::cout << "3 - Differentiated trash & Limited capacity" << std::endl;
    std::cout << "4 - Set Container fill percentage needed for pickup" << std::endl;
    std::cout << "5 - Set Algorithm" << std::endl;
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Option: ", 5);
}

void setFillPercentageInteraction(GarbageManagement &management) {

    int  percentage = 0;

    while(percentage <= 0) {

        percentage = getUnsignedInt("\tInsert Percentage: ");

        if(percentage <= 0 || percentage > 100) {
            std::cout << "Percentage must be a value between 0 and 100.";
        }
    }

    management.setFillPerNeeded((float)percentage / 100.0);

    std::cout << "Percentage set to: " << management.getFillPerNeeded() * 100.0 << " %\n";
}

void setAlgorithmInteraction(GarbageManagement &management) {

    unsigned int option = selectAlgorithMenu();

    if(option == 4) {
        return;
    }

    Algorithm alg = (Algorithm)(option - 1);

    management.setAlgorithm(alg);

    std::cout << "Now using " << getAlgorithmName(management.getAlgorithm()) << " algorithm to calculate paths.\n";
}

void garbageServiceMenu(GarbageManagement &management) {
    switch (garbageService()) {
        case 1:
            management.collectGarbage();
            break;
        case 2:
            management.collectGarbage();
            break;
        case 3:
            management.collectGarbage();
            break;
        case 4:
            setFillPercentageInteraction(management);
            break;
        case 5:
            setAlgorithmInteraction(management);
            break;
        case 0:
            mainMenu(management);
            return;
        default:
            break;
    }

    garbageServiceMenu(management);
}
