/*
Brian Steuber
CPSC 223-01
HW7
This hash_table_collection.h file implements
the abstract class in collection.h.
*/

#ifndef HASH_TABLE_COLLECTION_H
#define HASH_TABLE_COLLECTION_H

#include <vector>
#include <algorithm>
#include <functional>
#include "collection.h"

using namespace std;

template <typename K, typename V>
class HashTableCollection : public Collection <K,V>
{
public:
  
  // create an empty linked list 
  HashTableCollection();

  // copy a linked list
  HashTableCollection(const HashTableCollection<K,V>& rhs);
 
  // assign a linked list 
  HashTableCollection<K,V>& operator=(const HashTableCollection<K,V>& rhs);
  
  // delete a linked list 
  ~HashTableCollection();
  
  // insert a key-value
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
  int size() const;
  
  // prints keys 
  void print() const;

private:

  // helper to empty entire hash table 
  void make_empty();
  
  // resize and rehash the hash table 
  void resize_and_rehash();

  // linked list node structure 
  struct Node {
    K key;
    V value;
    Node* next;
  };

  // number of k-v pairs in the collection
  int collection_size;

  // number of hash table buckets (default is 16)
  int table_capacity;

  // hash table array load factor (set at 75% for resizing)
  const double load_factor_threshold;

  // hash table array
  Node** hash_table;
};

// create an empty linked list 
template <typename K, typename V>
HashTableCollection<K,V>::HashTableCollection() :
  collection_size(0), table_capacity(16), load_factor_threshold(0.75)
{
  // dynamically allocate the hash table array 
  hash_table = new Node*[table_capacity];
  // initialize the hash table chains 
  for (int i = 0; i < table_capacity; ++i)
	hash_table[i] = nullptr;
}

// copy a linked list
template <typename K, typename V>
HashTableCollection<K,V>::HashTableCollection(const HashTableCollection<K,V>& rhs)
  : hash_table(nullptr)
{
  *this = rhs; 
}

// helper to empty entire hash table
template <typename K, typename V>
void HashTableCollection<K,V>::make_empty() 
{
  Node* tmp;
  Node* cpy;
  // make sure hash table exists 
  if (hash_table == nullptr)
    return;
  // remove each key
  for (int i = 0; i < table_capacity-1; i++)
  {
	if (nullptr != hash_table[i]) // traverse till end
	{
	  tmp = hash_table[i];
	  while(nullptr != tmp)
	  {
	    cpy = tmp->next;
		delete tmp;
		tmp = cpy;
		collection_size--;
	  }
	  hash_table[i] = nullptr;
	}
  }
  // remove the hash table 
  delete hash_table;
  hash_table = nullptr;
}

// delete a linked list
template <typename K, typename V>
HashTableCollection<K,V>::~HashTableCollection()
{
  make_empty(); // helper
}
	
// assign a linked list 
template <typename K, typename V>
HashTableCollection<K,V>&
HashTableCollection<K,V>::operator=(const HashTableCollection<K,V>& rhs)
{
  // check if rhs is current object and return current object 
  if (this == &rhs)
	return *this;
  // delete current object 
  make_empty(); 
  //initialize current object
  //create the hash table
  hash_table = new Node*[rhs.table_capacity];
  table_capacity = rhs.table_capacity;
  // do the copy 
  for(int i = 0; i < table_capacity-1; i++) // traverse
  {
	if (nullptr != rhs.hash_table[i]) // case 
	{
		while (nullptr != rhs.hash_table[i]) // traverse to end
		{
		  insert(rhs.hash_table[i]->key, rhs.hash_table[i]->value);
		  rhs.hash_table[i] = rhs.hash_table[i]->next;
		}
	}
  }
  return *this; 
}

// resize and rehash the hash table 
template<typename K, typename V> 
void HashTableCollection<K,V>::resize_and_rehash()
{
  // setup new table
  int new_capacity = table_capacity * 2;
  // ... similarly with collection size ...
  // dynamically allocate the new table 
  Node** new_table = new Node*[new_capacity];
  // initialize new table 
  for (int i = 0; i < new_capacity; ++i)
	  new_table[i] = nullptr;
  // insert key values
  vector<K> ks;
  keys(ks);
  for (K key : ks) 
  {
	// hash the key
	std::hash<K> hash_function;
	size_t hash = hash_function(key);
	size_t index = hash % new_capacity;
	// create a new node in new table
	Node* cur = new Node;
	V val;
	find(key, val);
	cur->key = key;
	cur->value = val;
	cur->next = new_table[index];
	new_table[index] = cur;
	collection_size++;
  }
  // clear the current data 
  make_empty();
  // update to the new settings
  hash_table = new_table;
  // ... update remaining vars ...
  table_capacity = new_capacity;
}

// insert a key-value
template<typename K, typename V>
void HashTableCollection<K,V>::insert(const K& key, const V& val)
{
  // check current load factor vs load factor threshold,
  // and resize and copy if necessary by calling resize_and_rehash()
  if(collection_size/table_capacity >= load_factor_threshold) //calculate
  {
	resize_and_rehash();
  }
  // hash the key
  std::hash<K> hash_function;
  size_t hash = hash_function(key);
  size_t index = hash % table_capacity;
  // create the new node 
  Node* cur = new Node;
  cur->key = key;
  cur->value = val;
  cur->next = hash_table[index];
  hash_table[index] = cur;
  // update the size 
  collection_size++;
}

// remove a key-value pair from the collection
template<typename K, typename V>
void HashTableCollection<K,V>::remove(const K& key)
{
  std::hash<K> hash_function;
  size_t hash = hash_function(key);
  size_t index = hash % table_capacity;
	
  if (hash_table[index] == nullptr) // empty 
    return;
  if (hash_table[index]->key == key) // found 
  {
	Node* tmp = hash_table[index];
	hash_table[index] = hash_table[index]->next;
	delete tmp;
	tmp = nullptr;
	collection_size--;
	return;
  }
  else
  {
	Node* cur = hash_table[index]->next;
	Node* prev = hash_table[index];
	while (cur != nullptr) // traverse till end
	{
      if (cur->key == key) // when key found 
	  {
		prev->next = cur->next;
		delete cur;
		cur = nullptr;
		collection_size--;
		return;
	  }
	  cur = cur->next;
	  prev = prev->next;
	}
  }
}

// find the value associated with the key 
template<typename K, typename V>
bool HashTableCollection<K,V>::find(const K& key, V& val) const
{
  std::hash<K> hash_function;
  size_t hash = hash_function(key);
  size_t index = hash % table_capacity;
	
  if (hash_table[index] == nullptr) // empty
	return false;
  Node* cur = hash_table[index];
  while (cur != nullptr) // traverse
  {
    if (cur->key == key) // found
	{
	  val = cur->value;
	  return true;
	}
	cur = cur->next;
  }
  return false;
}

// find the keys associated with the range 
template<typename K, typename V>
void HashTableCollection<K,V>::find(const K& k1, const K& k2, vector<K>& keys) const
{
  for (int i = 0; i < table_capacity-1; i++) // traverse
  {
    Node* cur = hash_table[i];
	while (cur != nullptr) // traverse till end
	{
	  if (cur->key >= k1 && cur->key <= k2)
		keys.push_back(cur->key);
	  cur = cur->next;
	}
  }
}

// return all the keys in the collection
template<typename K, typename V>
void HashTableCollection<K,V>::keys(vector<K>& keys) const
{
  for (int i = 0; i < table_capacity; i++) // traverse
  {
    Node* cur = hash_table[i];
	while (cur != nullptr) // traverse till end
	{
	  keys.push_back(cur->key);
	  cur = cur->next;
	}
  }
}

// return collection keys in sorted order
template<typename K, typename V>
void HashTableCollection<K,V>::sort(vector<K>& ks) const
{
  keys(ks);
  std::sort(ks.begin(), ks.end());
}

// return the number of keys in collection
template<typename K, typename V>
int HashTableCollection<K,V>::size() const
{
  return collection_size;
}

// prints keys 
template<typename K, typename V>
void HashTableCollection<K,V>::print() const
{
  for (int i = 0; i < table_capacity; i++) // traverse
  {
	Node* cur = hash_table[i];
	while (cur != nullptr) // traverse till end
	{
	  cout << cur->key << endl; 
	  cur = cur->next;
	}
  }
}

#endif