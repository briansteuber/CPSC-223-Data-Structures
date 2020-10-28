/*
Brian Steuber
CPSC 223-01
HW6
This linked_list_collection.h file implements
the abstract class in collection.h.
This assignment was focused on insertion,
merge, and quick sort.
*/

#ifndef LINKED_LIST_COLLECTION_H
#define LINKED_LIST_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"

using namespace std;

template<typename K, typename V>
class LinkedListCollection : public Collection<K,V>
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
  
  // return all keys in the collection 
  void keys(vector<K>& keys) const;
  
  // return collection keys in sorted order
  void sort(vector<K>& keys) const;
  
  // return the number of keys in the collection
  int size() const;
  
  // function to print keys 
  void print() const;
  
  // in place sorting
  void insertion_sort();
  void merge_sort();
  void quick_sort();

private:

  // linked list node structure 
  struct Node {
    K key;
	V value;
	Node* next;
  };
  Node* head;
  Node* tail;
  int length;
  
  // helper to delete linked list
  void make_empty();
  
  // merge sort helper (see course notes for details)
  Node* merge_sort(Node* left, int len);
  
  // quick sort helper (see course notes for details)
  Node* quick_sort(Node* start, int len);
  
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
	insert(ptr->key, ptr->value);
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
    insert(ptr->key, ptr->value);
	ptr = ptr->next;
  }	
  insert(ptr->key, ptr->value);
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
  ptr->key = key;
  ptr->value = val;
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
  if (size() > 0)
  {	  
    Node* ptr = head;
    Node* cur = head->next;
    if (head->key == key) // head edgecase
    {
	  head = head->next;
	  delete ptr;
	  ptr = nullptr;
	  length--;
	  return;
    }
    else
    {
	  while (cur != nullptr)
	  {
	    if (cur->key == key)
	    {
		  if (cur->next = nullptr) // tail edgecase
		    tail = ptr;
	      ptr->next = cur->next;
		  delete cur;
		  cur = nullptr;
		  cur = nullptr;
		  length--;
		  break;
	    }
	    ptr = cur;
	    cur = cur->next;
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
    if (ptr->key == key)
	{
      val = ptr->value;
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
	if (ptr->key >= k1 && ptr->key <= k2)
    {		
	  keys.push_back(ptr->key);
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
	keys.push_back(ptr->key);
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
	keys.push_back(ptr->key);
	ptr = ptr->next;
  }
  std::sort(keys.begin(), keys.end());
}

// return the number of keys in collection
template <typename K, typename V>
int LinkedListCollection<K,V>::size() const
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

// sorts a linked list using insertion sort
template <typename K, typename V>
void LinkedListCollection<K,V>::insertion_sort()
{
  Node* cur = head;
  Node* sorted = head;
  for (int i = 1; i < length; i++) // traverse
  {
    bool move = false;
    sorted = head;
    while (!move && cur->next != sorted) // traverse 
	{
      move = false;
      if (cur->next->key < head->key) // comparison
	  {
        Node* tmp = cur->next;
        cur->next = cur->next->next;
        tmp->next = head;
		head = tmp;
		move = true;
	  }
	  else if (cur->next->key < sorted->next->key) // comparison 
	  {
		Node* tmp = cur->next;
		cur->next = cur->next->next;
		tmp->next = sorted->next;
		sorted->next = tmp;
		move = true;
	  }
	  else 
		sorted = sorted->next;
	}
	if (!move)
	  cur = cur->next;
  }     		
}

// merge sort function 
template <typename K, typename V>
void LinkedListCollection<K,V>::merge_sort()
{
  head = merge_sort(head, length); // call to helper
  tail = head;
  while (tail->next != nullptr) // traverse
  {
	tail = tail->next;
  }
}
 
// helper function for merge sort 
template <typename K, typename V>
typename LinkedListCollection<K,V>::Node*
LinkedListCollection<K,V>::merge_sort(Node* left, int len)
{
  if (len == 1) // base case
	return left;
  Node* cur = left;
  int mid = len/2; // mid
  int i = 0;
  while (i < mid-1) // left 
  {
	cur = cur->next;
	i++;
  }
  Node* right = cur->next;
  cur->next = nullptr;
  
  left = merge_sort(left, mid); // recursive call to left
  right = merge_sort(right, len-mid); // recursive call to right
  Node* first;
  
  if (left->key < right->key) // left < right comparison
  {
	first = left;
	left = left->next;
	first->next = nullptr;
  }
  else // left > right comparison
  {
	first = right;
	right = right->next;
	first->next = nullptr;
  }
  cur = first;
  for (int j = 0; j < len-1; j++) // traverse
  {
	if (left == nullptr) // left edgecase
	{
	  cur->next = right;
	  right = right->next;
	  cur->next->next = nullptr;
	  cur = cur->next;
	}
	else if (right == nullptr) // right edgecase
	{
	  cur->next = left;
	  left = left->next;
	  cur->next->next = nullptr;
	  cur = cur->next;
	}
	else if (left->key < right->key) // comparison
	{
      cur->next = left;
      left = left->next;
      cur->next->next = nullptr;
      cur = cur->next;
	}
    else // other comparison
	{
      cur->next = right;
      right = right->next;
      cur->next->next = nullptr;
      cur = cur->next;
	}
  }
  return first;  
}
	  
// quick sort function 
template <typename K, typename V>
void LinkedListCollection<K,V>::quick_sort()
{
  head = quick_sort(head,length); // call to helper
  tail = head;
  while (tail->next != nullptr) // traverse
  {
	tail = tail->next;
  }
}

// helper function for quick sort
template <typename K, typename V>
typename LinkedListCollection<K,V>::Node*
LinkedListCollection<K,V>::quick_sort(Node* start, int len)
{ 
  if (len == 1) // case if there is len is 1 
    return start;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* cur = start->next;
  while (cur != nullptr) // traverse
  {
	if (cur->key < start->key && left == nullptr) // edgecase
	  left = cur;
	if (cur->key >= start->key && right == nullptr) // edgecase  
	  right = cur;
	cur = cur->next;
  }
  cur = start->next;
  start->next = nullptr;
  Node* left_end = left;
  Node* right_end = right;
  while (cur != nullptr) // traverse
  {
	if (left != nullptr) //traverse left
	{
	  if (cur->key < start->key && cur != left) // comparison
	  {
		left_end->next = cur;
		left_end = left_end->next;
	  }
	}
	if (right != nullptr) // traverse right
	{
	  if (cur->key >= start->key && cur != right) // other comparison
	  {
		right_end->next = cur;
		right_end = right_end->next;
	  }
	}
	cur = cur->next;
  }
  if (left_end != nullptr)
	left_end->next = nullptr;
  if (right_end != nullptr)
	right_end->next = nullptr;
  cur = left;
  int left_len = 0;
  if (left != nullptr) // makes sure left isn't empty
  {
	while (cur != nullptr) // traverse 
	{
	  left_len++;
	  cur = cur->next;
	}
  }
  cur = right;
  int right_len = 0;
  if (right != nullptr) // makes sure right isn't empty
  {
	while (cur != nullptr) // traverse
	{	
	  right_len++;
	  cur = cur->next;
	}
  }
  if (left != nullptr) // makes sure left isn't empty
	left = quick_sort(left, left_len); // recursive call to left
  if (right != nullptr) // makes sure right isn't empty
	right = quick_sort(right, right_len);  // recursive call to right
  if (left != nullptr) // makes sure left isn't empty
  {
	cur = left;
	while (cur->next != nullptr) // traverse until end is reached
		cur = cur->next;
	left_end = cur;	
	left_end->next = start;
	start->next = right;
	return left;
  }
  if (left == nullptr) // edgecase
  {
	start->next = right;
	return start;
  }
}

// function to print keys 
template <typename K, typename V>
void LinkedListCollection<K,V>::print() const
{
  Node* cur = head;
  if (cur == nullptr) // empty
  {
	cout << "Null" << endl;
    return;
  }
  while (cur != nullptr) // traverse
  {
	cout << cur->key << endl;
	cur = cur->next;
  }
}
 
#endif