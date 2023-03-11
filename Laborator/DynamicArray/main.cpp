#include <iostream>
#include "Dynamic_Array.h"
#include "Dynamic_Array.cpp"

using namespace std;

int main() {

    DynamicArray<int> t;

    t.addToEnd(1);
    t.addToEnd(2);
    t.addToEnd(3);
    t.addToEnd(4);
    t.addToEnd(5);
//    t.addToEnd(6);
//    t.addToEnd(7);
//    t.addToEnd(8);
//    t.addToEnd(9);
//    t.addToEnd(10);
//    t.addToEnd(11);

    t.display();

    t.deleteFromEnd();

    t.display();

    t.addToPosition(1, 200);

    t.display();

    t.deleteFromPosition(1);

    t.display();

    return 0;
}
