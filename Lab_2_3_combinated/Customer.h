#pragma once
#include <string>
#include <iostream>

class Customer {
private:
    std::string name;
    std::string email;
    double balance;
    static int customerCount;

public:
    Customer(const std::string& name = "Guest",
             const std::string& email = "none@email.com",
             double balance = 0.0);
    Customer(const std::string& name, double balance);
    Customer(const Customer& other);
    Customer(Customer&& other) noexcept;
    ~Customer();

    std::string getName()    const;
    double      getBalance() const;

    Customer& topUp(double amount);

    void display()                  const;
    bool canAfford(double amount)   const;
    static int getCustomerCount();

    Customer  operator+(const Customer& other) const;
    Customer& operator-=(double amount);

    friend std::ostream& operator<<(std::ostream& os, const Customer& c);
    friend std::istream& operator>>(std::istream& is, Customer& c);
};
