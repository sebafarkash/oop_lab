#include <vector>
#include "Product.h"
#include "Exceptions.h"
#include <sstream>
#include <iomanip>

Product::Product(int id, const std::string& name, double price, int stock)
    : id(id), name(name), price(price), stock(stock) {}

int         Product::getId()    const { return id; }
std::string Product::getName()  const { return name; }
double      Product::getPrice() const { return price; }
int         Product::getStock() const { return stock; }

void Product::setName(const std::string& n)  { name = n; }
void Product::setPrice(double p)             { price = p; }
void Product::setStock(int s)                { stock = s; }

void Product::decreaseStock(int qty) {
    if (qty > stock)
        throw InsufficientStockException(name, stock);
    stock -= qty;
}

void Product::display() const {
    std::cout << "[" << id << "] " << name
              << " | $" << std::fixed << std::setprecision(2) << price
              << " | stock: " << stock << "\n";
}

std::string Product::serialize() const {
    return std::to_string(id) + "|" + name + "|" +
           std::to_string(price) + "|" + std::to_string(stock);
}

Product Product::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(ss, token, '|')) tokens.push_back(token);
    if (tokens.size() < 4) throw StoreException("Invalid product data");
    return Product(std::stoi(tokens[0]), tokens[1],
                   std::stod(tokens[2]), std::stoi(tokens[3]));
}
