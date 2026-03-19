#include "PremiumCustomer.h"

PremiumCustomer::PremiumCustomer(int id, const std::string& name,
                                 const std::string& email, double balance,
                                 double subscriptionFee)
    : Customer(id, name, email, balance),
      subscriptionFee(subscriptionFee), bonusPoints(0) {
    std::cout << "[PremiumCustomer] Created: " << name << "\n";
}

PremiumCustomer::PremiumCustomer(const PremiumCustomer& other)
    : Customer(other), subscriptionFee(other.subscriptionFee),
      bonusPoints(other.bonusPoints) {
    std::cout << "[PremiumCustomer] Copy ctor\n";
}

PremiumCustomer::PremiumCustomer(PremiumCustomer&& other) noexcept
    : Customer(std::move(other)), subscriptionFee(other.subscriptionFee),
      bonusPoints(other.bonusPoints) {
    other.subscriptionFee = 0;
    other.bonusPoints = 0;
    std::cout << "[PremiumCustomer] Move ctor\n";
}

PremiumCustomer::~PremiumCustomer() {
    std::cout << "[PremiumCustomer] Destroyed: " << name << "\n";
}

double PremiumCustomer::getSubscriptionFee() const { return subscriptionFee; }
int    PremiumCustomer::getBonusPoints()     const { return bonusPoints; }
void   PremiumCustomer::addBonusPoints(int p)      { bonusPoints += p; }
double PremiumCustomer::getDiscount()        const { return 0.15; }
double PremiumCustomer::getValue()           const { return balance + bonusPoints * 0.1; }

void PremiumCustomer::display() const {
    std::cout << "PremiumCustomer #" << id << ": " << name
              << " | $" << balance
              << " | bonus: " << bonusPoints
              << " | discount: " << getDiscount() * 100 << "%\n";
}

std::string PremiumCustomer::getInfo() const {
    return "PremiumCustomer: " + name + " bonus: " + toStr(bonusPoints);
}
