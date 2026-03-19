#pragma once
#include "Entity.h"

class Customer : public Entity {
protected:
    std::string name;
    std::string email;
    double balance;
    static int customerCount;

public:
    Customer(int id, const std::string& name,
             const std::string& email = "none@email.com",
             double balance = 0.0);
    Customer(const Customer& other);
    Customer(Customer&& other) noexcept;
    virtual ~Customer();

    std::string getName()    const;
    std::string getEmail()   const;
    double      getBalance() const;

    Customer& topUp(double amount);
    bool canAfford(double amount) const;

    static int getCustomerCount();

    void display()        const override;
    std::string getInfo() const override;
    double getValue()     const override;

    Customer  operator+(const Customer& other) const;
    Customer& operator-=(double amount);

    friend std::ostream& operator<<(std::ostream& os, const Customer& c);
    friend std::istream& operator>>(std::istream& is, Customer& c);
};
