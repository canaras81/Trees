/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, HTML, CSS, JS.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <list>

using namespace std;

struct Node{
    int val;
    Node *left;
    Node *right;
};

class Tree
{
    private:
        Node *top;
        Node *createNode(int val);
        void addNodeInternal(int node_val, Node **top);
        void printInOrderInternal(Node *top);
    public:
        Tree();
        void constructTree(int arr[], int arr_size);
        void addNode(int node_val);
        void printInOrder();
};

// private member methods
Node* Tree::createNode(int val)
{
    Node *node = new Node();
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void Tree::addNodeInternal(int node_val, Node **top)
{
    Node *temp = *top;
    
    if(temp == NULL)
    {
        *top = createNode(node_val);
        return;
    }
    
    if(node_val < temp->val)
    {
        if(temp->left != NULL)
            addNodeInternal(node_val, &(temp->left));
        else
        {
            Node *new_node = createNode(node_val);
            temp -> left = new_node;
            return;
        }
    }
    if(node_val > temp->val) 
    {
        if(temp->right != NULL)
            addNodeInternal(node_val, &(temp->right));
        else
        {
            Node *new_node = createNode(node_val);
            temp -> right = new_node;
            return;
        }
    }
    else if(node_val == temp->val)
    {
        cout << "Discarding duplicate " << node_val << endl;
    }
}

void Tree::printInOrderInternal(Node *node)
{
    if(node == NULL)
        return;
    printInOrderInternal(node->left);
    cout << node->val << " ";
    printInOrderInternal(node->right);
    return;
}

// public member methods
Tree::Tree()
{
    cout << "constructing" << endl;
    top = NULL;
}

void Tree::constructTree(int arr[], int arr_size)
{
    for(int i=0; i<arr_size; i++)
        this->addNode(arr[i]);
}

void Tree::addNode(int node_val)
{
    addNodeInternal(node_val, &(this->top));
}

void Tree::printInOrder()
{
    printInOrderInternal(top);
}

/*
Node *Tree::lowestCommonAncestor(Node *n1, Node *n2)
{
    std::list<int> n1_path;
    
}
*/

int main()
{
    //printf("Hello World");
    Tree BST;
    int arr_size = 19;
    int arr[arr_size] = {10,5,15,3,8,2,4,7,9,18,13,17,19,12,14,11,16,6,1};
    BST.constructTree(arr, arr_size);
    BST.printInOrder();
    
    return 0;
}
