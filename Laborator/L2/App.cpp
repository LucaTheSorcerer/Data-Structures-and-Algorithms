#include "Queue/test/ExtendedQueueTest.h"
#include "Queue/test/ShortQueueTest.h"
#include "Stack/test/ShortStackTest.h"
#include "Stack/test/ExtendedStackTest.h"
#include <iostream>

using namespace std;

int main() {

//	testAllQueue();
//	testAllExtendedQueue();
	testAllStack();
    //testAllExtendedStack();

	cout << "Test end" << endl;
    cin.get();
}