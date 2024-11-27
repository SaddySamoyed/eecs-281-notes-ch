// Project identifier: 1CAEF3A0FEDD0DEC26BA9808C69D4D22A9962768

#include "evaluate.hpp"
#include <iostream>
#include <stack>
#include <string>
#include <cstdint>


std::int64_t evaluate(std::string const& expression) {
    std::stack<int64_t> operands;
    std::stack<char> operators;

    for (char ch : expression) {
        if (isdigit(ch)) {
            operands.push(ch - '0');
        } else {
            operators.push(ch);
        }
        if (operators.size() > 0 && operands.size() >= 2) {
            char op = operators.top();
            operators.pop();

            int64_t right = operands.top();
            operands.pop();
            int64_t left = operands.top();
            operands.pop();

            int64_t result;
            switch (op) {
                case '+':
                    result = left + right;
                    break;
                case '-':
                    result = left - right;
                    break;
                case '*':
                    result = left * right;
                    break;
                case '/':
                    result = left / right;
                    break;
                default:
                    throw std::invalid_argument("Invalid operator");
            }
            operands.push(result);
        }
    }

    if (operands.size() != 1) {
        throw std::invalid_argument("Invalid expression");
    }

    return operands.top();
}