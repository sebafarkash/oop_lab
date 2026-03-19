#pragma once
#include "Product.h"

// Фізичний товар — має вагу і розміри (Is-A Product)
class PhysicalProduct final : public Product {
private:
    double weight;
    std::string dimensions;

public:
    PhysicalProduct(int id, const std::string& name, double price,
                    int stock, double weight, const std::string& dimensions);
    PhysicalProduct(const PhysicalProduct& other);
    PhysicalProduct(PhysicalProduct&& other) noexcept;
    PhysicalProduct& operator=(const PhysicalProduct& other);
    ~PhysicalProduct();

    double getWeight() const;
    double getShippingCost() const;

    void display()        const override;
    std::string getInfo() const override;
    double getValue()     const override;
};
// (додаємо в public секцію)
