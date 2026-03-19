#include <iostream>
#include "Product.h"
#include "PhysicalProduct.h"
#include "DigitalProduct.h"
#include "Customer.h"
#include "RegularCustomer.h"
#include "PremiumCustomer.h"
#include "Order.h"

int main() {
    std::cout << "\n===== LAB 4: Inheritance =====\n\n";

    // ── Ієрархія конструкторів ──
    std::cout << "--- Constructors hierarchy ---\n";
    PhysicalProduct laptop(1, "Laptop", 999.99, 10, 2.5, "30x20x2cm");
    DigitalProduct  vscode(2, "VSCode Pro", 49.99, 500.0, "KEY-1234");
    RegularCustomer alice(1, "Alice", "alice@mail.com", 500.0);
    PremiumCustomer bob(2, "Bob", "bob@mail.com", 1000.0);

    // ── Copy / Move конструктори (лаб 4, пункт 6) ──
    std::cout << "\n--- Copy & Move ---\n";
    PhysicalProduct laptopCopy(laptop);              // copy
    DigitalProduct  vscodeMoved(std::move(vscode));  // move

    // ── operator= (лаб 4, пункт 6) ──
    std::cout << "\n--- operator= ---\n";
    PhysicalProduct mouse(3, "Mouse", 29.99, 50, 0.1, "10x6x3cm");
    PhysicalProduct keyboard(4, "Keyboard", 59.99, 25, 0.5, "40x15x3cm");
    mouse = keyboard; // operator=
    mouse.display();

    // ── display кожного класу ──
    std::cout << "\n--- Display all ---\n";
    laptop.display();
    vscodeMoved.display();
    alice.display();
    bob.display();

    // ── RegularCustomer — знижка після 5 замовлень ──
    std::cout << "\n--- RegularCustomer orders ---\n";
    for (int i = 0; i < 6; i++) alice.addOrder();
    alice.display();
    std::cout << "Discount: " << alice.getDiscount() * 100 << "%\n";

    // ── PremiumCustomer — бонусні бали ──
    std::cout << "\n--- PremiumCustomer bonus ---\n";
    bob.addBonusPoints(150);
    bob.display();

    // ── Order — Has-A (композиція) ──
    std::cout << "\n--- Order (Has-A) ---\n";
    alice.topUp(500.0);
    Order o1(1, laptop, alice, 2);
    o1.confirm();
    o1.display();
    std::cout << o1 << "\n";

    // ── Static поля ──
    std::cout << "\n--- Static counts ---\n";
    std::cout << "Products: "  << Product::getProductCount()   << "\n";
    std::cout << "Customers: " << Customer::getCustomerCount() << "\n";
    std::cout << "Orders: "    << Order::getOrderCount()       << "\n";

    std::cout << "\n===== END =====\n\n";
    return 0;
}
