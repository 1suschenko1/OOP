#include "AccessControl.h"

AccessControl::AccessControl(const std::string& name, const std::string& pass)
    : User(name, pass) {}

void AccessControl::setAccess(const std::string& site, uint64_t rights) {
    accessRights[site] = rights;
    std::cout << "Права доступа для сайта \"" << site << "\" установлены: " 
              << std::bitset<8>(rights) << "\n";
}

void AccessControl::displayAccessRights() const {
    std::cout << "Права доступа:\n";
    for (const auto& pair : accessRights) {
        std::cout << "Сайт: " << pair.first << ", Права: " << std::bitset<8>(pair.second) << "\n";
    }
}

bool AccessControl::checkAccess(const std::string& site, uint64_t mask) const {
    auto it = accessRights.find(site);
    if (it != accessRights.end()) {
        return (it->second & mask) == mask;
    }
    return false;
}
