#include "RegularCustomer.h"

RegularCustomer::RegularCustomer(int id, const std::string& name,
                                 const std::string& email, double balance)
    : Customer(id, name, email, balance), ordersCount(0) {
    std::cout << "[RegularCustomer] Created: " << name << "\n";
}

RegularCustomer::RegularCustomer(const RegularCustomer& other)
    : Customer(other), ordersCount(other.ordersCount) {
    std::cout << "[RegularCustomer] Copy ctor\n";
}

RegularCustomer::RegularCustomer(RegularCustomer&& other) noexcept
    : Customer(std::move(other)), ordersCount(other.ordersCount) {
    other.ordersCount = 0;
    std::cout << "[RegularCustomer] Move ctor\n";
}

RegularCustomer::~RegularCustomer() {
    std::cout << "[RegularCustomer] Destroyed: " << name << "\n";
}

int    RegularCustomer::getOrdersCount() const { return ordersCount; }
void   RegularCustomer::addOrder()             { ++ordersCount; }
double RegularCustomer::getDiscount()    const { return ordersCount > 5 ? 0.05 : 0.0; }
double RegularCustomer::getValue()       const { return balance; }

void RegularCustomer::display() const {
    std::cout << "RegularCustomer #" << id << ": " << name
              << " | $" << balance
              << " | orders: " << ordersCount
              << " | discount: " << getDiscount() * 100 << "%\n";
}

std::string RegularCustomer::getInfo() const {
    return "RegularCustomer: " + name + " orders: " + toStr(ordersCount);
}
