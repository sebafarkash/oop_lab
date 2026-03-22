#include "PhysicalProduct.h"
#include <utility>

PhysicalProduct::PhysicalProduct(int id, const std::string& name, double price,
                                 int stock, double weight, const std::string& dimensions)
    : Product(id, name, price, stock), weight(weight), dimensions(dimensions) {
    std::cout << "[PhysicalProduct] Created: " << name << "\n";
}

PhysicalProduct::PhysicalProduct(const PhysicalProduct& other)
    : Product(other), weight(other.weight), dimensions(other.dimensions) {
    std::cout << "[PhysicalProduct] Copy ctor\n";
}

PhysicalProduct::PhysicalProduct(PhysicalProduct&& other) noexcept
    : Product(std::move(other)), weight(other.weight),
      dimensions(std::move(other.dimensions)) {
    other.weight = 0;
    std::cout << "[PhysicalProduct] Move ctor\n";
}

PhysicalProduct::~PhysicalProduct() {
    std::cout << "[PhysicalProduct] Destroyed: " << name << "\n";
}

double PhysicalProduct::getWeight() const { return weight; }
double PhysicalProduct::getShippingCost() const { return weight * 2.5; }
double PhysicalProduct::getValue() const { return price * stock - getShippingCost(); }

void PhysicalProduct::display() const {
    std::cout << "PhysicalProduct #" << id << ": " << name
              << " | $" << price << " | stock: " << stock
              << " | weight: " << weight << "kg"
              << " | shipping: $" << getShippingCost() << "\n";
}

std::string PhysicalProduct::getInfo() const {
    return "PhysicalProduct: " + name + " " + dimensions;
}

PhysicalProduct& PhysicalProduct::operator=(const PhysicalProduct& other) {
    if (this != &other) {
        Product::operator=(other);
        weight = other.weight;
        dimensions = other.dimensions;
        std::cout << "[PhysicalProduct] operator=\n";
    }
    return *this;
}
