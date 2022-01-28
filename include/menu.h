#ifndef PROJECT2_MENU_H
#define PROJECT2_MENU_H

#include <iostream>
#include "busCompany.h"

class Menu {

    static std::string BUS_ADMIN_PASSWORD;

    static bool exitApplication;

    enum MainMenuOption {
        CLIENT = 1,
        ADMIN,
        LEAVE
    };

    enum AdminMenuOption {
        ADMIN_BACK = 1
    };

    enum ClientMenuOption {
        CLIENT_LIST_ALL_STOPS = 1,
        CLIENT_TRAVEL_DISTANCE,
        CLIENT_TRAVEL_STOPS,
        CLIENT_WALKING,
        CLIENT_BACK
    };

    /**
     * Waits for user input (new line) to progress
     * @param prompt
     */
    static void waitForPrompt(const std::string& prompt);

public:
    /**
     * Initialize the program
     */
    static void init();

    /**
     * Shows the initial menu on screen
     * @param busCompanyName Name of the bus company we are travelling with (displayed on screen)
     * @return User option (Client/Admin/EXit)
     */
    static int showInitialMenu(const std::string& busCompanyName);
    /**
     * Shows the administrator menu on screen
     * @return User option (from the admin functionalities available)
     */
    static int showAdminMenu();
    /**
     * Shows the administrator menu on screen
     * @return User option (from the client functionalities available)
     */
    static int showClientMenu();

    /**
     * Close the program
     */
    static void endProgram();

    static void listStops(BusCompany & busCompany);
    static void travelMinDistance(BusCompany & busCompany);
    static void travelMinStops(BusCompany & busCompany);
    static void changeWalkingDistance(BusCompany & busCompany);
};

#endif //PROJECT2_MENU_H
