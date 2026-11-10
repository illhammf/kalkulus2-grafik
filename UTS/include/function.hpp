#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>
#include <vector>
#include <exprtk.hpp>

class MathematicalFunction {
private:
    typedef exprtk::symbol_table<double> SymbolTable;
    typedef exprtk::expression<double> Expression;
    typedef exprtk::parser<double> Parser;

    double x;

    SymbolTable symbolTable;
    Expression expression;
    Parser parser;

    bool valid;

public:
    MathematicalFunction();

    bool setFormula(const std::string& formula);

    double evaluate(double inputX) const;

    bool isValid() const;
};

#endif
