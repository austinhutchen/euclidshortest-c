#include "ll.hpp"


using namespace std;

// Search for a specified key and return a pointer to that node
// MANDETORY_TODO: complete this function
// Given the key this function will find the node where the key is present
// If found it will return the node, else NULL
Node *LinkedList::searchList(int key) {
  Node *ptr = head;
  while (ptr != NULL && ptr->key != key) {
    ptr = ptr->next;
  }     
  return ptr;
}

void LinkedList::insert(Node *prev, int newKey) {
  // Check if head is Null i.e list is empty
  if (head == NULL) {
    head = new Node;
    head->key = newKey;
    head->next = NULL;
  }

  // if list is not empty, look for prev and append our node there, add to beginning of list and reassign head
  else if (prev == NULL) {
    Node *newNode = new Node;
    newNode->key = newKey;
    newNode->next = head;
    head = newNode;
  }

  else {
    Node *newNode = new Node;
    newNode->key = newKey;
    newNode->next = prev->next;
    prev->next = newNode;
  }
}

// Print the keys in your list
void LinkedList::printList() {
  Node *temp = head;
  if (temp == NULL) {
    return;
  }
  while (temp != NULL) {
    cout << temp->key << " -> ";
    temp = temp->next;
  }

}

// TODO: SILVER PROBLEM (mandetory)
// Delete node at a particular index
bool LinkedList::deleteAtIndex(int n) {
  bool isDeleted = false;
  Node *current = head;
  Node *prev;
  int counter = 0;
  if (head == NULL) {
    cout << "List is already empty" << endl;
    return isDeleted;
  }
  // Special case to delete the head
  if (n == 0) {
    head=current->next;
    delete current;
    isDeleted = true;
    return isDeleted;
  }
  while (current != NULL) {
    if (counter == n) {
      prev->next = current->next;
      delete current;
      isDeleted = true;
      return isDeleted;
    }
    prev = current;
    current = current->next;
    counter++;
  }
  return isDeleted;
}

// TODO:GOLD PROBLEM (optional)
LinkedList::~LinkedList() {
  // TODO
  Node *temp=head;
  if (temp == NULL) {
    cout << "network deleted" << endl;
    return;
  }
  while(head!=NULL){
    temp=head->next;
    delete head;
    head=temp;
  }

  cout << "network deleted" << endl;
}