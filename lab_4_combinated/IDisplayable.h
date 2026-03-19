#pragma once
#include <string>

// Інтерфейс — всі методи чисто віртуальні (лаб 5, пункт 8)
class IDisplayable {
public:
    virtual void display() const = 0;
    virtual std::string getInfo() const = 0;
    virtual ~IDisplayable() = default;
};
