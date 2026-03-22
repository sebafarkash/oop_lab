#pragma once
#include "IDisplayable.h"
#include <string>
#include <iostream>
#include <sstream>

// Helper замість std::to_string (фікс для MinGW)
template<typename T>
std::string toStr(T val) {
    std::ostringstream ss;
    ss << val;
    return ss.str();
}

class Entity : public IDisplayable {
protected:
    int id;
    std::string createdAt;

public:
    Entity(int id, const std::string& createdAt = "2025-01-01");
    Entity(const Entity& other);
    Entity(Entity&& other) noexcept;
    Entity& operator=(const Entity& other);
    virtual ~Entity();

    int getId() const;
    std::string getCreatedAt() const;

    virtual void display() const override;
    virtual std::string getInfo() const override;
    virtual double getValue() const = 0;
};
