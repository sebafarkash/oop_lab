#include "Customer.h"
#include <utility>

int Customer::customerCount = 0;

Customer::Customer(const std::string& name, const std::string& email, double balance)
    : name(name), email(email), balance(balance) {
    ++customerCount;
}

Customer::Customer(const std::string& name, double balance)
    : Customer(name, "none@email.com", balance) {}

Customer::Customer(const Customer& other)
    : name(other.name), email(other.email), balance(other.balance) {
    ++customerCount;
}

Customer::Customer(Customer&& other) noexcept
    : name(std::move(other.name)), email(std::move(other.email)), balance(other.balance) {
    other.balance = 0;
    ++customerCount;
}

Customer::~Customer() { --customerCount; }

std::string Customer::getName()    const { return name; }
double      Customer::getBalance() const { return balance; }

Customer& Customer::topUp(double amount) { this->balance += amount; return *this; }

void Customer::display() const {
    std::cout << "Customer: " << name << " | " << email << " | $" << balance << "\n";
}
bool Customer::canAfford(double amount) const { return balance >= amount; }
int  Customer::getCustomerCount()             { return customerCount; }

Customer Customer::operator+(const Customer& o) const {
    return Customer(name + "&" + o.name, email, balance + o.balance);
}
Customer& Customer::operator-=(double amount) {
    if (balance >= amount) balance -= amount;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Customer& c) {
    return os << "[" << c.name << ", " << c.email << ", $" << c.balance << "]";
}
std::istream& operator>>(std::istream& is, Customer& c) {
    std::cout << "Name: ";    is >> c.name;
    std::cout << "Email: ";   is >> c.email;
    std::cout << "Balance: "; is >> c.balance;
    return is;
}
