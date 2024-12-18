#include "AccessControl.h"
#include <iostream>
#include <vector>

using namespace std;

// Инициализация пользователей в коде
void initializeUsers(vector<AccessControl>& users) {
    users.emplace_back("admin", "admin123");
    users.emplace_back("123", "123");
    users.emplace_back("guest", "guest123");
}

// Функция для проверки имени пользователя и пароля
AccessControl* authenticateUser(vector<AccessControl>& users, const string& username, const string& password) {
    for (auto& user : users) {
        if (user.getUsername() == username && user.verifyPassword(password)) {
            return &user;
        }
    }
    return nullptr;
}

int main() {
    vector<AccessControl> users;
    initializeUsers(users);

    string username, password;
    AccessControl* currentUser = nullptr;

    // Авторизация
    while (!currentUser) {
        cout << "Введите имя пользователя: ";
        cin >> username;
        cout << "Введите пароль: ";
        cin >> password;

        currentUser = authenticateUser(users, username, password);
        if (!currentUser) {
            cout << "Ошибка: Неправильное имя пользователя или пароль. Попробуйте снова.\n";
        }
    }

    cout << "Добро пожаловать, " << currentUser->getUsername() << "!\n";

    // Основное меню
    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Сгенерировать токен\n";
        cout << "2. Показать информацию о пользователе\n";
        cout << "3. Установить права доступа\n";
        cout << "4. Показать все права доступа\n";
        cout << "5. Проверить права доступа\n";
        cout << "6. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        string site;
        uint64_t rights, mask;

        switch (choice) {
            case 1:
                currentUser->generateToken();
                break;
            case 2:
                currentUser->displayInfo();
                break;
            case 3:
                cout << "Введите название сайта: ";
                cin >> site;
                cout << "Введите права доступа (битовая маска): ";
                cin >> rights;
                currentUser->setAccess(site, rights);
                break;
            case 4:
                currentUser->displayAccessRights();
                break;
            case 5:
                cout << "Введите название сайта: ";
                cin >> site;
                cout << "Введите маску доступа для проверки: ";
                cin >> mask;
                if (currentUser->checkAccess(site, mask)) {
                    cout << "Доступ к \"" << site << "\" разрешён.\n";
                } else {
                    cout << "Доступ к \"" << site << "\" запрещён.\n";
                }
                break;
            case 6:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный ввод. Попробуйте снова.\n";
        }
    } while (choice != 6);

    return 0;
}
