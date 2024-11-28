#include "table.h"
#include <cassert>
#include <iostream>
#include <memory>

int main() {
    std::cout << "Начало тестирования NumericCell" << std::endl;

    NumericCell nc1(10.5);
    assert(nc1.getType() == Cell::Type::Number);
    assert(nc1.getNumber() == 10.5);

    nc1.setNumber(20.0);
    assert(nc1.getNumber() == 20.0);

    std::cout << "NumericCell пройдено успешно" << std::endl << std::endl;

    std::cout << "Начало тестирования TextCell" << std::endl;

    TextCell tc1("Hello");
    assert(tc1.getType() == Cell::Type::Text);
    assert(tc1.getText() == "Hello");

    tc1.setText("World");
    assert(tc1.getText() == "World");

    std::cout << "TextCell пройдено успешно" << std::endl << std::endl;

    std::cout << "Начало тестирования FormulaCell" << std::endl;

    auto nc2 = std::make_shared<NumericCell>(5.0);
    auto nc3 = std::make_shared<NumericCell>(15.0);
    auto nc4 = std::make_shared<NumericCell>(25.0);

    std::vector<std::shared_ptr<Cell>> range = { nc2, nc3, nc4 };

    FormulaCell sumCell(range, FormulaCell::Operation::Sum);
    assert(sumCell.getType() == Cell::Type::Formula);
    assert(sumCell.getValue() == "45.000000");
    std::cout << "Сумма: " << sumCell.getValue() << std::endl;

    FormulaCell productCell(range, FormulaCell::Operation::Product);
    assert(productCell.getValue() == "1875.000000");
    std::cout << "Произведение: " << productCell.getValue() << std::endl;

    FormulaCell averageCell(range, FormulaCell::Operation::Average);
    assert(averageCell.getValue() == "15.000000");
    std::cout << "Среднее: " << averageCell.getValue() << std::endl;

    std::cout << "FormulaCell пройдено успешно" << std::endl;
    std::cout << "Все тесты пройдены успешно!" << std::endl;
    return 0;
}
