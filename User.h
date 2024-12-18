#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <functional>

class User {
protected:
    std::string username;
    std::size_t passwordHash;
    std::string token;
    bool isTokenGenerated;

public:
    User(const std::string& name, const std::string& pass);
    virtual ~User() = default;

    void generateToken();
    void displayInfo() const;
    bool verifyPassword(const std::string& pass) const;

    std::string getUsername() const { return username; }
};

#endif // USER_H
