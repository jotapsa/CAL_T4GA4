#include <iostream>
#include <iomanip>
#include "GarbageManagement.h"
#include "Cli.h"
#include "GarbageType.h"
#include "Algorithm.h"
#include <fstream>
#include "Parser.h"

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

bool askMap(GarbageManagement &management){
    std::fstream mapsList;
    std::string mapName, mapPath,line;
    std::vector<std::string> map, mapPaths, mapNames;
    unsigned int i=1;

    mapsList.open(MAPSLIST_FILEPATH);

    if(!mapsList.is_open()) {
        std::cout << "Maps List could not be open!\n";
        return false;
    }

    std::cout << "\nChoose a Map:" << std::endl;
    while(getline(mapsList, line)){
        map = split(line,';');
        mapNames.push_back(map.at(0));
        mapPaths.push_back(map.at(1));
        std::cout << "\t" << i << " - " << map.at(0) << std::endl;
        i++;
    }
    std::cout << "\t0  - Create New Map" << std::endl;

    i = nextUnsignedInt("Map: ", mapPaths.size());

    switch(i){
        case 0:{
            do{
                std::cout << "Name: ";
                getline(std::cin,mapName);
            }while(mapName.length() <=0);

            do{
                std::cout << "Path Name: ";
                getline(std::cin, mapPath);
            }while(mapPath.length() <=0);

            management.setMapName(mapName);
            management.setMapPath(mapPath);
            return false;
        }
        default:{
            management.setMapPath(mapPaths.at(i-1));
            management.setMapName(mapNames.at(i-1));
        }
    }

    return true;
}

unsigned int editGarageOption() {

    std::cout << "-----Garage options------" << std::endl;
    std::cout << "1 - Edit garage location" << std::endl;
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Option: ", 1);
}

void editGarageMenu(GarbageManagement &management) {

    unsigned long garageID;

    Garage *editing = nullptr;

    do {
        printMainHeader("Garages", 2 * MAX_DOUBLE_WITH);

        printTableCell("Garage ID", MAX_DOUBLE_WITH, 'l');

        printTableCell("#Vehicles", MAX_DOUBLE_WITH, 'r');

        std::cout << std::endl;

        for(auto garage : management.getGarages()) {
            std::cout << std::left << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << garage->getPlace()->getID();
            std::cout << std::right << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << garage->getNumberOfVehicles() << std::endl;
        }

        garageID = getUnsignedInt("Insert a garage ID to edit: ");

    } while((editing = management.getGarage(garageID)) == nullptr);

    if(editGarageOption() == 0) {
        return;
    }

    std::cout << "Insert new garage coordinates.\n";

    double newLongitude = parseDouble("Insert new longitude (value above 180 degrees to maintain previous value):");

    double newLatitude = parseDouble("Insert new latitude (value above 90 degrees to maintain previous value):");

    if(newLongitude <= 180) {
        editing->getPlace()->setLon(newLongitude);
    }
    else{
        std::cout << "Maintained previous longitude!\n";
    }

    if(newLatitude <= 90) {
        editing->getPlace()->setLat(newLatitude);
    }
    else {
        std::cout << "Maintained previous latitude!\n";
    }

    std::cout << "New data for this garage:\n" << editing->toString() << std::endl;
}

unsigned int editMenuDialog() {

    std::cout << "-------Settings-------" << std::endl;
    std::cout << "\t1 - Edit garage" << std::endl;
    std::cout << "\t2 - Edit container" << std::endl;
    std::cout << "\t3 - Edit station" << std::endl;
    std::cout << "\t0 - Back" << std::endl;

    return nextUnsignedInt("Option: ", 3);
}

void editContainerMenu(GarbageManagement &management) {

    unsigned long containerID;
    double newLongitude;
    double newLatitude;
    int garbageType;
    double newCapacity;
    double percentage;

    Container *toEdit = nullptr;

    do {
        printMainHeader("Containers", 4 * MAX_DOUBLE_WITH);

        std::cout << std::endl;

        printTableCell("Container ID", MAX_DOUBLE_WITH, 'l');

        printTableCell("Garbage type", MAX_DOUBLE_WITH, 'e');

        printTableCell("Capacity", MAX_DOUBLE_WITH, 'e');

        printTableCell("Filled (%)", MAX_DOUBLE_WITH, 'e');

        std::cout << std::endl;

        for(auto container : management.getContainers()) {
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << container->getPlace()->getID();
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << getGarbageType(container->getType());
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << container->getCapacity();
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << container->getFilledPer() << std::endl;
        }

        containerID = getUnsignedInt("Insert a container ID to edit: ");

    } while((toEdit = management.getContainer(containerID)) == nullptr);

    switch (editContainerMenu()) {
        case 0:
            return;
        case 1:
            std::cout << "Insert new garage coordinates.\n";
            newLongitude = parseDouble("Insert new longitude (value above 180 degrees to maintain previous value):");
            newLatitude = parseDouble("Insert new latitude (value above 90 degrees to maintain previous value):");
            if(newLongitude <= 180) {
                toEdit->getPlace()->setLon(newLongitude);
            }
            else{
                std::cout << "Maintained previous longitude!\n";
            }
            if(newLatitude <= 90) {
                toEdit->getPlace()->setLat(newLatitude);
            }
            else {
                std::cout << "Maintained previous latitude!\n";
            }
            break;
        case 2:
           garbageType =  selectGarbageTypeMenu() - 1;
           if(garbageType == 4) {
               return;
           }
           toEdit->setGarbageType((GarbageType) garbageType);
           break;
        case 3:
            newCapacity = 0;
            while(newCapacity <= 0) {
                newCapacity = parseDouble("Insert new capacity for container: ");
            }
            toEdit->setCapacity(newCapacity);
            break;
        case 4:
            percentage = -1;
            while(percentage < 0 ||  percentage > 100) {
                percentage = parseDouble("Insert new filled percentage for container: ");
            }
            //TODO Sa
//            toEdit->setFilledPer(percentage);
            break;
        default:
            return;
    }

    std::cout << "New data for this container:\n" << toEdit->toString() << std::endl;
}

unsigned int editContainerMenu() {

    std::cout << "---------Container options----------" << std::endl;
    std::cout << "1 - Edit container location" << std::endl;
    std::cout << "2 - Edit container type" << std::endl;
    std::cout << "3 - Edit container capacity" << std::endl;
    std::cout << "4 - Edit container filled percentage" << std::endl;
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Option: ", 4);
}

unsigned int editStationMenu() {

    std::cout << "------Station options------" << std::endl;
    std::cout << "1 - Edit container location" << std::endl;
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Option: ", 1);
}

void editStation(GarbageManagement &management) {

    unsigned long stationID;
    double newLongitude;
    double newLatitude;

    Station *toEdit = nullptr;

    do {
        printMainHeader("Stations", MAX_DOUBLE_WITH);

        std::cout << std::endl;

        printTableCell("Station ID", MAX_DOUBLE_WITH, 'l');

        std::cout << std::endl;

        for(auto station : management.getStations()) {
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << station->getPlace()->getID() << std::endl;
        }

        stationID = getUnsignedInt("Insert a station ID to edit: ");

    } while((toEdit = management.getStation(stationID)) == nullptr);


    if(editGarageOption() == 0) {
        return;
    }

    std::cout << "Insert new garage coordinates.\n";

    newLongitude = parseDouble("Insert new longitude (value above 180 degrees to maintain previous value):");

    newLatitude = parseDouble("Insert new latitude (value above 90 degrees to maintain previous value):");

    if(newLongitude <= 180) {
        toEdit->getPlace()->setLon(newLongitude);
    }
    else{
        std::cout << "Maintained previous longitude!\n";
    }

    if(newLatitude <= 90) {
        toEdit->getPlace()->setLat(newLatitude);
    }
    else {
        std::cout << "Maintained previous latitude!\n";
    }

    std::cout << "New data for this station:\n" << toEdit->toString() << std::endl;
}

void editMenu(GarbageManagement &management) {

    while(true) {

        switch (editMenuDialog()) {
            case 1:
                editGarageMenu(management);
                break;
            case 2:
                editContainerMenu(management);
                break;
            case 3:
                editStation(management);
                break;
            case 0:
                management.rearrange();
                return;
            default:
                break;
        }
    }
}

unsigned int vehicleMenuDialog(){
    std::cout << "---Vehicle Menu--" << std::endl;
    std::cout << "1 - List Vehicles" << std::endl;
    std::cout << "2 - Create Vehicle" << std::endl;
    std::cout << "3 - Remove Vehicle" << std::endl;
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Option: ", 3);
}

void listAllVehicles(GarbageManagement &management) {

    printMainHeader("Vehicles List", 5 * MAX_DOUBLE_WITH);

    for(auto garage: management.getGarages()) {
        std::cout << "\nGarage: " << garage->getPlace()->getID() << " #Vehicles: " << garage->getNumberOfVehicles() << std::endl;
        std::cout << std::endl;

        printTableCell("Vehicle ID", MAX_DOUBLE_WITH, 'e');
        printTableCell(" Plate ", MAX_DOUBLE_WITH, 'e');
        printTableCell("Garbage Type", MAX_DOUBLE_WITH, 'e');
        printTableCell("Capacity", MAX_DOUBLE_WITH, 'e');
        printTableCell("Free Space", MAX_DOUBLE_WITH, 'e');

        std::cout << std::endl;

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

void createVehicle(GarbageManagement &management) {

    unsigned int vehicleID = getUnsignedInt("Insert an id to the new vehicle: ");

    unsigned long garageID = 0;

    std::string plate;

    std::vector<GarbageType> garbageThatTruckCanCarry;

    std::vector<double> capacities;

    Vehicle * newVehicle;

    double capacity;

    int typeOfGarbage = -1;

    //TODO Validate truck number plate with regular expression
    while(plate.length() != 8) {
        plate.clear();
        std::cout << "Insert a valid number plate for the new vehicle: ";
        std::getline(std::cin, plate);
    }

    while(true) {
        std::cout << "Types of garbage:" << std::endl;
        std::cout << "\t1 - Glass" << std::endl;
        std::cout << "\t2 - Plastic" << std::endl;
        std::cout << "\t3 - Paper" << std::endl;
        std::cout << "\t4 - Generic" << std::endl;
        std::cout << "\t0 - Finish garbage types insertion." << std::endl;

        typeOfGarbage = nextUnsignedInt("Insert an option: ", 4);

        if(typeOfGarbage == 0)
            break;

        bool alreadyExists = false;

        for (auto garbageType : garbageThatTruckCanCarry) {
            if (garbageType == (GarbageType)(typeOfGarbage - 1)) {
                alreadyExists = true;
            }
        }

        if (!alreadyExists) {
            garbageThatTruckCanCarry.push_back((GarbageType)(typeOfGarbage - 1));
        }
    }

    for(auto garbageType : garbageThatTruckCanCarry) {

        capacity = -1;

        do {
            capacity = parseDouble("Insert capacity for " + getGarbageType(garbageType) + " garbage: ");
        } while(capacity < 0);

        capacities.push_back(capacity);
    }

    do {
        std::cout << std::right << std::setfill('-') << std::setw(MAX_DOUBLE_WITH) << "Garages";

        std::cout << std::right << std::setfill('-') << std::setw(MAX_DOUBLE_WITH) << "-" << std::endl;

        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "Garage ID";

        std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << "#Vehicles" <<  std::endl;

        for(auto garage : management.getGarages()) {
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << garage->getPlace()->getID();
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << garage->getNumberOfVehicles() << std::endl;
        }

        garageID = getUnsignedInt("Insert a garage ID that new vehicle will belong to: ");

    } while(management.getGarage(garageID) == nullptr);

    newVehicle = new Vehicle(vehicleID, management.getGarage(garageID), plate, garbageThatTruckCanCarry, capacities);

    management.addVehicle(garageID, newVehicle);

    management.rearrange();

    std::cout << "Vehicle added!\n";
}

void deleteVehicle(GarbageManagement &management) {

    unsigned long vehicleID = getUnsignedInt("Insert vehicle ID to remove: ");

    for(auto garage: management.getGarages()) {

        for(auto vehicle: garage->getVehicles()) {

            if(vehicleID == vehicle->getID()) {
                management.removeVehicle(vehicleID);

                std::cout << "Vehicle " << vehicleID << " was removed with success from garage " << garage->getPlace()->getID() << std::endl;

                return;
            }
        }
    }

    std::cout << "Vehicle " << vehicleID << " doesn't exist!\n";
}

void vehicleMenu(GarbageManagement &management){

    while(true) {
        switch(vehicleMenuDialog()){
            case 1:
                listAllVehicles(management);
                break;
            case 2:
                createVehicle(management);
                break;
            case 3:
                deleteVehicle(management);
                break;
            case 0:
                return;
            default:
                break;
        }
    }
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

    do{
        for(auto street : allStreets){
            street.second.length() > maxStreetLength ? maxStreetLength = street.second.length() : maxStreetLength = maxStreetLength;
        }

        printMainHeader("Streets", 2 * MAX_ULONG_WITH + maxStreetLength);

        printTableCell("Street ID", MAX_DOUBLE_WITH, 'l');
        printTableCell("Name", maxStreetLength, 'l');
        printTableCell("Edge ID", MAX_ULONG_WITH, 'l');

        for(auto street : allStreets) {

            std::cout << std::left << std::endl << std::setfill(' ') << std::setw(MAX_ULONG_WITH + 2) << street.first;

            std::cout << std::setfill(' ') << std::setw(maxStreetLength + 4) << street.second;

            std::cout << std::left << std::setfill(' ') << std::setw(MAX_ULONG_WITH) << management.getStreet(street.first)->getEdgeID();
        }

        std::cout << std::endl << "Leave? ";
    }while(readConfirmation());
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

    while(true) {

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
                return;
            default:
                break;
        }
    }
}

std::pair<double, double> askForLocation() {

    double lat = parseDouble("\tInsert Latitude: ");
    double lon = parseDouble("\tInsert Longitude: ");

    return std::make_pair(lat, lon);
};

void printMainHeader(std::string title, unsigned short length) {
    std::cout << std::right << std::setfill('-') << std::setw(length / 2) << title;

    std::cout << std::right << std::setfill('-') << std::setw(length / 2) << "-" << std::endl;
}

void printTableCell(std::string info, unsigned short length, char allignment) {

    switch(allignment) {
        case 'l':
            std::cout << std::left << std::setfill(' ') << std::setw(length) << info;
            break;
        case 'r':
            std::cout << std::right << std::setfill(' ') << std::setw(length) << info;
            break;
        default:
            std::cout << std::left << std::setfill(' ') << std::setw(length) << info;
            break;
    }

}

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
            std::cout << "Failed to create " <<  buildingType <<"!\n";
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

    while(true) {

        printMainHeader("Garage", MAX_ULONG_WITH + 3 * MAX_DOUBLE_WITH);

        printTableCell("Garage ID", MAX_ULONG_WITH, 'l');
        printTableCell("Longitude", MAX_DOUBLE_WITH, 'r');
        printTableCell("Latitude", MAX_DOUBLE_WITH, 'r');
        printTableCell("#Vehicles", MAX_DOUBLE_WITH, 'r');

        std::cout << std::endl;

        for(auto garage : management.getGarages()) {

            std::cout << std::left << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << garage->getPlace()->getID();
            std::cout << std::right << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << garage->getPlace()->getLongitudinalCoordinates().first;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << garage->getPlace()->getLongitudinalCoordinates().second;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH)  << garage->getNumberOfVehicles() << std::endl;
        }

        std::cout << "Leave?";

        if(readConfirmation())
            return;
    }
}

void listContainers(GarbageManagement &management) {

    while(true) {

        printMainHeader("Containers", (MAX_ULONG_WITH +  4 * MAX_DOUBLE_WITH));

        printTableCell("Node ID", MAX_ULONG_WITH, 'l');
        printTableCell("Longitude", MAX_DOUBLE_WITH, 'r');
        printTableCell("Latitude", MAX_DOUBLE_WITH, 'r');
        printTableCell("Type", MAX_DOUBLE_WITH, 'r');
        printTableCell("Capacity", MAX_DOUBLE_WITH, 'r');

        std::cout << std::endl;

        for(auto container : management.getContainers()) {

            std::cout << std::left << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << container->getPlace()->getID();
            std::cout << std::right << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << container->getPlace()->getLongitudinalCoordinates().first;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << container->getPlace()->getLongitudinalCoordinates().second;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << getGarbageType(container->getType());
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << container->getCapacity() << std::endl;
        }

        std::cout << "Leave?";

        if(readConfirmation())
            return;
    }
}

void listStations(GarbageManagement &management) {

    while(true) {
        printMainHeader("Stations", (MAX_ULONG_WITH +  2 * MAX_DOUBLE_WITH));

        printTableCell("Node ID", MAX_ULONG_WITH, 'l');
        printTableCell("Longitude", MAX_DOUBLE_WITH, 'r');
        printTableCell("Latitude", MAX_DOUBLE_WITH, 'r');

        std::cout << std::endl;

        for(auto station : management.getStations()) {

            std::cout << std::left << std::setfill(' ') << std::setw(MAX_ULONG_WITH)  << station->getPlace()->getID();
            std::cout << std::right << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << station->getPlace()->getLongitudinalCoordinates().first;
            std::cout << std::setfill(' ') << std::setw(MAX_DOUBLE_WITH) << station->getPlace()->getLongitudinalCoordinates().second << std::endl;
        }

        std::cout << "Leave?";

        if(readConfirmation())
            return;
    }
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

void nodeMenu(GarbageManagement &management) {

    while(true) {

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
                return;
            default:
                break;
        }
    }

}

unsigned int mainMenuDialog(){
    std::cout << "\nMain Menu" << std::endl;
    std::cout << "1 - Node Menu" << std::endl;
    std::cout << "2 - Edge Menu" << std::endl;
    std::cout << "3 - Vehicle Menu" << std::endl;
    std::cout << "4 - Edit Menu" << std::endl;
    std::cout << "5 - Garbage Service" << std::endl;
    std::cout << "6 - Evaluate Connectivity" << std::endl;
    std::cout << "7 - Stress Test" << std::endl;
    std::cout << "0 - Exit" << std::endl;

    return nextUnsignedInt("Option: ", 7);
}

void mainMenu(GarbageManagement &management) {

    while(true) {

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
                editMenu(management);
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
                return;
            default:
                break;
        }
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

    while(true) {

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
                return;
            default:
                break;
        }
    }
}
