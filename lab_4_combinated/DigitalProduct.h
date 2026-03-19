#pragma once
#include "Product.h"

// Цифровий товар — має розмір файлу і ліцензію (Is-A Product)
class DigitalProduct : public Product {
private:
    double fileSizeMB;
    std::string licenseKey;

public:
    DigitalProduct(int id, const std::string& name, double price,
                   double fileSizeMB, const std::string& licenseKey);
    DigitalProduct(const DigitalProduct& other);
    DigitalProduct(DigitalProduct&& other) noexcept;
    ~DigitalProduct();

    double getFileSizeMB()    const;
    std::string getLicense()  const;

    void display()        const override;
    std::string getInfo() const override;
    double getValue()     const override;
};
