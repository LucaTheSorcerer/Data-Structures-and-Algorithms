//
// Created by Luca Tudor on 24.04.2023.
//

#include "/Users/lulu/UBB/Semestrul_II/Data-Structures-and-Algorithms/Laborator/L2_queue_and_stack/Shunting_Yard_With_Both/test/shunting_yard_with_both_test.h"
#include "/Users/lulu/UBB/Semestrul_II/Data-Structures-and-Algorithms/Laborator/L2_queue_and_stack/Shunting_Yard_With_Both/src/shunting_yard_with_both.h"
#include "/Users/lulu/UBB/Semestrul_II/Data-Structures-and-Algorithms/Laborator/L2_queue_and_stack/Stack/src/stack.h"
#include "/Users/lulu/UBB/Semestrul_II/Data-Structures-and-Algorithms/Laborator/L2_queue_and_stack/Queue/src/queue.h"

#include <iostream>

using namespace std;

void test_shunting_yard_small_with_both() {
    cout << "Test shunting yard smaller expression with both queue and stack" << endl;
    string infix = "( 2 + 3 ) * 4"; // 2 3 + 4 *
    string postfix = infix_to_postfix_conversion_both(infix);
    int result = evaluate_postfix_both(postfix);
    assert(infix == "( 2 + 3 ) * 4");
    assert(postfix == "2 3 + 4 * ");
    assert(result == 20);
    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Result: " << result << endl;
}

void test_shunting_yard_bigger_with_both() {
    cout << "Test shunting yard longer expression with both queue and stack" << endl;
    string infix = "( 2 + 3 ) * 4 + 5 * 6";
    string postfix = infix_to_postfix_conversion_both(infix);
    int result = evaluate_postfix_both(postfix);
    assert(infix == "( 2 + 3 ) * 4 + 5 * 6");
    assert(postfix == "2 3 + 4 * 5 6 * + ");
    assert(result == 50);
    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Result: " << result << endl;
}

void test_shunting_yard_even_bigger_with_both() {
    cout << "Test shunting yard even longer expression with both queue and stack" << endl;
    string infix = "( 2 + 3 ) * 4 + 5 * 6 - 7 * 8 + 9 * 10";
    string postfix = infix_to_postfix_conversion_both(infix);
    int result = evaluate_postfix_both(postfix);
    assert(infix == "( 2 + 3 ) * 4 + 5 * 6 - 7 * 8 + 9 * 10");
    assert(postfix == "2 3 + 4 * 5 6 * + 7 8 * - 9 10 * + ");
    assert(result == 84);
    cout << "Infix: " << infix << endl;
    cout << "Postfix: " << postfix << endl;
    cout << "Result: " << result << endl;
}

