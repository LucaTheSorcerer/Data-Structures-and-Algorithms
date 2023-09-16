//
// Created by Luca Tudor on 07.07.2023.
//


#include <iostream>

using namespace std;

class PreNode {
public:
    PreNode* left;
    PreNode* right;
    char data;
};

int search(char arr[], int strt, int end, char value);
PreNode* newNode(char data);


PreNode* buildTree(char in[], char pre[], int inStrt, int inEnd) {

    static int preIndex = 0;

    if(inStrt > inEnd) {
        return nullptr;
    }

    PreNode* tNode = newNode(pre[preIndex++]);

    if(inStrt == inEnd)
        return tNode;

    int inIndex = search(in, inStrt, inEnd, tNode->data);

    tNode->left = buildTree(in, pre, inStrt, inIndex-1);
    tNode->right = buildTree(in, pre, inIndex+1, inEnd);

    return tNode;

}

int search(char arr[], int strt, int end, char value) {

    for(int i = strt; i <= end; i++) {
        if(arr[i] == value)
            return i;
    }
}

PreNode* newNode(char data) {
    PreNode* Node = new PreNode();
    Node->data = data;
    Node->left = nullptr;
    Node->right = nullptr;

    return (Node);
}

void printInorder(PreNode* node) {
    if(node == nullptr)
        return;

    printInorder(node->left);

    cout << node->data << " ";

    printInorder(node->right);
}

int main()
{
    char in[] = { 'D', 'B', 'E', 'A', 'F', 'C' };
    char pre[] = { 'A', 'B', 'D', 'E', 'C', 'F' };
    int len = sizeof(in) / sizeof(in[0]);
    PreNode* root = buildTree(in, pre, 0, len - 1);

    /* Let us test the built tree by
    printing Inorder traversal */
    cout << "Inorder traversal of the constructed tree is \n";
    printInorder(root);
}