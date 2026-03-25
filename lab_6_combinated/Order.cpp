#include <vector>
#include "Order.h"
#include "Exceptions.h"
#include <sstream>
#include <iomanip>

Order::Order(int orderId, const std::string& customerName,
             const std::string& productName, int quantity,
             double totalPrice, const std::string& date)
    : orderId(orderId), customerName(customerName), productName(productName),
      quantity(quantity), totalPrice(totalPrice), date(date) {}

std::string Order::getCustomerName() const { return customerName; }
int Order::getOrderId() const { return orderId; }

void Order::display() const {
    std::cout << "Order #" << orderId
              << " | " << customerName
              << " | " << productName
              << " x" << quantity
              << " | $" << std::fixed << std::setprecision(2) << totalPrice
              << " | " << date << "\n";
}

std::string Order::serialize() const {
    return std::to_string(orderId) + "|" + customerName + "|" +
           productName + "|" + std::to_string(quantity) + "|" +
           std::to_string(totalPrice) + "|" + date;
}

Order Order::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(ss, token, '|')) tokens.push_back(token);
    if (tokens.size() < 6) throw StoreException("Invalid order data");
    return Order(std::stoi(tokens[0]), tokens[1], tokens[2],
                 std::stoi(tokens[3]), std::stod(tokens[4]), tokens[5]);
}
