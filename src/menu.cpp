#include "../include/menu.h"

std::string Menu::BUS_ADMIN_PASSWORD = "toni";
bool Menu::exitApplication = false;

void Menu::init() {

    BusCompany stcp{"STCP"};

    atexit(Menu::endProgram);

    while (!Menu::exitApplication) {

        std::cout << std::string(100, '\n');

        int option = Menu::showInitialMenu(stcp.getName());

        switch (option) {
            case CLIENT:
            case ADMIN:

                if (option == CLIENT) {

                    option = Menu::showClientMenu();

                    switch (option) {
                        case CLIENT_LIST_ALL_STOPS:
                            Menu::listStops(stcp);
                            break;
                        case CLIENT_LIST_LINES:
                            Menu::listStops(stcp);
                            break;
                        case CLIENT_TRAVEL_DISTANCE:
                            Menu::travelMinDistance(stcp);
                            break;
                        case CLIENT_TRAVEL_DISTANCE_NEARBY:
                            Menu::travelMinDistanceCoord(stcp);
                            break;
                        case CLIENT_TRAVEL_STOPS:
                            Menu::travelMinStops(stcp);
                            break;
                        case CLIENT_TRAVEL_STOPS_NEARBY:
                            Menu::travelMinStopsCoord(stcp);
                            break;
                        case CLIENT_TRAVEL_ZONES:
                            Menu::travelMinZones(stcp);
                            break;
                        case CLIENT_TRAVEL_ZONES_NEARBY:
                            Menu::travelMinZonesCoord(stcp);
                            break;
                        case CLIENT_WALKING:
                            Menu::changeWalkingDistance(stcp);
                            break;
                        case CLIENT_BACK:
                            break;
                        default:
                            std::cout << "Invalid option, returning to main menu\n\n";
                            break;
                    }

                } else {

                    option = Menu::showAdminMenu();

                    switch (option) {
                        case ADMIN_BACK:
                            break;
                        default:
                            std::cout << "Invalid option, returning to main menu\n\n";
                            break;
                    }
                }
                break;
            case LEAVE:
                Menu::exitApplication = true;
                break;
            default:
                std::cout << "\tInvalid option chosen!\n\n";
                break;
        }
    }
}

int Menu::showAdminMenu() {

    std::string password;
    std::cout << "\tEnter your password please: ";
    std::cin >> password;

    if (!std::cin)
        exit(0);

    if (password != Menu::BUS_ADMIN_PASSWORD) {
        std::cout << "\tInvalid password, going back to main menu\n\n";
        return ADMIN_BACK;
    }

    std::cout << std::string(100, '\n');

    int option;

    std::cout << "\tHello administrator, what would you like to do?\n\n";
    std::cout << "\t[1] Back\n\n";
    std::cout << "\t> ";
    std::cin >> option;

    if (!std::cin)
        exit(0);

    std::cout.flush();

    return option;
}

int Menu::showClientMenu() {

    int option;

    std::cout << "\tHello client, what would you like to do?\n\n";
    std::cout << "\t[1] List all stops\n\t[2] List lines (and check a line)\n\t[3] Find the shortest path for your travel\n\t[4] Find the shortest path for your travel (coordinates)\n\t[5] Find the path with less stops for your travel\n\t[6] Find the path with less stops for your travel (coordinates)\n\t[7] Find the cheapest path (less zones) for your travel\n\t[8] Find the cheapest path (less zones) for your travel (coordinates)\n\t[9] Set your max walking distance\n\t[10] Back\n\n";
    std::cout << "\t> ";
    std::cin >> option;

    if (!std::cin)
        exit(0);

    std::cout.flush();

    return option;
}

int Menu::showInitialMenu(const std::string& busCompany) {

    int option;

    std::cout << "\t\tWelcome to " << busCompany << "\n\n";
    std::cout << "\t[1] Client\n\t[2] Admin\n\t[3] Exit\n\n";
    std::cout << "\t> ";
    std::cin >> option;

    if (!std::cin)
        exit(0);

    std::cout.flush();

    return option;
}

void Menu::waitForPrompt(const std::string &prompt) {
    std::cout << prompt << std::endl;
    std::cin.get();
    if (std::cin.peek() == '\n') std::cin.ignore(100, '\n'); // 100 chars should be enough to ignore
}

void Menu::endProgram() {
    Menu::waitForPrompt("\tProgram terminated, see you soon :) [press ENTER to quit]");
}

void Menu::listStops(BusCompany & busCompany) {
    busCompany.listStops(); // generate the call in menu, delegate it to BusCompany
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::travelMinDistance(BusCompany & busCompany) {
    busCompany.travelMinDistance(); // generate the call in menu, delegate it to BusCompany
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::travelMinDistanceCoord(BusCompany & busCompany) {
    busCompany.travelMinDistanceCoord(); // generate the call in menu, delegate it to BusCompany
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::travelMinStops(BusCompany & busCompany) {
    busCompany.travelMinStops(); // generate the call in menu, delegate it to BusCompany
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::travelMinStopsCoord(BusCompany & busCompany) {
    busCompany.travelMinStopsCoord(); // generate the call in menu, delegate it to BusCompany
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::travelMinZones(BusCompany &busCompany) {
    busCompany.travelMinZones(); // generate the call in menu, delegate it to BusCompany
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::travelMinZonesCoord(BusCompany &busCompany) {
    busCompany.travelMinZonesCoord(); // generate the call in menu, delegate it to BusCompany
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::changeWalkingDistance(BusCompany &busCompany) {
    busCompany.changeWalkingDistance(); // generate the call in menu, delegate it to BusCompany
    Menu::waitForPrompt("\t[press ENTER to continue]");
}



