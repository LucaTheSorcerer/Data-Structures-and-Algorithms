#include "ExtendedTest.h"
#include "ShortTest.h"

#include "Map.h"


#include <iostream>
using namespace std;


int main() {

	testAll();
//    testMapInterval();
	testAllExtended();
//    basicTest();


	cout << "That's all!" << endl;
	cin.get();
	return 0;
}


