#pragma once
#include <string>
#include <iostream>

class Product {
private:
    std::string name;
    double price;
    int stock;
    static int productCount;

public:
    Product(const std::string& name = "Unknown", double price = 0.0, int stock = 0);
    Product(const std::string& name, double price, bool inStock);
    Product(const Product& other);
    Product(Product&& other) noexcept;
    ~Product();

    std::string getName()  const;
    double      getPrice() const;
    int         getStock() const;
    void        setStock(int s);

    Product& setName(const std::string& n);
    Product& setPrice(double p);

    void display()            const;
    bool isAvailable()        const;
    static int getProductCount();

    Product& operator++();
    Product  operator++(int);
    Product& operator--();
    bool operator<(const Product& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Product& p);
    friend std::istream& operator>>(std::istream& is, Product& p);
};
