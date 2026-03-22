#pragma once
#include "Entity.h"

class Product : public Entity {
protected:
    std::string name;
    double price;
    int stock;
    static int productCount;

public:
    Product(int id, const std::string& name, double price, int stock = 0);
    Product(const Product& other);
    Product(Product&& other) noexcept;
    Product& operator=(const Product& other);
    virtual ~Product();

    std::string getName()  const;
    double      getPrice() const;
    int         getStock() const;
    void        setStock(int s);

    Product& setName(const std::string& n);
    Product& setPrice(double p);

    bool isAvailable() const;
    static int getProductCount();

    // Override віртуальних методів Entity
    void display()            const override;
    std::string getInfo()     const override;
    double getValue()         const override;

    Product& operator++();
    Product  operator++(int);
    Product& operator--();
    bool operator<(const Product& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Product& p);
    friend std::istream& operator>>(std::istream& is, Product& p);
};
