#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <functional>

// Структура узла для бинарного дерева поиска
template <typename T, typename U>
struct Node {
    std::pair<T, U> data;
    Node* left;
    Node* right;
    Node(const std::pair<T, U>& val) : data(val), left(nullptr), right(nullptr) {}
};

// Шаблонный класс для бинарного дерева
template <typename T, typename U>
class BinaryTree {
private:
    Node<T, U>* root;
    
    void destroyTree(Node<T, U>* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void add(Node<T, U>*& node, const std::pair<T, U>& value) {
        if (!node) {
            node = new Node<T, U>(value);
            return;
        }
        if (value.second < node->data.second) {
            add(node->left, value);
        } else if (value.second > node->data.second) {
            add(node->right, value);
        }
    }

    void inOrder(Node<T, U>* node, std::vector<std::pair<T, U>>& result) const {
        if (node) {
            inOrder(node->left, result);
            result.push_back(node->data);
            inOrder(node->right, result);
        }
    }

    bool equals(Node<T, U>* a, Node<T, U>* b) const {
        if (!a && !b) return true;
        if (!a || !b) return false;
        return a->data == b->data && equals(a->left, b->left) && equals(a->right, b->right);
    }

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { destroyTree(root); }

    // Добавить пару в дерево
    void add(const T& event, const U& date) {
        add(root, {event, date});
    }

    // Получить коллекцию в отсортированном порядке дат
    std::vector<std::pair<T, U>> getSortedCollection() const {
        std::vector<std::pair<T, U>> result;
        inOrder(root, result);
        return result;
    }

    // Сравнить две коллекции
    bool operator==(const BinaryTree<T, U>& other) const {
        return equals(root, other.root);
    }

    // Сохранить дерево в файл
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        auto sortedData = getSortedCollection();
        for (const auto& item : sortedData) {
            file << item.first << ", " << item.second << "\n";
        }
        file.close();
    }

    // Загрузить дерево из файла
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string event;
        U date;
        while (file >> event >> date) {
            add(event, date);
        }
        file.close();
    }
};

int main() {
    BinaryTree<std::string, std::string> astroTree;

    // Добавление значений в коллекцию
    astroTree.add("Солнечное затмение", "2024-04-08");
    astroTree.add("Лунное затмение", "2024-09-18");
    astroTree.add("Метеорный дождь", "2024-08-12");

    // Проверка отсортированной коллекции
    auto sorted = astroTree.getSortedCollection();
    for (const auto& item : sorted) {
        std::cout << item.first << " - " << item.second << std::endl;
    }

    // Сохранение в файл и загрузка
    astroTree.saveToFile("astro_events.txt");
    BinaryTree<std::string, std::string> newTree;
    newTree.loadFromFile("astro_events.txt");

    std::cout << "Все тесты успешно пройдены!" << std::endl;
    return 0;
}
