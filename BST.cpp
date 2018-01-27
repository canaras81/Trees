/******************************************************************************
Created and tested on GDB Online.
*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <list>
#include <stack>

using namespace std;

struct Node{
    int val;
    Node *left;
    Node *right;
    int level;
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
        int lowestCommonAncestor(int val1, int val2);
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
    cout << endl;
}

int Tree::lowestCommonAncestor(int val1, int val2)
{
    stack<int> n1_path;
    stack<int> n2_path;
    stack<int> temp_stack;
    
    // find path to val1
    Node *compare = top;
    int compare_val = compare->val;
    while(compare_val != val1)
    {
        n1_path.push(compare_val);
        if(val1 < compare_val)
            compare = compare->left;
        else if(val1 > compare_val)
            compare = compare->right;
        compare_val = compare->val;
    }
    n1_path.push(val1);
    
    // find path to val2
    compare = top;
    compare_val = compare->val;
    while(compare_val != val2)
    {
        n2_path.push(compare_val);
        if(val2 < compare_val)
            compare = compare->left;
        else if(val2 > compare_val)
            compare = compare->right;
        compare_val = compare->val;
    }
    n2_path.push(val2);
    
    // print path from val1 to top
    /*
    while(!n1_path.empty())
    {
        cout << n1_path.top() << " ";
        temp_stack.push(n1_path.top());
        n1_path.pop();
    }
    cout << endl;
    while(!temp_stack.empty())
    {
        n1_path.push(temp_stack.top());
        temp_stack.pop();
    }
    
    // print path from val2 to top
    while(!n2_path.empty())
    {
        cout << n2_path.top() << " ";
        temp_stack.push(n2_path.top());
        n2_path.pop();
    }
    cout << endl;
    while(!temp_stack.empty())
    {
        n2_path.push(temp_stack.top());
        temp_stack.pop();
    }*/
    
    while(!n1_path.empty())
    {
        int n1_val = n1_path.top();
        //cout << n1_val << endl;
        n1_path.pop();
        while(!n2_path.empty())
        {
            int n2_val = n2_path.top();
            n2_path.pop();
            temp_stack.push(n2_val);
            if(n1_val == n2_val)
            {
                cout << "found LCA! " << n1_val << endl;
                return n1_val;
            }
        }
        
        while(!temp_stack.empty())
        {
            n2_path.push(temp_stack.top());
            temp_stack.pop();
        }
    }
    
    return 0;
}

int main()
{
    //printf("Hello World");
    Tree BST;
    int arr_size = 19;
    int arr[arr_size] = {10,5,15,3,8,2,4,7,9,18,13,17,19,12,14,11,16,6,1};
    BST.constructTree(arr, arr_size);
    BST.printInOrder();
    BST.lowestCommonAncestor(6,9); //8
    BST.lowestCommonAncestor(11,9); //10
    BST.lowestCommonAncestor(11,10); //10
    BST.lowestCommonAncestor(12,15); //15
    BST.lowestCommonAncestor(5,6); //5
    BST.lowestCommonAncestor(1,1); //1
    BST.lowestCommonAncestor(1,18); //10
    
    return 0;
}
