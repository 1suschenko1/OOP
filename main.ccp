#include "table.h"
#include <iostream>
#include <memory>

int main() {
    Table table(3, 3);

    // Установка числовых и текстовых значений
    table.setCell(0, 0, std::make_shared<NumericCell>(1));
    table.setCell(0, 1, std::make_shared<NumericCell>(2));
    std::vector<std::shared_ptr<Cell>> range = { table.getCell(0, 0), table.getCell(0, 1) };
    table.setCell(0, 2, std::make_shared<FormulaCell>(range, FormulaCell::Operation::Sum));
    
    std::cout << "Текущая таблица:" << std::endl;
    table.printTable();

    
    return 0;
}
