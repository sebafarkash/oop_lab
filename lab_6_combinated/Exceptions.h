#pragma once
#include <stdexcept>
#include <string>

class StoreException : public std::runtime_error {
public:
    explicit StoreException(const std::string& msg) : std::runtime_error(msg) {}
};

class ProductNotFoundException : public StoreException {
public:
    explicit ProductNotFoundException(const std::string& name)
        : StoreException("Product not found: " + name) {}
};

class InsufficientStockException : public StoreException {
public:
    explicit InsufficientStockException(const std::string& name, int available)
        : StoreException("Insufficient stock for: " + name + ". Available: " + std::to_string(available)) {}
};

class InsufficientFundsException : public StoreException {
public:
    explicit InsufficientFundsException(double required, double available)
        : StoreException("Insufficient funds. Required: $" + std::to_string(required) + ", Available: $" + std::to_string(available)) {}
};

class InvalidPasswordException : public StoreException {
public:
    explicit InvalidPasswordException()
        : StoreException("Invalid password!") {}
};

class FileException : public StoreException {
public:
    explicit FileException(const std::string& filename)
        : StoreException("File error: " + filename) {}
};
