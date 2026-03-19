#include "Entity.h"
#include <utility>

Entity::Entity(int id, const std::string& createdAt)
    : id(id), createdAt(createdAt) {
    std::cout << "[Entity] Created #" << id << "\n";
}

Entity::Entity(const Entity& other)
    : id(other.id), createdAt(other.createdAt) {
    std::cout << "[Entity] Copy ctor #" << id << "\n";
}

Entity::Entity(Entity&& other) noexcept
    : id(other.id), createdAt(std::move(other.createdAt)) {
    other.id = -1;
    std::cout << "[Entity] Move ctor\n";
}

Entity& Entity::operator=(const Entity& other) {
    if (this != &other) {
        id = other.id;
        createdAt = other.createdAt;
        std::cout << "[Entity] operator= #" << id << "\n";
    }
    return *this;
}

Entity::~Entity() {
    std::cout << "[Entity] Destroyed #" << id << "\n";
}

int Entity::getId() const { return id; }
std::string Entity::getCreatedAt() const { return createdAt; }

void Entity::display() const {
    std::cout << "Entity #" << id << " created: " << createdAt << "\n";
}

std::string Entity::getInfo() const {
    return "Entity #" + toStr(id);
}
