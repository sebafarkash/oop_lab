#include "Menu.h"
#include "Exceptions.h"
#include <iostream>
#include <limits>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool Menu::loginAdmin() {
    std::string password;
    std::cout << "Enter admin password: ";
    std::cin >> password;
    if (password != ADMIN_PASSWORD)
        throw InvalidPasswordException();
    return true;
}

std::string Menu::getUsername() {
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    return name;
}

void Menu::adminMenu() {
    int choice;
    do {
        std::cout << "\n=== ADMIN MENU ===\n"
                  << "1. Show all products\n"
                  << "2. Add product\n"
                  << "3. Remove product\n"
                  << "4. Update product\n"
                  << "5. Show all orders\n"
                  << "0. Logout\n"
                  << "Choice: ";
        std::cin >> choice;
        clearInput();

        try {
            if (choice == 1) {
                store.showProducts();
            } else if (choice == 2) {
                std::string name;
                double price;
                int stock;
                std::cout << "Product name: "; std::getline(std::cin, name);
                std::cout << "Price: ";        std::cin >> price;
                std::cout << "Stock: ";        std::cin >> stock;
                clearInput();
                store.addProduct(name, price, stock);
            } else if (choice == 3) {
                int id;
                store.showProducts();
                std::cout << "Enter product ID to remove: "; std::cin >> id;
                clearInput();
                store.removeProduct(id);
            } else if (choice == 4) {
                int id; double price; int stock;
                store.showProducts();
                std::cout << "Enter product ID: ";    std::cin >> id;
                std::cout << "New price: ";           std::cin >> price;
                std::cout << "New stock: ";           std::cin >> stock;
                clearInput();
                store.updateProduct(id, price, stock);
            } else if (choice == 5) {
                store.showAllOrders();
            }
        } catch (const StoreException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    } while (choice != 0);
}

void Menu::userMenu() {
    std::string username = getUsername();
    int choice;
    do {
        std::cout << "\n=== USER MENU [" << username << "] ===\n"
                  << "1. Show products\n"
                  << "2. Buy product\n"
                  << "3. My purchase history\n"
                  << "0. Logout\n"
                  << "Choice: ";
        std::cin >> choice;
        clearInput();

        try {
            if (choice == 1) {
                store.showProducts();
            } else if (choice == 2) {
                int id, qty;
                store.showProducts();
                std::cout << "Enter product ID: "; std::cin >> id;
                std::cout << "Quantity: ";          std::cin >> qty;
                clearInput();
                store.buyProduct(username, id, qty);
            } else if (choice == 3) {
                store.showUserHistory(username);
            }
        } catch (const StoreException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    } while (choice != 0);
}

void Menu::run() {
    int choice;
    do {
        std::cout << "\n=== ONLINE STORE ===\n"
                  << "1. Login as Admin\n"
                  << "2. Login as User\n"
                  << "0. Exit\n"
                  << "Choice: ";
        std::cin >> choice;
        clearInput();

        try {
            if (choice == 1) {
                if (loginAdmin()) adminMenu();
            } else if (choice == 2) {
                userMenu();
            }
        } catch (const InvalidPasswordException& e) {
            std::cout << "Error: " << e.what() << "\n";
        } catch (const StoreException& e) {
            std::cout << "Error: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "Unexpected error: " << e.what() << "\n";
        }
    } while (choice != 0);

    std::cout << "Goodbye!\n";
}
