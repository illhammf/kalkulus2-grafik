#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <string>
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
    std::string errorMessage;

public:
    MathematicalFunction();

    bool setFormula(const std::string& formula);

    double evaluate(double inputX);

    bool isValid() const;

    std::string getErrorMessage() const;
};

#endif
