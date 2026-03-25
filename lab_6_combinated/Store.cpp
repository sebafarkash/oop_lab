#include "Store.h"
#include "Exceptions.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>

Store::Store() : fileManager("data"), nextProductId(1), nextOrderId(1) {
    products = fileManager.loadProducts();
    orders   = fileManager.loadOrders();
    // Визначити наступні ID
    for (const auto& p : products)
        if (p.getId() >= nextProductId) nextProductId = p.getId() + 1;
    for (const auto& o : orders)
        if (o.getOrderId() >= nextOrderId) nextOrderId = o.getOrderId() + 1;
}

std::string Store::getCurrentTime() const {
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::localtime(&t);
    std::ostringstream ss;
    ss << std::put_time(tm, "%Y-%m-%d %H:%M");
    return ss.str();
}

void Store::addProduct(const std::string& name, double price, int stock) {
    if (name.empty()) throw StoreException("Product name cannot be empty");
    if (price < 0)    throw StoreException("Price cannot be negative");
    if (stock < 0)    throw StoreException("Stock cannot be negative");
    products.emplace_back(nextProductId++, name, price, stock);
    save();
    fileManager.saveHistory("[ADMIN] Added product: " + name + " at " + getCurrentTime());
    std::cout << "Product added successfully!\n";
}

void Store::removeProduct(int id) {
    auto it = std::find_if(products.begin(), products.end(),
        [id](const Product& p) { return p.getId() == id; });
    if (it == products.end()) throw ProductNotFoundException(std::to_string(id));
    std::string name = it->getName();
    products.erase(it);
    save();
    fileManager.saveHistory("[ADMIN] Removed product: " + name + " at " + getCurrentTime());
    std::cout << "Product removed!\n";
}

void Store::updateProduct(int id, double newPrice, int newStock) {
    Product& p = findProduct(id);
    p.setPrice(newPrice);
    p.setStock(newStock);
    save();
    fileManager.saveHistory("[ADMIN] Updated product: " + p.getName() + " at " + getCurrentTime());
    std::cout << "Product updated!\n";
}

void Store::showAllOrders() const {
    if (orders.empty()) { std::cout << "No orders yet.\n"; return; }
    for (const auto& o : orders) o.display();
}

void Store::showProducts() const {
    if (products.empty()) { std::cout << "No products available.\n"; return; }
    std::cout << "\n=== Available Products ===\n";
    for (const auto& p : products) p.display();
}

void Store::buyProduct(const std::string& customerName, int productId, int qty) {
    if (qty <= 0) throw StoreException("Quantity must be positive");
    Product& p = findProduct(productId);
    p.decreaseStock(qty); // може кинути InsufficientStockException
    double total = p.getPrice() * qty;
    Order order(nextOrderId++, customerName, p.getName(), qty, total, getCurrentTime());
    orders.push_back(order);
    fileManager.saveOrder(order);
    save();
    fileManager.saveHistory("[USER] " + customerName + " bought " + p.getName() +
                            " x" + std::to_string(qty) + " at " + getCurrentTime());
    std::cout << "Purchase successful! Total: $" << std::fixed << std::setprecision(2) << total << "\n";
}

void Store::showUserHistory(const std::string& customerName) const {
    bool found = false;
    std::cout << "\n=== Your Purchase History ===\n";
    for (const auto& o : orders) {
        if (o.getCustomerName() == customerName) {
            o.display();
            found = true;
        }
    }
    if (!found) std::cout << "No purchases yet.\n";
}

Product& Store::findProduct(int id) {
    auto it = std::find_if(products.begin(), products.end(),
        [id](const Product& p) { return p.getId() == id; });
    if (it == products.end()) throw ProductNotFoundException(std::to_string(id));
    return *it;
}

void Store::save() {
    fileManager.saveProducts(products);
}
