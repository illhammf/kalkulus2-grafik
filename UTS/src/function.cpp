
#include "function.hpp"

MathematicalFunction::MathematicalFunction()
    : x(0.0), valid(false) {

    symbolTable.add_variable("x", x);
    symbolTable.add_constants();

    expression.register_symbol_table(symbolTable);
}

bool MathematicalFunction::setFormula(const std::string& formula) {
    valid = parser.compile(formula, expression);
    return valid;
}

double MathematicalFunction::evaluate(double inputX) const {
    if (!valid) {
        return 0.0;
    }

    const_cast<MathematicalFunction*>(this)->x = inputX;

    return expression.value();
}

bool MathematicalFunction::isValid() const {
    return valid;
}
