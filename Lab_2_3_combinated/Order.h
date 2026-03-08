#pragma once
#include <iostream>
#include "Product.h"
#include "Customer.h"

class Order {
public:
    enum class Status { PENDING, CONFIRMED, CANCELLED };

private:
    int      orderId;
    Product  product;
    Customer customer;
    int      quantity;
    Status   status;
    static int orderCount;

public:
    Order(int id, const Product& p, const Customer& c, int qty = 1);
    Order(const Product& p, const Customer& c, int qty);
    Order(const Order& other);
    Order(Order&& other) noexcept;
    ~Order();

    double totalPrice() const;
    void   display()    const;

    Order& confirm();
    Order& cancel();

    static int getOrderCount();

    bool operator==(const Order& other) const;
    bool operator!()                    const;

    friend std::ostream& operator<<(std::ostream& os, const Order& o);
    friend std::istream& operator>>(std::istream& is, Order& o);
};
