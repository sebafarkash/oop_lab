#include "Product.h"
#include <utility>

int Product::productCount = 0;

Product::Product(int id, const std::string& name, double price, int stock)
    : Entity(id), name(name), price(price), stock(stock) {
    ++productCount;
    std::cout << "[Product] Created: " << name << "\n";
}

Product::Product(const Product& other)
    : Entity(other), name(other.name), price(other.price), stock(other.stock) {
    ++productCount;
    std::cout << "[Product] Copy ctor: " << name << "\n";
}

Product::Product(Product&& other) noexcept
    : Entity(std::move(other)), name(std::move(other.name)),
      price(other.price), stock(other.stock) {
    other.price = 0; other.stock = 0;
    ++productCount;
    std::cout << "[Product] Move ctor\n";
}

Product::~Product() {
    --productCount;
    std::cout << "[Product] Destroyed: " << name << "\n";
}

std::string Product::getName()  const { return name; }
double      Product::getPrice() const { return price; }
int         Product::getStock() const { return stock; }
void        Product::setStock(int s)  { stock = s; }

Product& Product::setName(const std::string& n) { this->name = n; return *this; }
Product& Product::setPrice(double p)             { this->price = p; return *this; }

bool Product::isAvailable()     const { return stock > 0; }
int  Product::getProductCount()       { return productCount; }
double Product::getValue()      const { return price * stock; }

void Product::display() const {
    std::cout << "Product #" << id << ": " << name
              << " | $" << price << " | stock: " << stock << "\n";
}

std::string Product::getInfo() const {
    return "Product: " + name + " $" + toStr(price);
}

Product& Product::operator++()    { ++stock; return *this; }
Product  Product::operator++(int) { Product t(*this); ++stock; return t; }
Product& Product::operator--()    { if (stock > 0) --stock; return *this; }
bool Product::operator<(const Product& o) const { return price < o.price; }

std::ostream& operator<<(std::ostream& os, const Product& p) {
    return os << "[" << p.name << ", $" << p.price << ", stock: " << p.stock << "]";
}
std::istream& operator>>(std::istream& is, Product& p) {
    std::cout << "Name: ";  is >> p.name;
    std::cout << "Price: "; is >> p.price;
    std::cout << "Stock: "; is >> p.stock;
    return is;
}

Product& Product::operator=(const Product& other) {
    if (this != &other) {
        Entity::operator=(other);
        name = other.name;
        price = other.price;
        stock = other.stock;
    }
    return *this;
}
