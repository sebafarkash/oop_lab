#include "FileManager.h"
#include "Exceptions.h"
#include <fstream>
#include <iostream>
#include <direct.h>

FileManager::FileManager(const std::string& dir) {
    mkdir(dir.c_str());
    productsFile = dir + "/products.txt";
    ordersFile   = dir + "/orders.txt";
    historyFile  = dir + "/history.txt";
}

void FileManager::saveProducts(const std::vector<Product>& products) {
    std::ofstream file(productsFile);
    if (!file.is_open()) throw FileException(productsFile);
    for (const auto& p : products)
        file << p.serialize() << "\n";
}

std::vector<Product> FileManager::loadProducts() {
    std::vector<Product> products;
    std::ifstream file(productsFile);
    if (!file.is_open()) return products;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        try {
            products.push_back(Product::deserialize(line));
        } catch (...) {
            std::cerr << "Skipping invalid product line\n";
        }
    }
    return products;
}

void FileManager::saveOrder(const Order& order) {
    std::ofstream file(ordersFile, std::ios::app);
    if (!file.is_open()) throw FileException(ordersFile);
    file << order.serialize() << "\n";
}

std::vector<Order> FileManager::loadOrders() {
    std::vector<Order> orders;
    std::ifstream file(ordersFile);
    if (!file.is_open()) return orders;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        try {
            orders.push_back(Order::deserialize(line));
        } catch (...) {
            std::cerr << "Skipping invalid order line\n";
        }
    }
    return orders;
}

void FileManager::saveHistory(const std::string& entry) {
    std::ofstream file(historyFile, std::ios::app);
    if (!file.is_open()) throw FileException(historyFile);
    file << entry << "\n";
}

std::vector<std::string> FileManager::loadHistory() {
    std::vector<std::string> history;
    std::ifstream file(historyFile);
    if (!file.is_open()) return history;
    std::string line;
    while (std::getline(file, line))
        if (!line.empty()) history.push_back(line);
    return history;
}
