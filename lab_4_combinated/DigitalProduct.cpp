#include "DigitalProduct.h"
#include <utility>

DigitalProduct::DigitalProduct(int id, const std::string& name, double price,
                               double fileSizeMB, const std::string& licenseKey)
    : Product(id, name, price, 999), fileSizeMB(fileSizeMB), licenseKey(licenseKey) {
    std::cout << "[DigitalProduct] Created: " << name << "\n";
}

DigitalProduct::DigitalProduct(const DigitalProduct& other)
    : Product(other), fileSizeMB(other.fileSizeMB), licenseKey(other.licenseKey) {
    std::cout << "[DigitalProduct] Copy ctor\n";
}

DigitalProduct::DigitalProduct(DigitalProduct&& other) noexcept
    : Product(std::move(other)), fileSizeMB(other.fileSizeMB),
      licenseKey(std::move(other.licenseKey)) {
    other.fileSizeMB = 0;
    std::cout << "[DigitalProduct] Move ctor\n";
}

DigitalProduct::~DigitalProduct() {
    std::cout << "[DigitalProduct] Destroyed: " << name << "\n";
}

double DigitalProduct::getFileSizeMB()   const { return fileSizeMB; }
std::string DigitalProduct::getLicense() const { return licenseKey; }
double DigitalProduct::getValue()        const { return price * 0.9; } // знижка 10%

void DigitalProduct::display() const {
    std::cout << "DigitalProduct #" << id << ": " << name
              << " | $" << price << " | " << fileSizeMB << "MB"
              << " | license: " << licenseKey << "\n";
}

std::string DigitalProduct::getInfo() const {
    return "DigitalProduct: " + name + " (" + toStr(fileSizeMB) + "MB)";
}
