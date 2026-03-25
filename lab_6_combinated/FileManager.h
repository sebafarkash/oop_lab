#pragma once
#include <string>
#include <vector>
#include "Product.h"
#include "Order.h"

class FileManager {
private:
    std::string productsFile;
    std::string ordersFile;
    std::string historyFile;

public:
    FileManager(const std::string& dir = "data");

    void saveProducts(const std::vector<Product>& products);
    std::vector<Product> loadProducts();

    void saveOrder(const Order& order);
    std::vector<Order> loadOrders();

    void saveHistory(const std::string& entry);
    std::vector<std::string> loadHistory();
};
