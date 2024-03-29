#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

struct Node {
    TComp info;
    Node* parent;
    Node* left;
    Node* right;
    int nrLeftElements;
};

class SortedIndexedList {
private:
	friend class ListIterator;
private:
	//TODO - Representation

    Node* root;
    Relation r;
    int sizeTree;

public:
	// constructor
	SortedIndexedList(Relation r);

	// returns the size of the list
	int size() const;

	//checks if the list is empty
	bool isEmpty() const;

	// returns an element from a position
	//throws exception if the position is not valid
	TComp getElement(int pos) const;

	// adds an element to a given position
	//throws an exception if the position is not valid
	void add(TComp e);

	// removes an element from a given position
	//returns the removed element
	//throws an exception if the position is not valid
	TComp remove(int pos);

	// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
	int search(TComp e) const;

	// returns an iterator set to the first element of the list or invalid if the list is empty
	ListIterator iterator();

	//destructor
	~SortedIndexedList();

    Node *findMin(Node *node) const;

    void destroyTree(Node *node);

    void updateNrLeftElements(Node *node);

    void printTree(Node *node, int level) const;


    void printDebugInfo() const;

    void printSortedList() const;

    Node *getSuccessor(Node *node) const;

    Node *getParent(Node *node) const;

    void updateNrLeftElementsSubtree(Node *node);

    Node *getPredecessor(Node *node) const;

    static Node *findMax(Node *node) ;

    void decrease(int i) const;

    TComp successor(TComp e);

    TComp parentOfNode(TComp e);

    //function that checks if two sorted indexed lists are the same
    bool equals(SortedIndexedList& list);

    //Another implementation that checks if two sorted indexed lists are the same using the assignment operator overloaded  ==


    bool isEqual(Node *node1, Node *node2);
};
