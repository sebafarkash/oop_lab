#pragma once
#include "Store.h"
#include <string>

class Menu {
private:
    Store store;
    const std::string ADMIN_PASSWORD = "admin123";

    void adminMenu();
    void userMenu();
    bool loginAdmin();
    std::string getUsername();

public:
    void run();
};
