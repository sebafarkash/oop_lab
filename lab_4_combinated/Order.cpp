#include "Order.h"
#include <utility>

int Order::orderCount = 0;

Order::Order(int id, const Product& p, const Customer& c, int qty)
    : Entity(id), product(p), customer(c), quantity(qty), status(Status::PENDING) {
    ++orderCount;
    std::cout << "[Order] Created #" << id << "\n";
}

Order::Order(const Order& other)
    : Entity(other), product(other.product), customer(other.customer),
      quantity(other.quantity), status(other.status) {
    ++orderCount;
    std::cout << "[Order] Copy ctor #" << id << "\n";
}

Order::Order(Order&& other) noexcept
    : Entity(std::move(other)), product(std::move(other.product)),
      customer(std::move(other.customer)), quantity(other.quantity), status(other.status) {
    other.quantity = 0;
    ++orderCount;
    std::cout << "[Order] Move ctor\n";
}

Order::~Order() {
    --orderCount;
    std::cout << "[Order] Destroyed #" << id << "\n";
}

double Order::totalPrice() const { return product.getPrice() * quantity; }
double Order::getValue()   const { return totalPrice(); }

Order& Order::confirm() { this->status = Status::CONFIRMED; return *this; }
Order& Order::cancel()  { this->status = Status::CANCELLED; return *this; }

int  Order::getOrderCount()               { return orderCount; }
bool Order::operator==(const Order& o) const { return id == o.id; }
bool Order::operator!()                const { return status == Status::CANCELLED; }

void Order::display() const {
    std::string s[] = {"PENDING", "CONFIRMED", "CANCELLED"};
    std::cout << "Order #" << id << " | " << product.getName()
              << " x" << quantity << " | $" << totalPrice()
              << " | " << customer.getName()
              << " | " << s[(int)status] << "\n";
}

std::string Order::getInfo() const {
    return "Order #" + toStr(id) + " $" + toStr(totalPrice());
}

std::ostream& operator<<(std::ostream& os, const Order& o) {
    return os << "[Order #" << o.id << ", " << o.product.getName()
              << " x" << o.quantity << ", $" << o.totalPrice() << "]";
}
std::istream& operator>>(std::istream& is, Order& o) {
    std::cout << "Quantity: "; is >> o.quantity;
    return is;
}
