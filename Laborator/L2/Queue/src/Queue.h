#pragma once
#include <vector>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

struct QNode {
    TElem info;
    QNode* next;
};

class Queue
{
private:
    QNode* head;
    QNode* tail;
public:
	Queue();

	//pushes an element to the end of the queue
	void push(TElem e);

	//returns the element from the front of the queue
	//throws exception if the queue is empty
	[[nodiscard]] TElem top() const;

	//removes and returns the element from the front of the queue
	//throws exception if the queue is empty
	TElem pop();

	//checks if the queue is empty
	[[nodiscard]] bool isEmpty() const;

	// destructor
	~Queue();
};
