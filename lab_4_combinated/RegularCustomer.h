#pragma once
#include "Customer.h"

// Звичайний покупець (Is-A Customer)
class RegularCustomer : public Customer {
private:
    int ordersCount;

public:
    RegularCustomer(int id, const std::string& name,
                    const std::string& email, double balance);
    RegularCustomer(const RegularCustomer& other);
    RegularCustomer(RegularCustomer&& other) noexcept;
    ~RegularCustomer();

    int getOrdersCount() const;
    void addOrder();
    double getDiscount() const;

    void display()        const override;
    std::string getInfo() const override;
    double getValue()     const override;
};
