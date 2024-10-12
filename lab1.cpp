#include <iostream>
#include <vector>
#include <string>
#include <cassert>

// Класс, представляющий ячейку таблицы
class Cell {
public:
    enum Type { NUMBER, TEXT, EMPTY };

    Cell() : type(EMPTY), numericValue(0) {}

    Cell(const Cell& other) : type(other.type), numericValue(other.numericValue), textValue(other.textValue) {}

    // Метод для установки числового значения в ячейку
    void setValue(double number) {
        type = NUMBER;
        numericValue = number;
        textValue.clear();
    }

    // Метод для установки текстового значения в ячейку
    void setValue(const std::string& text) {
        type = TEXT;
        textValue = text;
        numericValue = 0;
    }

    // Метод для получения типа данных ячейки (число, текст или пусто)
    Type getType() const {
        return type;
    }

    // Метод для получения числового значения ячейки
    double getNumber() const {
        assert(type == NUMBER);
        return numericValue;
    }

    // Метод для получения текстового значения ячейки
    const std::string& getText() const {
        assert(type == TEXT);
        return textValue;
    }

    // Метод для проверки, является ли ячейка пустой
    bool isEmpty() const {
        return type == EMPTY;
    }

private:
    Type type;
    double numericValue;
    std::string textValue;
};

// Класс, представляющий таблицу из ячеек
class Table {
public:
    // Конструктор, создающий таблицу заданного размера (строки x столбцы)
    Table(int rows, int cols) : rows(rows), cols(cols) {
        cells.resize(rows, std::vector<Cell>(cols));
    }

    // Конструктор копирования для класса Table
    Table(const Table& other) : rows(other.rows), cols(other.cols), cells(other.cells) {}

    // Метод для получения ссылки на ячейку по её координатам (строка, столбец)
    Cell& getCell(int row, int col) {
        assert(row >= 0 && row < rows);
        assert(col >= 0 && col < cols);
        return cells[row][col];
    }

    // Метод для вычисления суммы числовых значений в диапазоне ячеек
    double calculateSum(int startRow, int startCol, int endRow, int endCol) const {
        double sum = 0;
        for (int i = startRow; i <= endRow; ++i) {
            for (int j = startCol; j <= endCol; ++j) {
                if (cells[i][j].getType() == Cell::NUMBER) {
                    sum += cells[i][j].getNumber();
                }
            }
        }
        return sum;
    }

    // Метод для вывода текущего состояния таблицы
    void printTable() const {
        for (const auto& row : cells) {
            for (const auto& cell : row) {
                if (cell.getType() == Cell::NUMBER) {
                    std::cout << cell.getNumber() << "\t";
                } else if (cell.getType() == Cell::TEXT) {
                    std::cout << cell.getText() << "\t";
                } else {
                    std::cout << "EMPTY\t";
                }
            }
            std::cout << std::endl;
        }
    }

private:
    int rows, cols;
    std::vector<std::vector<Cell>> cells;
};

// Функция для тестирования всех функций
void testTable() {
    Table table(3, 3);

    // Тест 1: Устанавливаем числовое значение в ячейку и проверяем его
    table.getCell(0, 0).setValue(10.5);
    assert(table.getCell(0, 0).getNumber() == 10.5);

    // Тест 2: Устанавливаем текстовое значение и проверяем его
    table.getCell(0, 2).setValue("Hello");
    assert(table.getCell(0, 2).getText() == "Hello");

    // Тест 3: Проверка суммы диапазона чисел
    table.getCell(0, 1).setValue(20.0);
    table.getCell(1, 0).setValue(5.0);
    table.getCell(1, 1).setValue(15.0);
    assert(table.calculateSum(0, 0, 1, 1) == 50.5);

    // Тест 4: Проверка пустой ячейки
    assert(table.getCell(2, 2).isEmpty());

    std::cout << "Все тесты пройдены успешно!" << std::endl;
}

int main() {
    testTable();

    // Дополнительный пример использования программы:
    Table table(3, 3);

    // Заполнение таблицы значениями
    table.getCell(0, 0).setValue(10.5);
    table.getCell(0, 1).setValue(20.0);
    table.getCell(0, 2).setValue("Hello");
    table.getCell(1, 0).setValue(5.0);
    table.getCell(1, 1).setValue(15.0);
    table.getCell(2, 0).setValue("Text");

    // Печать таблицы
    std::cout << "Текущая таблица:" << std::endl;
    table.printTable();

    // Вычисление и вывод суммы диапазона
    double sum = table.calculateSum(0, 0, 1, 1);
    std::cout << "Сумма диапазона (0,0) - (1,1): " << sum << std::endl;

    return 0;
}
