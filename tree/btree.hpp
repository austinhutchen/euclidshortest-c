#pragma ONCE
#include <stack>
using namespace std;

struct Node{
    int key;
    Node* left ;
    Node* right;
};

class BST{
    private:
        Node* root;
        Node* createNode(int data);
        /** since root is a private member we need helper functions
         to access root for insertion, searching and printing.
         These helper functions is used for performing recursion **/
        void traverse(Node* root, std::stack<int> &st);
        bool isSameTree(Node *p, Node *q);
        Node* addNodeHelper(Node*, int);
        bool isomorphic(std::stack<int> n1, std::stack<int> n2);
        void printTreeHelper(Node*);
        void print2DUtilHelper(Node *, int);

        Node* searchKeyHelper(Node*, int);

        Node* kthSmallestHelper(Node* currNode, int* counter, int k);
        void destroyNode(Node *root);

    public:
        Node* getRoot();                // Returns the root of the tree;
        void addNode(int);              // function to insert a node in the tree.
        bool searchKey(int);            // function to search a data in the tree
        void printTree();               //function to print the tree
        BST();                          // default constructor
        BST(int data);                  // parameterized constructor
        ~BST();                         // destructor
        
        void print2DUtil(int);
        
        
        Node* findKthSmallest(int k);
    
        void rangePrint(int k1,int k2);

};

