/*
Brian Steuber
CPSC 223-01
HW4
This linked_list_collection.h file implements
the abstract class in collection.h.
This file allows the hw4_tests.cpp to 
access the functions in order to test
difference cases for the key value 
data type being implemented by a linked list.  
*/

#ifndef LINKED_LIST_COLLECTION_H
#define LINKED_LIST_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"

using namespace std;

template <typename K, typename V>
class LinkedListCollection : public Collection <K,V>
{
public:
  
  // create an empty linked list
  LinkedListCollection();
  
  // copy a linked list
  LinkedListCollection(const LinkedListCollection<K,V>& rhs);
  
  // assign a linked list
  LinkedListCollection<K,V>& operator=(const LinkedListCollection<K,V>& rhs);
  
  // delete a linked list
  ~LinkedListCollection();
  
  // insert a key-value pair into the collection
  void insert(const K& key, const V& val);
  
  // remove a key-value pair from the collection
  void remove(const K& key);
  
  // find the value associated with the key
  bool find(const K& key, V& val) const;
  
  // find the keys associated with the range 
  void find(const K& k1, const K& k2, vector<K>& keys) const;
  
  // return all the keys in the collection
  void keys(vector<K>& keys) const;
  
  // return collection keys in sorted order
  void sort(vector<K>& keys) const;
  
  // return the number of keys in collection
  int size();
  
  // deletes all nodes in the list
  void make_empty();
  
private:

  struct Node
  {
    	K the_key;
	V the_value;
	Node* next;
  };
  Node* head;
  Node* tail;
  int length;
};

// create an empty linked list
template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection()
{
  head = nullptr;
  tail = nullptr;
  length = 0; 
}

// copy a linked list
template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection(const LinkedListCollection<K,V>& rhs)
{
  head = nullptr;
  tail = nullptr;
  length = 0;
  Node* ptr = rhs.head;
  while (ptr != nullptr)
  {
	insert(ptr->the_key, ptr->the_value);
	ptr = ptr->next;
  }
  tail = ptr;
  ptr = nullptr;
}

// assign a linked list
template <typename K, typename V>
LinkedListCollection<K,V>& LinkedListCollection<K,V>::operator=(const LinkedListCollection<K,V>& rhs)
{
  make_empty();
  head = nullptr;
  tail = nullptr;
  length = 0;
  Node* ptr = rhs.head;
  while (ptr->next != nullptr)
  { 
    insert(ptr->the_key, ptr->the_value);
	ptr = ptr->next;
  }	
  insert(ptr->the_key, ptr->the_value);
  tail = ptr;
  tail->next = nullptr;
  ptr = nullptr;
  return *this;
}

// delete a linked list
template <typename K, typename V>
LinkedListCollection<K,V>::~LinkedListCollection()
{ 
  make_empty();
}

// insert a key-value pair into the collection
template <typename K, typename V>
void LinkedListCollection<K,V>::insert(const K& key, const V& val)
{
  Node* ptr = new Node;
  ptr->the_key = key;
  ptr->the_value = val;
  ptr->next = nullptr;
  if (length > 0)
  {
	tail->next = ptr;
	tail = ptr;
  }
  else 
  {
	head = ptr;
	head->next = nullptr;
    	tail = ptr;
  } 
  length++;
  tail->next = nullptr;
}

// remove a key-value pair from the collection
template <typename K, typename V>	
void LinkedListCollection<K,V>::remove(const K& key)
{
  Node* ptr = new Node;
  ptr = head;
  if (ptr->the_key == key)
  {
	head = ptr->next;
	delete ptr;
	length--;
	return;
  }
  else
  {
	for (int i = 0; i < length - 1; i++)
	{
	  if (ptr->next->the_key == key)
	  {
	        if (ptr->next == tail)
		  ptr->next = nullptr;
		else 
		{
	      	  delete ptr->next;
		  ptr->next= ptr->next->next;
		}
	    length--;
	  }
    }
  }
}

// find the value associated with the key
template <typename K, typename V>	
bool LinkedListCollection<K,V>::find(const K& key, V& val) const
{
  Node* ptr = head;	
  while(ptr != nullptr)
  {
    if (ptr->the_key == key)
	{
      val = ptr->the_value;
	  return true;
	}
	ptr = ptr->next;
  }
  return false;
}

// find the keys associated with the range
template <typename K, typename V>	
void LinkedListCollection<K,V>::find(const K& k1, const K& k2, vector<K>& keys) const
{
  Node* ptr = head;
  while(ptr != nullptr)
  {
	if (ptr->the_key >= k1 && ptr->the_key <= k2)
    {		
	  keys.push_back(ptr->the_key);
    }
	ptr = ptr->next;
  }
}

// return all the keys in the collection
template <typename K, typename V>	
void LinkedListCollection<K,V>::keys(vector<K>& keys) const
{
  Node* ptr = head;	
  while(ptr != nullptr)
  {
	keys.push_back(ptr->the_key);
	ptr = ptr->next;
  }
}

// return collection keys in sorted order
template <typename K, typename V>
void LinkedListCollection<K,V>::sort(vector<K>& keys) const
{
  Node* ptr = head;
  while(ptr != nullptr)
  {
	keys.push_back(ptr->the_key);
	ptr = ptr->next;
  }
  std::sort(keys.begin(), keys.end());
}

// return the number of keys in collection
template <typename K, typename V>
int LinkedListCollection<K,V>::size()
{	
  return length;
}

// deletes all nodes in the list
template <typename K, typename V>
void LinkedListCollection<K,V>::make_empty()
{
  Node* ptr = new Node;
  ptr = head;  
  if (ptr == nullptr)
  {
	return;
  }
  while (ptr != nullptr)
  {
	Node* cur = ptr->next;
	delete ptr;
	ptr = cur;
	length--;
  }
  head = nullptr;
  tail = nullptr;
}

#endif


