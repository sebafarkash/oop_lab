#include "Product.h"
#include <utility>

int Product::productCount = 0;

Product::Product(const std::string& name, double price, int stock)
    : name(name), price(price), stock(stock) {
    ++productCount;
}

Product::Product(const std::string& name, double price, bool inStock)
    : Product(name, price, inStock ? 1 : 0) {}

Product::Product(const Product& other)
    : name(other.name), price(other.price), stock(other.stock) {
    ++productCount;
}

Product::Product(Product&& other) noexcept
    : name(std::move(other.name)), price(other.price), stock(other.stock) {
    other.price = 0; other.stock = 0;
    ++productCount;
}

Product::~Product() { --productCount; }

std::string Product::getName()  const { return name; }
double      Product::getPrice() const { return price; }
int         Product::getStock() const { return stock; }
void        Product::setStock(int s)  { stock = s; }

Product& Product::setName(const std::string& n) { this->name = n; return *this; }
Product& Product::setPrice(double p)             { this->price = p; return *this; }

void Product::display() const {
    std::cout << "Product: " << name << " | $" << price << " | stock: " << stock << "\n";
}
bool Product::isAvailable() const { return stock > 0; }
int  Product::getProductCount()   { return productCount; }

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
