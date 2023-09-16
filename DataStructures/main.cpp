//#include <iostream>
//#include "LinkedList/SLL/SLL.h"
//#include "LinkedList/SLL/SLL_Iterator.h"
//
//using std::cout;
//
//int main() {
//
//    SLL list1;
//    list1.addFirst(1);
//    list1.addFirst(2);
//    list1.addFirst(3);
//    list1.addFirst(4);
//
//    SLL list2;
//    list2.addFirst(1);
//    list2.addFirst(2);
//    list2.addFirst(3);
//    list2.addFirst(4);
//    list2.addFirst(5);
//
//    SLL mergedList;
//
//    mergedList.merge(list1, list2);
//
//    SLLIterator it = mergedList.getIterator();
//
//    cout << "Current element:";
//    while (it.valid()) {
//        cout << it.getCurrent() << " ";
//        it.next();
//    }
//
//
//
//    return 0;
//}

/**
* Map implemented with a hashtable with coalesced chaining
 *
 * Representierung:
 *
 * Element:
 *     Tkey key
 *     TValue value
 *
 * T : Element[]
 * next : Integer[]
 * firstEmpty : integer
 * capacity : integer
 * h : hash function
 *
 * Implementation:
 *
 * function add(Tkey key, TValue value)is
 *     position = h(key)
 *
 *     while T[position.first] != key and next[position] != -1 execute
 *         position = next[position]
 *     end-while
 *     if T[position.first] = key then
 *        T[position.second] <- value
 *        add<-T[position.second].value
 *
 *     else
 *         if firstEmpty == -1
 *             @resizeAndRehash()
 *
 *         T[firstEmpty.first] = key
 *         T[firstEmpty.second] = value
 *
 *         next[position] = firstEmpty
 *         firstEmpty = next[firstEmpty]
 *
 *         add<-NULL_TELEM
 *     end-if
 *
 *
 *     Specification:
 *     pre = key apartine TKey, value apartine TValue
 *     post: T' = T U <key, value>
 *
 *     Complexities:
 *     best case = theta(1) cand il gaseste pe pozitia initiala de hash si nu
 *                 trebuie parcurs lantul
 *     average case = Suma de P(i) * E(i) = theta(n)
 *     P(i) = 1/n+1
 *     E(i) = 1 + 2 + .... + n + n
 *     worst case = theta(n) cand parcuge tot chainul sau trebuie resize si rehash la tabel
*/


/**
 *
 * struct Node {
 *     Telem info,
 *     Node* next
 *     bool visited;
 *}
 *
* function getIntersection(Node* head1, Node* head2) {
 *     Node* temp = head1
 *     while(temp != NULL) {
 *         temp->visited = true
 *         temp = temp->next;
 *    }
 *
 *    temp1 = head2
 *
 *    while(temp1 != NULL) {
 *       if(temp1->visited)
 *           return temp1
 *       else
 *           temp1 -> visited = true
 *       temp1 = temp1->next
 *    }
 * }
*/

/**
* function infixToPostfix(infix)
 *    infix: sll
 *    output: string
 *    input: string
 *    operator_stack: Stack (SLL)
 *    postfix_queue: Queue
 *    token: string
 *    open_parentheses: int
 *    currentNode: *Node
 *
 *    current <-     head
 *    while(current != nullptr) execute
 *        if type(current->info) == 2
 *            output += current->info
 *            postfix_queue.push(current->info)
 *
 *        else if (type(current->info) == 3) then
 *            operator_stack.push(current->info)
 *            open_parentheses++
 *        else if(type(current->info) == 4) then
 *            if(--open_parentheses < 0)then
 *                @throw
 *
 *            while operator_stack.top() != '(' execute
 *                output += operator_stack.top()
 *                postfix_queue.push(output)
 *                operator_stack.pop()
 *            end-while
 *
 *            operator_stack.pop()
 *
 *        else then
 *            while(!operator_stack.isEmpty() && getPrecedence(current->info) <= getPrecedence(operator_stack.top()) execute
 *                output += operator_stack.top()
 *                postfix_queue.push(output)
 *                operator_stack.pop()
 *            end-while
 *            operator_stack.push(current->info)
 *        end-if
 *
 *        if(open_parentheses != 0)
 *            @throw
 *
 *        while(!operator_stack.isEmpty()) {
 *            output += operator_stack.top()
 *            postfix_queue(output)
 *            operator_stack.pop()
 *        end-while
 *
 *        infixToPostfix <- output
*/