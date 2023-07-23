#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP
#include <iostream>

struct Node{
      int key;
      Node *next;
};

class LinkedList
{
  private:
    Node *head;

  public:
    LinkedList(){
    	head = NULL;
    }
    ~LinkedList();
    void insert(Node *prev, int newKey);
    Node* searchList(int key);
    void printList();
    bool deleteAtIndex(int n);
};

#endif
