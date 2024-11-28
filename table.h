#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include <memory>

class Cell {
public:
    enum class Type { Number, Text, Formula, Empty };
    virtual ~Cell() = default;
    virtual Type getType() const = 0;
    virtual std::string getValue() const = 0;
};

class NumericCell : public Cell {
public:
    explicit NumericCell(double value);
    Type getType() const override;
    std::string getValue() const override;
    double getNumber() const;
    void setNumber(double value);

private:
    double value;
};

class TextCell : public Cell {
public:
    explicit TextCell(const std::string& text);
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

#endif // TABLE_H
