#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

class Cell {
public:
    enum class Type { Number, Text, Formula, Empty };
    virtual ~Cell() = default;
    virtual Type getType() const = 0;
    virtual std::string getValue() const = 0;
};

class NumericCell : public Cell {
public:
    explicit NumericCell(double value = 0.0);
    Type getType() const override;
    std::string getValue() const override;
    double getNumber() const;
    void setNumber(double value);

private:
    double value;
};

class TextCell : public Cell {
public:
    explicit TextCell(const std::string& text = "");
    Type getType() const override;
    std::string getValue() const override;
    const std::string& getText() const;
    void setText(const std::string& text);

private:
    std::string text;
};

class FormulaCell : public Cell {
public:
    enum class Operation { Sum, Product, Average };
    FormulaCell(const std::vector<std::shared_ptr<Cell>>& range, Operation operation);
    Type getType() const override;
    std::string getValue() const override;

private:
    std::vector<std::shared_ptr<Cell>> range;
    Operation operation;
    double calculate() const;
};

class Table {
public:
    Table(int rows, int cols);
    std::shared_ptr<Cell> getCell(int row, int col) const;
    void setCell(int row, int col, std::shared_ptr<Cell> cell);
    void printTable() const;

private:
    int rows, cols;
    std::vector<std::vector<std::shared_ptr<Cell>>> cells;
    void checkBounds(int row, int col) const;
};

#endif
