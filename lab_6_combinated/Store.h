#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Product.h"
#include "Order.h"
#include "FileManager.h"

class Store {
private:
    std::vector<Product> products;
    std::vector<Order>   orders;
    FileManager          fileManager;
    int                  nextProductId;
    int                  nextOrderId;

    std::string getCurrentTime() const;

public:
    Store();

    // Адмін функції
    void addProduct(const std::string& name, double price, int stock);
    void removeProduct(int id);
    void updateProduct(int id, double newPrice, int newStock);
    void showAllOrders() const;

    // Юзер функції
    void showProducts() const;
    void buyProduct(const std::string& customerName, int productId, int qty);
    void showUserHistory(const std::string& customerName) const;

    // Загальні
    Product& findProduct(int id);
    void save();
};
