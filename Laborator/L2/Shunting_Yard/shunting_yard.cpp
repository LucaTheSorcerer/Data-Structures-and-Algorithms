//
// Created by Luca Tudor on 14.04.2023.
//
//Include the stack
#include "../Stack/src/Stack.h"
#include "../Queue/src/Queue.h"
#include <sstream>

//Method that computes the precedence of an operator

int get_precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }

    else if(op == '*' || op == '/') {
        return 2;
    }

    else {
        return 0;
    }
}

//Method that evaluates a postfix expression

int evaluate_postfix(const string& postfix) {
    Stack stack;
    stringstream ss(postfix);
    string token;

    while(getline(ss, token, ' ')) {
        if(isdigit(token[0])) {
            stack.push(stoi(token));
        }
        else {
            int op2 = stack.pop();
            int op1 = stack.pop();
            switch(token[0]) {
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