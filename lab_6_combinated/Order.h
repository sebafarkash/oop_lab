#pragma once
#include <string>
#include <iostream>

class Order {
private:
    int orderId;
    std::string customerName;
    std::string productName;
    int quantity;
    double totalPrice;
    std::string date;

public:
    Order(int orderId, const std::string& customerName,
          const std::string& productName, int quantity,
          double totalPrice, const std::string& date);

    void display() const;
    std::string serialize() const;
    static Order deserialize(const std::string& line);

    std::string getCustomerName() const;
    int getOrderId() const;
};
