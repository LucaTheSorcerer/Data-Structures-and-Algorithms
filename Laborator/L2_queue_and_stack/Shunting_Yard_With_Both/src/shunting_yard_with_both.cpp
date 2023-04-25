//
// Created by Luca Tudor on 24.04.2023.
//

#include "shunting_yard_with_both.h"
#include "/Users/lulu/UBB/Semestrul_II/Data-Structures-and-Algorithms/Laborator/L2_queue_and_stack/Shunting_Yard_With_Both/src/shunting_yard_with_both.h"
#include "/Users/lulu/UBB/Semestrul_II/Data-Structures-and-Algorithms/Laborator/L2_queue_and_stack/Stack/src/stack.h"
#include "/Users/lulu/UBB/Semestrul_II/Data-Structures-and-Algorithms/Laborator/L2_queue_and_stack/Queue/src/queue.h"
#include <sstream>
#include <cmath>


/**
 * @brief function used to determine the precedence of an operator
 * @details It takes an operator as input and returns an integer value representing the precedence. The higher the value
 * that is returned, the higher the precedence of the operator. The function checks the input parameter with different
 * mathematical operators and returns the corresponding value. If the input parameter is not a mathematical operator,
 * the function returns 0.
 * @param op the operator whose precedence is to be determined
 * @Precedence_level:
 * 0 - not an operator
 * 1 - + or -
 * 2 - * or /
 * 3 - ^
 * @return an integer value representing the precedence of the operator
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-MediumCase θ(1)
 * @TimeComplexity-WorstCase θ(1)
 */
int get_precedence_both(char op) {   // function to get operator precedence
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else if (op == '^') {
        return 3;
    }
    else {
        return 0;
    }
}

/**
 * @brief function used to evaluate a postfix expression given as input
 * @details The function takes a postfix expression as input. It uses two data structures, a stack and a queue, to
 * evaluate the expression. It first initializes an empty stack and an empty queue. It also creates a stringstream
 * object called input that holds the postfix expression. The function then reads the postfix expression token by token
 * using the getline function. If the token is a digit, it is converted to an integer and it is pushed onto both the
 * operand_stack and the operand_queue using the push function. If the token is an operator, the two elements from the
 * operand_stack are popped and are assigned to the variables operand2 and operand1. A switch statement is then used to
 * check the operator stored in the token. The result is computed and it is pushed onto both the operand_stack and the
 * operand_queue. The function returns the result of the expression.
 * @param postfix the postfix expression to be evaluated
 * @return the result of the expression
 * @TimeComplexity-BestCase θ(n)
 * @TimeComplexity-MediumCase θ(n)
 * @TimeComplexity-WorstCase θ(n)
 */
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
                case '^':
                    result = pow(operand1, operand2);
                    break;
            }

            operand_stack.push(result);
            operand_queue.push(result);
        }
    }

    return operand_stack.pop();
}

/**
 * @brief Function used to convert an infix expression to a postfix expression
 * @details This function takes as input an expression in infix notation and then it converts it to postfix notation.
 * It uses two data structures, a stack and a queue and a stringstream to perform the shunting yard algorithm, It first
 * initializes an empty queue and an empty stack. Then the function getline is used to read each token of the infix
 * expression using the space as delimiter.  If the token is a digit, it is then appended to the output string, it is
 * converted to an integer and it is pushed onto the postfix_queue. If the token is a left parenthesis, it is pushed
 * onto the stack. If the token is a right parenthesis, all the operators are popped from the operator_stack and are
 * appended to the output string until a matching opening parenthesis is found. Then the opening parenthesis are popped
 * from the stack. If the token is an operator, the function will pop operators from the stack and add them to the string
 * stream until an operator with lower precedence is found and then it pushes the operator onto the stack.
 * After it reads all the token, it pops the remaining operators from the stack and adds them to the stringstream output
 * and queue. The function returns the output string.
 * @param infix the infix expression to be converted
 * @return the postfix expression
 * @TimeComplexity-BestCase θ(n)
 * @TimeComplexity-MediumCase θ(n)
 * @TimeComplexity-WorstCase θ(n)
 * @note To analyze the time complexity, we can observe that each token will be read once and each operand or operator
 * will be pushed or pooped once. There are constant operations executed with every token, and then the time complexity
 * is θ(n).
 */
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