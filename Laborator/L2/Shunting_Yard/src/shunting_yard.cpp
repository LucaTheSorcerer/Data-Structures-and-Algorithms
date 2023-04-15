//
// Created by Luca Tudor on 14.04.2023.
//
//Include the stack
#include "../../Stack/src/Stack.h"
#include "../../Queue/src/Queue.h"
#include <sstream>

//Method that computes the precedence of an operator

int get_precedence(char op) {   // function to get operator precedence
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else {
        return 0;   // return 0 for non-operators
    }
}

int evaluate_postfix(const string& postfix) {   // function to evaluate postfix expression
    Stack stack;
    stringstream ss(postfix);
    string token;
    while (getline(ss, token, ' ')) {
        if (isdigit(token[0])) {
            stack.push(stoi(token));
        }
        else {
            int op2 = stack.pop();
            int op1 = stack.pop();
            switch (token[0]) {
                case '+':
                    stack.push(op1 + op2);
                    break;
                case '-':
                    stack.push(op1 - op2);
                    break;
                case '*':
                    stack.push(op1 * op2);
                    break;
                case '/':
                    stack.push(op1 / op2);
                    break;
            }
        }
    }
    return stack.pop();
}

string infix_to_postfix_conversion(const string& infix) {   // function to convert infix
    stringstream input(infix);
    string output;
    Stack operator_stack;
    string token;
    while (getline(input, token, ' ')) {
        if (isdigit(token[0])) {
            output += token;
            output += " ";
        }
        else if (token[0] == '(') {
            operator_stack.push(token[0]);
        }
        else if (token[0] == ')') {
            while (operator_stack.getTail() != nullptr && operator_stack.getTail()->info != '(') {
                char op = operator_stack.pop();
                output += op;
                output += " ";
            }
            operator_stack.pop(); // discard the '('
        }
        else {
            while (operator_stack.getTail() != nullptr && get_precedence(token[0]) <= get_precedence(operator_stack.getTail()->info)) {
                char op = operator_stack.pop();
                output += op;
                output += " ";
            }
            operator_stack.push(token[0]);
        }
    }
    while (operator_stack.getTail() != nullptr) {
        char op = operator_stack.pop();
        output += op;
        output += " ";
    }
    return output;
}