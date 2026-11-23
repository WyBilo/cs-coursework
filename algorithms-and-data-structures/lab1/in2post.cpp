#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include "GenericStack.h"

using namespace std;

bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int precedence(const string& op) {
    if (op == "*" || op == "/") {
        return 2;
    }

    if (op == "+" || op == "-") {
        return 1;
    }

    return 0;
}

bool isNumber(const string& token) {
    if (token.length() == 0) {
        return false;
    }

    char* endptr = NULL;
    strtod(token.c_str(), &endptr);

    return *endptr == '\0';
}

bool isOperand(const string& token) {
    return token != "(" && token != ")" && !isOperator(token);
}

void addToken(string& output, const string& token) {
    if (output.length() > 0) {
        output += " ";
    }

    output += token;
}

string getNextToken(const string& line, int& index) {
    string token = "";

    while (index < static_cast<int>(line.length()) && isspace(line[index])) {
        index++;
    }

    while (index < static_cast<int>(line.length()) && !isspace(line[index])) {
        token += line[index];
        index++;
    }

    return token;
}

bool infixToPostfix(const string& infix, string& postfix) {
    GenericStack<string> operatorStack;

    enum LastToken {
        NONE,
        OPERAND,
        OPERATOR,
        LEFT_PAREN,
        RIGHT_PAREN
    };

    LastToken last = NONE;
    postfix = "";

    int index = 0;

    while (index < static_cast<int>(infix.length())) {
        string token = getNextToken(infix, index);

        if (token.length() == 0) {
            break;
        }

        if (isOperand(token)) {
            if (last == OPERAND || last == RIGHT_PAREN) {
                cerr << "Error: invalid expression." << endl;
                return false;
            }

            addToken(postfix, token);
            last = OPERAND;
        }
        else if (token == "(") {
            if (last == OPERAND || last == RIGHT_PAREN) {
                cerr << "Error: invalid expression." << endl;
                return false;
            }

            operatorStack.push(token);
            last = LEFT_PAREN;
        }
        else if (isOperator(token)) {
            if (last == NONE || last == OPERATOR || last == LEFT_PAREN) {
                cerr << "Error: invalid expression." << endl;
                return false;
            }

            while (!operatorStack.empty()
                && operatorStack.top() != "("
                && precedence(operatorStack.top()) >= precedence(token)) {
                addToken(postfix, operatorStack.top());
                operatorStack.pop();
            }

            operatorStack.push(token);
            last = OPERATOR;
        }
        else if (token == ")") {
            if (last == OPERATOR || last == LEFT_PAREN || last == NONE) {
                cerr << "Error: invalid expression." << endl;
                return false;
            }

            bool foundLeftParenthesis = false;

            while (!operatorStack.empty()) {
                if (operatorStack.top() == "(") {
                    foundLeftParenthesis = true;
                    operatorStack.pop();
                    break;
                }

                addToken(postfix, operatorStack.top());
                operatorStack.pop();
            }

            if (!foundLeftParenthesis) {
                cerr << "Error: mismatched parentheses." << endl;
                return false;
            }

            last = RIGHT_PAREN;
        }
        else {
            cerr << "Error: invalid token." << endl;
            return false;
        }
    }

    if (last == OPERATOR || last == LEFT_PAREN) {
        cerr << "Error: invalid expression." << endl;
        return false;
    }

    while (!operatorStack.empty()) {
        if (operatorStack.top() == "(") {
            cerr << "Error: mismatched parentheses." << endl;
            return false;
        }

        addToken(postfix, operatorStack.top());
        operatorStack.pop();
    }

    return true;
}

bool postfixHasOnlyNumbers(const string& postfix) {
    int index = 0;

    while (index < static_cast<int>(postfix.length())) {
        string token = getNextToken(postfix, index);

        if (token.length() == 0) {
            break;
        }

        if (!isOperator(token) && !isNumber(token)) {
            return false;
        }
    }

    return true;
}

bool evaluatePostfix(const string& postfix, double& result) {
    GenericStack<double> operandStack;

    int index = 0;

    while (index < static_cast<int>(postfix.length())) {
        string token = getNextToken(postfix, index);

        if (token.length() == 0) {
            break;
        }

        if (isNumber(token)) {
            operandStack.push(atof(token.c_str()));
        }
        else if (isOperator(token)) {
            if (operandStack.size() < 2) {
                cerr << "Error: not enough operands." << endl;
                return false;
            }

            double right = operandStack.top();
            operandStack.pop();

            double left = operandStack.top();
            operandStack.pop();

            double value = 0.0;

            if (token == "+") {
                value = left + right;
            }
            else if (token == "-") {
                value = left - right;
            }
            else if (token == "*") {
                value = left * right;
            }
            else if (token == "/") {
                if (right == 0.0) {
                    cerr << "Error: division by zero." << endl;
                    return false;
                }

                value = left / right;
            }

            operandStack.push(value);
        }
        else {
            cerr << "Error: invalid postfix expression." << endl;
            return false;
        }
    }

    if (operandStack.empty()) {
        result = 0.0;
        return true;
    }

    if (operandStack.size() > 1) {
        cerr << "Error: too many operands." << endl;
        return false;
    }

    result = operandStack.top();
    return true;
}

void printNumber(double value) {
    long long whole = static_cast<long long>(value);

    if (value == static_cast<double>(whole)) {
        cout << whole << endl;
    }
    else {
        cout << value << endl;
    }
}

int main() {
    string line;

    cout << "Enter infix expression, or press Ctrl+D to quit:" << endl;

    while (getline(cin, line)) {
        if (line.length() == 0) {
            cout << "Enter infix expression, or press Ctrl+D to quit:" << endl;
            continue;
        }

        string postfix = "";

        if (infixToPostfix(line, postfix)) {
            cout << postfix << endl;

            if (postfixHasOnlyNumbers(postfix)) {
                double result = 0.0;

                if (evaluatePostfix(postfix, result)) {
                    printNumber(result);
                }
            }
        }

        cout << "Enter infix expression, or press Ctrl+D to quit:" << endl;
    }

    return 0;
}