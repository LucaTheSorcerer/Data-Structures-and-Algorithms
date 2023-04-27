#include "../Queue/test/ExtendedQueueTest.h"
#include "../Queue/test/ShortQueueTest.h"
#include "../Stack/test/ShortStackTest.h"
#include "../Stack/test/ExtendedStackTest.h"
#include "../Shunting_Yard/test/shunting_yard_test.h"
#include "/Users/lulu/UBB/Semestrul_II/Data-Structures-and-Algorithms/Laborator/L2_queue_and_stack/Shunting_Yard_With_Both/test/shunting_yard_with_both_test.h"
#include <iostream>

using namespace std;

int main() {

    cout << "Test start" << endl;
	testAllQueue();
	testAllExtendedQueue();
	testAllStack();
    testAllExtendedStack();
    test_shunting_yard_small();
    test_shunting_yard_bigger();
    test_shunting_yard_even_bigger();
    test_shunting_yard_small_with_both();
    test_shunting_yard_bigger_with_both();
    test_shunting_yard_even_bigger_with_both();
    test_shunting_yard_with_both_all_operations();
    test_shunting_yard_with_both_all_operations_bigger();
    test_shunting_yard_with_both_mismatched_parentheses();
    cout << "Test end" << endl;
    cin.get();
}