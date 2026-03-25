#pragma once
#include <string>
#include <iostream>

class Product {
private:
    int id;
    std::string name;
    double price;
    int stock;

public:
    Product(int id = 0, const std::string& name = "", double price = 0.0, int stock = 0);

    int         getId()    const;
    std::string getName()  const;
    double      getPrice() const;
    int         getStock() const;

    void setName(const std::string& name);
    void setPrice(double price);
    void setStock(int stock);
    void decreaseStock(int qty);

    void display() const;
    std::string serialize() const;
    static Product deserialize(const std::string& line);
};
