#include <iostream>
#include <vector>
#include "IDisplayable.h"
#include "Entity.h"
#include "Product.h"
#include "PhysicalProduct.h"
#include "DigitalProduct.h"
#include "Customer.h"
#include "RegularCustomer.h"
#include "PremiumCustomer.h"
#include "Order.h"

// ╔══════════════════════════════════════════════════╗
// ║  Пункт 1: Проблема статичної прив'язки           ║
// ╚══════════════════════════════════════════════════╝
void staticBindingProblem(Product& p) {
    // Без virtual — завжди викликається Product::display()
    // навіть якщо передати PhysicalProduct чи DigitalProduct
    p.display();
}

// ╔══════════════════════════════════════════════════╗
// ║  Пункт 3: Динамічний поліморфізм — вказівник     ║
// ╚══════════════════════════════════════════════════╝
void showEntityPointer(Entity* e) {
    e->display();   // викликається правильний display() завдяки virtual
    std::cout << "Value: $" << e->getValue() << "\n";
}

// ╔══════════════════════════════════════════════════╗
// ║  Пункт 6: Динамічний поліморфізм — посилання     ║
// ╚══════════════════════════════════════════════════╝
void showEntityReference(const Entity& e) {
    e.display();    // теж динамічна прив'язка через посилання
    std::cout << "Info: " << e.getInfo() << "\n";
}

// ╔══════════════════════════════════════════════════╗
// ║  Пункт 8: Інтерфейс IDisplayable                 ║
// ╚══════════════════════════════════════════════════╝
void printDisplayable(const IDisplayable& obj) {
    obj.display();
    std::cout << "Info: " << obj.getInfo() << "\n";
}

int main() {
    std::cout << "\n===== LAB 5: Polymorphism =====\n\n";

    // ── Об'єкти ──
    PhysicalProduct laptop(1, "Laptop", 999.99, 10, 2.5, "30x20x2cm");
    DigitalProduct  vscode(2, "VSCode Pro", 49.99, 500.0, "KEY-1234");
    RegularCustomer alice(1, "Alice", "alice@mail.com", 500.0);
    PremiumCustomer bob(2, "Bob", "bob@mail.com", 1000.0);

    // ╔══════════════════════════════════════════════════╗
    // ║  Пункт 1: Static binding — проблема             ║
    // ╚══════════════════════════════════════════════════╝
    std::cout << "\n--- 1. Static Binding (проблема) ---\n";
    std::cout << "Передаємо PhysicalProduct як Product&:\n";
    staticBindingProblem(laptop);
    // Якби display() не була virtual — завжди б виводило Product::display()
    // Але оскільки вона virtual — виводить PhysicalProduct::display()
    // Щоб показати СПРАВЖНЮ проблему статичної прив'язки:
    std::cout << "\nСтатична прив'язка через вказівник на НЕвіртуальний метод:\n";
    Product* ptr = &laptop;
    // getShippingCost() — НЕ virtual в Product, тому статична прив'язка
    // ptr->getShippingCost(); // ← це б не скомпілювалось — Product не знає про цей метод
    // Демонструємо через вивід без virtual:
    std::cout << "Product::getInfo() через Product*: " << ptr->getInfo() << "\n";

    // ╔══════════════════════════════════════════════════╗
    // ║  Пункти 2, 3: Virtual + Base class pointer      ║
    // ╚══════════════════════════════════════════════════╝
    std::cout << "\n--- 2 & 3. Virtual functions + Base pointer ---\n";
    std::vector<Entity*> entities;
    entities.push_back(new PhysicalProduct(3, "Monitor", 299.99, 5, 3.5, "50x30x10cm"));
    entities.push_back(new DigitalProduct(4, "Photoshop", 199.99, 1200.0, "KEY-5678"));
    entities.push_back(new RegularCustomer(3, "Charlie", "charlie@mail.com", 300.0));
    entities.push_back(new PremiumCustomer(4, "Diana", "diana@mail.com", 2000.0));

    std::cout << "Entity* вказівник викликає правильний display() кожного класу:\n";
    for (Entity* e : entities) {
        showEntityPointer(e); // virtual dispatch — правильний клас
        std::cout << "---\n";
    }

    // ╔══════════════════════════════════════════════════╗
    // ║  Пункт 4: Virtual destructor                    ║
    // ╚══════════════════════════════════════════════════╝
    std::cout << "\n--- 4. Virtual destructor ---\n";
    std::cout << "Видаляємо через Entity* — правильна послідовність деструкторів:\n";
    Entity* tempEntity = new PhysicalProduct(5, "Temp", 9.99, 1, 0.1, "5x5x5cm");
    delete tempEntity; // завдяки virtual destructor викликається PhysicalProduct::~PhysicalProduct()

    // ╔══════════════════════════════════════════════════╗
    // ║  Пункт 5: final                                 ║
    // ╚══════════════════════════════════════════════════╝
    std::cout << "\n--- 5. final ---\n";
    std::cout << "PhysicalProduct i PremiumCustomer — final класи\n";
    std::cout << "Від них не можна наслідуватись (перевіряється компілятором)\n";
    PremiumCustomer premium(5, "Eve", "eve@mail.com", 5000.0);
    premium.addBonusPoints(200);
    premium.display();

    // ╔══════════════════════════════════════════════════╗
    // ║  Пункт 6: Base class reference                  ║
    // ╚══════════════════════════════════════════════════╝
    std::cout << "\n--- 6. Base class reference ---\n";
    std::cout << "Entity& посилання — теж динамічна прив'язка:\n";
    showEntityReference(laptop);
    showEntityReference(alice);
    showEntityReference(bob);

    // ╔══════════════════════════════════════════════════╗
    // ║  Пункт 7: Pure virtual function                 ║
    // ╚══════════════════════════════════════════════════╝
    std::cout << "\n--- 7. Pure virtual function (getValue) ---\n";
    std::cout << "Entity::getValue() = 0 — кожен клас реалізує по своєму:\n";
    for (Entity* e : entities) {
        std::cout << e->getInfo() << " → getValue(): $" << e->getValue() << "\n";
    }

    // ╔══════════════════════════════════════════════════╗
    // ║  Пункт 8: Інтерфейс IDisplayable               ║
    // ╚══════════════════════════════════════════════════╝
    std::cout << "\n--- 8. Interface IDisplayable ---\n";
    std::cout << "Абсолютно різні класи через один інтерфейс:\n";
    printDisplayable(laptop);   // PhysicalProduct
    std::cout << "---\n";
    printDisplayable(alice);    // RegularCustomer
    std::cout << "---\n";
    printDisplayable(premium);  // PremiumCustomer

    // Cleanup
    for (Entity* e : entities) delete e;

    std::cout << "\n===== END =====\n\n";
    return 0;
}
