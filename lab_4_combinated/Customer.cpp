#include "Customer.h"
#include <utility>

int Customer::customerCount = 0;

Customer::Customer(int id, const std::string& name,
                   const std::string& email, double balance)
    : Entity(id), name(name), email(email), balance(balance) {
    ++customerCount;
    std::cout << "[Customer] Created: " << name << "\n";
}

Customer::Customer(const Customer& other)
    : Entity(other), name(other.name), email(other.email), balance(other.balance) {
    ++customerCount;
    std::cout << "[Customer] Copy ctor: " << name << "\n";
}

Customer::Customer(Customer&& other) noexcept
    : Entity(std::move(other)), name(std::move(other.name)),
      email(std::move(other.email)), balance(other.balance) {
    other.balance = 0;
    ++customerCount;
    std::cout << "[Customer] Move ctor\n";
}

Customer::~Customer() {
    --customerCount;
    std::cout << "[Customer] Destroyed: " << name << "\n";
}

std::string Customer::getName()    const { return name; }
std::string Customer::getEmail()   const { return email; }
double      Customer::getBalance() const { return balance; }
double      Customer::getValue()   const { return balance; }

Customer& Customer::topUp(double amount) { this->balance += amount; return *this; }
bool Customer::canAfford(double amount)  const { return balance >= amount; }
int  Customer::getCustomerCount()              { return customerCount; }

void Customer::display() const {
    std::cout << "Customer #" << id << ": " << name
              << " | " << email << " | $" << balance << "\n";
}

std::string Customer::getInfo() const {
    return "Customer: " + name + " $" + toStr(balance);
}

Customer Customer::operator+(const Customer& o) const {
    return Customer(id, name + "&" + o.name, email, balance + o.balance);
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
