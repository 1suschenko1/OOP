#include "table.h"
#include <stdexcept>
#include <numeric>

// Реализация NumericCell
NumericCell::NumericCell(double value) : value(value) {}

Cell::Type NumericCell::getType() const {
    return Type::Number;
}

std::string NumericCell::getValue() const {
    return std::to_string(value);
}

double NumericCell::getNumber() const { 
    return value; 
}

void NumericCell::setNumber(double value) { 
    this->value = value; 
}

// Реализация TextCell
TextCell::TextCell(const std::string& text) : text(text) {}

Cell::Type TextCell::getType() const {
    return Type::Text;
}

std::string TextCell::getValue() const {
    return text;
}

const std::string& TextCell::getText() const {
    return text;
}

void TextCell::setText(const std::string& text) {
    this->text = text;
}

// Реализация FormulaCell
FormulaCell::FormulaCell(const std::vector<std::shared_ptr<Cell>>& range, Operation operation)
    : range(range), operation(operation) {}

Cell::Type FormulaCell::getType() const {
    return Type::Formula;
}

std::string FormulaCell::getValue() const {
    try {
        double result = calculate();
        return std::to_string(result);
    } catch (const std::runtime_error& e) {
        return e.what();
    }
}

double FormulaCell::calculate() const {
    if (range.empty()) throw std::runtime_error("Ошибка: пустой диапазон");

    double result = (operation == Operation::Product) ? 1.0 : 0.0;
    int count = 0;

    for (const auto& cell : range) {
        if (cell->getType() != Type::Number) {
            throw std::runtime_error("Ошибка: нечисловая ячейка в диапазоне");
        }

        double value = std::static_pointer_cast<NumericCell>(cell)->getNumber();
        count++;

        switch (operation) {
            case Operation::Sum:
                result += value;
                break;
            case Operation::Product:
                result *= value;
                break;
            case Operation::Average:
                result += value;
                break;
        }
    }

    if (operation == Operation::Average && count > 0) {
        result /= count;
    }

    return result;
}
