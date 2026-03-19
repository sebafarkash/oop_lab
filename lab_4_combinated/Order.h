#pragma once
#include "Entity.h"
#include "Product.h"
#include "Customer.h"

// Order Has-A Product і Has-A Customer (композиція)
class Order : public Entity {
public:
    enum class Status { PENDING, CONFIRMED, CANCELLED };

private:
    Product  product;
    Customer customer;
    int      quantity;
    Status   status;
    static int orderCount;

public:
    Order(int id, const Product& p, const Customer& c, int qty = 1);
    Order(const Order& other);
    Order(Order&& other) noexcept;
    ~Order();

    double totalPrice() const;

    Order& confirm();
    Order& cancel();

    static int getOrderCount();

    void display()        const override;
    std::string getInfo() const override;
    double getValue()     const override;

    bool operator==(const Order& other) const;
    bool operator!()                    const;

    friend std::ostream& operator<<(std::ostream& os, const Order& o);
    friend std::istream& operator>>(std::istream& is, Order& o);
};
