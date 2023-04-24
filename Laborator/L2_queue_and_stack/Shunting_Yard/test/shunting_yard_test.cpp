//
// Created by Luca Tudor on 15.04.2023.
//

#include "../src/shunting_yard.h"
#include "shunting_yard_test.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

void test_shunting_yard_small() {
    cout << "Test shunting yard smaller expression" << endl;
    string infix = "( 2 + 3 ) * 4"; // 2 3 + 4 *
    string postfix = infix_to_postfix_conversion(infix);
    int result = evaluate_postfix(postfix);
    assert(infix == "( 2 + 3 ) * 4");
    assert(postfix == "2 3 + 4 * ");
    assert(result == 20);
    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Result: " << result << endl;
}

void test_shunting_yard_bigger() {
    cout << "Test shunting yard longer expression" << endl;
    string infix = "( 2 + 3 ) * 4 + 5 * 6";
    string postfix = infix_to_postfix_conversion(infix);
    int result = evaluate_postfix(postfix);
    assert(infix == "( 2 + 3 ) * 4 + 5 * 6");
    assert(postfix == "2 3 + 4 * 5 6 * + ");
    assert(result == 50);
    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Result: " << result << endl;
}

void test_shunting_yard_even_bigger() {
    cout << "Test shunting yard even longer expression" << endl;
    string infix = "( 2 + 3 ) * 4 + 5 * 6 - 7 * 8 + 9 * 10";
    string postfix = infix_to_postfix_conversion(infix);
    int result = evaluate_postfix(postfix);
    assert(infix == "( 2 + 3 ) * 4 + 5 * 6 - 7 * 8 + 9 * 10");
    assert(postfix == "2 3 + 4 * 5 6 * + 7 8 * - 9 10 * + ");
    assert(result == 84);
    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Result: " << result << endl;
}