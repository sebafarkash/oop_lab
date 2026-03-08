#include "Product.h"
#include "Customer.h"
#include "Order.h"

int main() {
    // Product
    Product p1("Laptop", 999.99, 10);
    Product p2("Mouse", 29.99, true);
    Product p3;
    p3.setName("Keyboard").setPrice(59.99);
    p3.setStock(25);

    Product p4(p1);
    Product p5(std::move(p2));

    ++p1; p1++;
    --p3;
    std::cout << p1 << "\n" << p3 << "\n";
    std::cout << "p3 < p1: " << (p3 < p1 ? "Yes" : "No") << "\n";
    std::cout << "Products: " << Product::getProductCount() << "\n\n";

    const Product cProduct("Monitor", 299.99, 5);
    cProduct.display();

    // Customer
    Customer c1("Alice", "alice@mail.com", 500.0);
    Customer c2("Bob", 200.0);
    c2.topUp(50.0).topUp(30.0);

    Customer c3(c1);
    Customer c4(std::move(c2));

    Customer merged = c1 + c3;
    c1 -= 100.0;
    std::cout << merged << "\n" << c1 << "\n";
    std::cout << "Customers: " << Customer::getCustomerCount() << "\n\n";

    const Customer cCustomer("Eve", "eve@mail.com", 1000.0);
    cCustomer.display();

    // Order
    Order o1(1, p1, c1, 2);
    Order o2(p3, cCustomer, 3);

    Order o3(o1);
    Order o4(std::move(o1));

    o2.confirm();
    o3.cancel();

    std::cout << "!o3 cancelled: " << (!o3 ? "Yes" : "No") << "\n";
    std::cout << "o2 == o2: "      << (o2 == o2 ? "Yes" : "No") << "\n";
    std::cout << o2 << "\n";
    std::cout << "Orders: " << Order::getOrderCount() << "\n";

    return 0;
}
