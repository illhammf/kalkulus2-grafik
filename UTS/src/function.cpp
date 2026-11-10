
#include "function.hpp"

MathematicalFunction::MathematicalFunction()
    : x(0.0), valid(false), errorMessage("") {

    symbolTable.add_variable("x", x);
    symbolTable.add_constants();

    expression.register_symbol_table(symbolTable);
}

bool MathematicalFunction::setFormula(const std::string& formula) {
    if (formula.empty()) {
        valid = false;
        errorMessage = "Rumus tidak boleh kosong.";
        return false;
    }

    valid = parser.compile(formula, expression);

    if (!valid) {
        errorMessage = "Format rumus matematika tidak valid.";
        return false;
    }

    errorMessage.clear();
    return true;
}

double MathematicalFunction::evaluate(double inputX) {
    if (!valid) {
        return 0.0;
    }

    x = inputX;

    return expression.value();
}

bool MathematicalFunction::isValid() const {
    return valid;
}

std::string MathematicalFunction::getErrorMessage() const {
    return errorMessage;
}
