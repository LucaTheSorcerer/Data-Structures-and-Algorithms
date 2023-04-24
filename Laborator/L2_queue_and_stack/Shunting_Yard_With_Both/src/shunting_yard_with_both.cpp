//
// Created by Luca Tudor on 24.04.2023.
//

#include "shunting_yard_with_both.h"
#include "/Users/lulu/UBB/Semestrul_II/Data-Structures-and-Algorithms/Laborator/L2_queue_and_stack/Shunting_Yard_With_Both/src/shunting_yard_with_both.h"
#include "/Users/lulu/UBB/Semestrul_II/Data-Structures-and-Algorithms/Laborator/L2_queue_and_stack/Stack/src/stack.h"
#include "/Users/lulu/UBB/Semestrul_II/Data-Structures-and-Algorithms/Laborator/L2_queue_and_stack/Queue/src/queue.h"
#include <sstream>


int get_precedence_both(char op) {   // function to get operator precedence
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

int evaluate_postfix_both(string postfix) {
    Stack operand_stack;
    Queue operand_queue;

    stringstream input(postfix);
    string token;
    while (getline(input, token, ' ')) {
        if (isdigit(token[0])) {
            int operand = stoi(token);
            operand_stack.push(operand);
            operand_queue.push(operand);
        }
        else {
            int operand2 = operand_stack.pop();
            int operand1 = operand_stack.pop();
            int result;

            switch (token[0]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
            }

            operand_stack.push(result);
            operand_queue.push(result);
        }
    }

    return operand_stack.pop();
}

string infix_to_postfix_conversion_both(const string& infix) {
    stringstream input(infix);
    string output = "";
    Stack operator_stack;
    Queue postfix_queue;
    string token;
    while (getline(input, token, ' ')) {
        if (isdigit(token[0])) {
            output += token;
            output += " ";
            postfix_queue.push(stoi(token));
        }
        else if (token[0] == '(') {
            operator_stack.push(token[0]);
        }
        else if (token[0] == ')') {
            while (operator_stack.top() != '(') {
                output += operator_stack.top();
                output += " ";
                postfix_queue.push(operator_stack.top());
                operator_stack.pop();
            }
            operator_stack.pop();
        }
        else {
            while (!operator_stack.isEmpty() && get_precedence_both(token[0]) <= get_precedence_both(operator_stack.top())) {
                output += operator_stack.top();
                output += " ";
                postfix_queue.push(operator_stack.top());
                operator_stack.pop();
            }
            operator_stack.push(token[0]);
        }
    }
    while (!operator_stack.isEmpty()) {
        output += operator_stack.top();
        output += " ";
        postfix_queue.push(operator_stack.top());
        operator_stack.pop();
    }
    return output;
}