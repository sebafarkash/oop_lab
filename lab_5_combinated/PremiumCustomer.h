#pragma once
#include "Customer.h"

// Преміум покупець — має підписку (Is-A Customer)
class PremiumCustomer final : public Customer {
private:
    double subscriptionFee;
    int bonusPoints;

public:
    PremiumCustomer(int id, const std::string& name,
                    const std::string& email, double balance,
                    double subscriptionFee = 9.99);
    PremiumCustomer(const PremiumCustomer& other);
    PremiumCustomer(PremiumCustomer&& other) noexcept;
    ~PremiumCustomer();

    double getSubscriptionFee() const;
    int    getBonusPoints()     const;
    void   addBonusPoints(int points);
    double getDiscount()        const;

    void display()        const override;
    std::string getInfo() const override;
    double getValue()     const override;
};
