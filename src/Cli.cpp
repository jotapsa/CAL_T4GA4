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

    unsigned long createdNodeId = management.getValidNodeID();

    management.addPlace(new Place(createdNodeId, askForLocation()));

    std::cout << "Added: nodeID-> " << createdNodeId << std::endl;
}

void createGarage(GarbageManagement &management) {
//TODO (Check if added garage is inside map window)

    std::cout << "Insert location for garage:\n";

    std::pair<double,double> garageCoordinates = askForLocation();

    unsigned long createdNodeId = management.getValidNodeID();

    management.addGarage(new Garage(createdNodeId, garageCoordinates));

    std::cout << "Added garage with ID= " << createdNodeId << std::endl;
}

//Container and Station both use the same parameters
void createContainerOrStation(GarbageManagement &management, std::string buildingType) {

    std::cout << "Insert location for " << buildingType << ": \n";

    std::pair<double,double> containerCoordinates = askForLocation();

    unsigned long createdNodeId = management.getValidNodeID();

    unsigned int garbageTypeIndex = selectGarbageTypeMenu();

    if(garbageTypeIndex == 0)
        return;

    double capacity = parseDouble("Insert " + buildingType + " capacity: ");

    if(buildingType.compare("container") == 0)
        management.addContainer(new Container(createdNodeId, containerCoordinates, getGarbageTypeForOption(garbageTypeIndex), capacity));
    else
        management.addStation(new Station(createdNodeId, containerCoordinates, getGarbageTypeForOption(garbageTypeIndex), capacity));

    std::cout << buildingType << " added with node ID: " << createdNodeId << std::endl;
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

unsigned int nodeMenuDialog() {
    std::cout << "\nNode Menu" << std::endl;
    std::cout << "1  - Create Location" << std::endl;
    std::cout << "2  - Create Garage" << std::endl;
    std::cout << "3  - Create Container" << std::endl;
    std::cout << "4  - Create Station" << std::endl;
    std::cout << "5  - List Locations" << std::endl;
    std::cout << "6  - List Garages" << std::endl;
    std::cout << "7  - List Containers" << std::endl;
    std::cout << "8  - List Stations" << std::endl;
    std::cout << "9  - Remove Location" << std::endl;
    std::cout << "10 - Remove Garage" << std::endl;
    std::cout << "11 - Remove Container" << std::endl;
    std::cout << "12 - Remove Container" << std::endl;
    std::cout << "0  - Back" << std::endl;

    return nextUnsignedInt("Option: ", 8);
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
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
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
