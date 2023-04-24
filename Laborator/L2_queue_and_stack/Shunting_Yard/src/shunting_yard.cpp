//
// Created by Luca Tudor on 14.04.2023.
//

#include "../../Stack/src/Stack.h"
#include "../../Queue/src/Queue.h"
#include <sstream>


/**
 * @brief: General explanation of the algorithm
 * This is the implementation of the shunting yard algorithm. It converts an infix expression to a postfix expression
 * The algorithm is based on the following rules:
 */




/**
 * @brief: This function returns the precedence of an operator
 * @details: This function takes as input an operator and it returns its precedence as an integer.
 * The operators with a higher precedence will be evaluated first.
 * The operator's precedence is defined as follows:
 * 1. + and - have precedence 1
 * 2. * and / have precedence 2
 * 3. for non-operators the function returns 0
 * @param op A single character representing an operator
 * @return the precedence of the input operator as an integer
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-MediumCase θ(1)
 * @TimeComplexity-WorstCase θ(1)
 */
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

/**
 * @brief: This function evaluates a postfix expression and returns the result
 * @details: The function returns the result by evaluating the expression and it does so by iterating
 * through each token in the postfix expression and it is either pushing it onto the stack or it is performing an
 * operation based on the operator.
 * The function uses an empty stack and a stringstream ss that contains the input postix expression.
 * It iterates through the expression using getline and parses each token separated by spaces and it stores it in the
 * string variable called token.
 * There are two cases: If the token is a digit, it is converted to an integer using stoi and it is pushed onto the
 * stack. If the token is an operator. It then pops the two top elements off the stack and saves the first into op2 and
 * the second into op1
 * Then the function uses a switch statement based on the value of the token[0] that represents the first char in the
 * token string. It performs the operation and the result is pushed onto the stack.
 * The function returns the result by popping the top element of the stack.
 * @param postfix represents the postfix expression to be evaluated
 * @return an integer representing the result of the expression evaluation
 * @TimeComplexity-BestCase θ(n)
 * @TimeComplexity-MediumCase θ(n)
 * @TimeComplexity-WorstCase θ(n)
 * @throws: none
 */
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

/**
 * @brief: This function converts an infix expression to a postfix expression using the shunting yard algorithm
 * @details: The function uses an empty stack and a stringstream input for the input infix expression.
 * It also initializes an empty string called output that will contain the postfix expression.
 * It reads each token of the input expression one by one using a while loop that uses getline.
 * If the token is an operand or number, it is appended to the output string followed by a space character
 * If the token is a left parenthesis, it is pushed onto the operator stack
 * If the token is a right parenthesis, it pops operators of the stack and appends them to the output string until a
 * left parenthesis is reached. The pop the left parenthesis and discard it.
 * If the token is an operator, it pop operators from the stack and appends them to the output string as long as they
 * have a higher precedence than the current operator. Finally pish the current operator onto the operator stack.
 * The above steps are repeated until there are no more token in the string
 * Finally, the function pops all the remaining operators from the stack and appends them to the output string.
 * @param infix represents the infix expression to be converted
 * @return a string representing the postfix expression equivalent to the input expression in infix notation
 * @TimeComplexity-BestCase θ(n)
 * @TimeComplexity-MediumCase θ(n)
 * @TimeComplexity-WorstCase θ(n)
 */
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