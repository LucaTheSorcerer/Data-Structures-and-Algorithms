#include "../Queue/test/ExtendedQueueTest.h"
#include "../Queue/test/ShortQueueTest.h"
#include "../Stack/test/ShortStackTest.h"
#include "../Stack/test/ExtendedStackTest.h"
#include "../Shunting_Yard/test/shunting_yard_test.h"
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

    cout << "Test end" << endl;
    cin.get();
}