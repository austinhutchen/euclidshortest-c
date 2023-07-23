// CPP program to implement hashing with chaining
#include "hash.hpp"
#include <iostream>

using namespace std;

node *HashTable::createNode(int key, node *next) {
  node *nw = new node;
  nw->key = key;
  nw->next = next;
  return nw;
}

HashTable::HashTable(int bsize) {
  this->tableSize = bsize;
  table = new node *[tableSize];
  for (int i = 0; i < bsize; i++)
    table[i] = nullptr;
}

// function to calculate hash function
unsigned int HashTable::hashFunction(int key) { return (key % tableSize); }

// TODO Complete this function
// function to search
node *HashTable::searchItem(int key) {
  // Compute the index by using the hash function
  int index = hashFunction(key);
  // TODO: Search the list at that specific index and return the node if found
  node *head = table[index];
  node *curr = head;
  while (curr != NULL) {
    if (curr->key == key) {
      return curr;
    }
    curr = curr->next;
  }
  return NULL;
}

// TODO Complete this function
// use the hash function on the key to get the index/slot
// create a new node with the key and insert it in the list
bool HashTable::insertItem(int key) {
    int pos=hashFunction(key);
    node* curr;
  if(!searchItem(key)){
   if(table[pos]!=NULL){
    //resolve chaining issue
    curr=table[pos];
    {
        while(curr->next!=NULL){
        curr=curr->next;
        }
            curr->next=createNode(key, NULL);
            return true;
    }
   }
   if(table[pos]==NULL){
    table[pos]=createNode(key, NULL);
    return true;
   }
  }
  else{
    cout << "duplicate entry" << key << endl;
    return false;
  }
}

// TODO Complete this function
//  function to display hash table
void HashTable::printTable() {
  for (int i = 0; i < tableSize; i++) {
    cout << i << "|| ";
    // TODO
    node *curr = table[i];
    while (curr != NULL) {
      cout << curr->key << " ";
      curr = curr->next;
    }
    cout << endl;
  }
}
