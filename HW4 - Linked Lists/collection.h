/*
Brian Steuber
CPSC 223-01
HW4
This collection.h file declares an 
abstract class. This h file is 
implemented in linked_list_collection.h
*/

#ifndef COLLECTION_H
#define COLLECTION_H

#include <vector>

using namespace std;

template<typename K, typename V>
class Collection
{
  public:
  /*
  // create an empty linked list
  virtual LinkedListCollection() = 0;
  
  // copy a linked list
  virtual LinkedListCollection(const LinkedListCollection<K,V> rhs) = 0;
  
  // assign a linked list
  virtual LinkedListCollection<K,V>& operator=(const LinkedListCollection<K,V>& rhs) = 0;
  
  // delete a linked list
  virtual ~LinkedListCollection() = 0;
  */
  // insert a key-value pair into the collection
  virtual void insert(const K& key, const V& val) = 0;
  
  // remove a key-value pair from the collection
  virtual void remove(const K& key) = 0;
  
  // find the value associated with the key
  virtual bool find(const K& key, V& val) const = 0;
  
  // find the keys associated with the range 
  virtual void find(const K& k1, const K& k2, vector<K>& keys) const = 0;
  
  // return all the keys in the collection
  virtual void keys(vector<K>& keys) const = 0;
  
  // return collection keys in sorted order
  virtual void sort(vector<K>& keys) const = 0;
  
  // return the number of keys in collection
  virtual int size() = 0;
  
};

#endif