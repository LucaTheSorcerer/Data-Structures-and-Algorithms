
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;


int main() {


	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	//system("pause"); This does not work for macos. It is only supported by Windows
    //We use std::cin.get() instead to get the same result
    std::cin.get();
}