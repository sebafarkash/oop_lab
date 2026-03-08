#include "Order.h"
#include <utility>

int Order::orderCount = 0;

Order::Order(int id, const Product& p, const Customer& c, int qty)
    : orderId(id), product(p), customer(c), quantity(qty), status(Status::PENDING) {
    ++orderCount;
}

Order::Order(const Product& p, const Customer& c, int qty)
    : Order(orderCount + 1, p, c, qty) {}

Order::Order(const Order& other)
    : orderId(other.orderId), product(other.product), customer(other.customer),
      quantity(other.quantity), status(other.status) {
    ++orderCount;
}

Order::Order(Order&& other) noexcept
    : orderId(other.orderId), product(std::move(other.product)),
      customer(std::move(other.customer)), quantity(other.quantity), status(other.status) {
    other.orderId = -1; other.quantity = 0;
    ++orderCount;
}

Order::~Order() { --orderCount; }

double Order::totalPrice() const { return product.getPrice() * quantity; }

void Order::display() const {
    std::string s[] = {"PENDING", "CONFIRMED", "CANCELLED"};
    std::cout << "Order #" << orderId << " | " << product.getName()
              << " x" << quantity << " | $" << totalPrice()
              << " | " << customer.getName() << " | " << s[(int)status] << "\n";
}

Order& Order::confirm() { this->status = Status::CONFIRMED; return *this; }
Order& Order::cancel()  { this->status = Status::CANCELLED; return *this; }

int  Order::getOrderCount()                    { return orderCount; }
bool Order::operator==(const Order& o)  const  { return orderId == o.orderId; }
bool Order::operator!()                 const  { return status == Status::CANCELLED; }

std::ostream& operator<<(std::ostream& os, const Order& o) {
    return os << "[Order #" << o.orderId << ", " << o.product.getName()
              << " x" << o.quantity << ", $" << o.totalPrice() << "]";
}
std::istream& operator>>(std::istream& is, Order& o) {
    std::cout << "Order ID: "; is >> o.orderId;
    std::cout << "Quantity: "; is >> o.quantity;
    return is;
}
