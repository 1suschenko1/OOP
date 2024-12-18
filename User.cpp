#include "User.h"
#include <cstdlib>

User::User(const std::string& name, const std::string& pass)
    : username(name), passwordHash(std::hash<std::string>{}(pass)), token(""), isTokenGenerated(false) {}

void User::generateToken() {
    if (isTokenGenerated) {
        std::cout << "Ошибка: Токен уже был сгенерирован ранее.\n";
        return;
    }

    token = "TOKEN_" + std::to_string(rand() % 10000);
    isTokenGenerated = true;
    std::cout << "Токен сгенерирован: " << token << "\n";
}

void User::displayInfo() const {
    std::cout << "Имя пользователя: " << username << "\n";
    if (isTokenGenerated) {
        std::cout << "Токен: " << token << "\n";
    } else {
        std::cout << "Токен ещё не был сгенерирован.\n";
    }
}

bool User::verifyPassword(const std::string& pass) const {
    return passwordHash == std::hash<std::string>{}(pass);
}
