#ifndef ACCESSCONTROL_H
#define ACCESSCONTROL_H

#include "User.h"
#include <unordered_map>
#include <bitset> 

class AccessControl : public User {
private:
    std::unordered_map<std::string, uint64_t> accessRights;

public:
    AccessControl(const std::string& name, const std::string& pass);
    void setAccess(const std::string& site, uint64_t rights);
    void displayAccessRights() const;
    bool checkAccess(const std::string& site, uint64_t mask) const;
};

#endif
