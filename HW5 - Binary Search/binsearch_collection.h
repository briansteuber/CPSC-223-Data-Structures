/*
Brian Steuber
CPSC 223-01
HW5
This binsearch_collection.h file implements
the abstract class in collection.h.
This file allows the hw5_tests.cpp to 
access the functions in order to test
difference cases for the key value 
data type.
*/

#ifndef BINSEARCH_COLLECTION_H
#define BINSEARCH_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"

using namespace std;

template <typename K, typename V>
class BinSearchCollection : public Collection<K,V>
{
public:

  //insert a key-value pair into the collection
  void insert(const K& key, const V& val);
  
  //remove a key-value pair from the collection
  void remove(const K& key);
  
  //find and return the value associated with the key
  bool find(const K& key, V& val) const;
  
  //find and return the list of keys >= to k1 and <= to k2
  void find(const K& k1, const K& k2, vector<K>& keys) const;
  
  //return all of the keys in the collection
  void keys(vector<K>& keys) const;
  
  //return all of the keys in ascending (sorted) order
  void sort(vector<K>& keys) const;
  
  //return the number of keys in collection
  int size() const;
  
private:

  //helper function for binary search
  bool binsearch(const K& key, int& index) const;
  
  //vector storage
  vector<pair<K,V>> kv_list;
  
};

//insert a key-value pair into the collection
template<typename K,typename V>
void BinSearchCollection<K,V>::insert(const K& key, const V& val)
{
  int pos;
  pair<K,V> p(key,val); // creates a key value pair p with key and val as parameters
  if (kv_list.size() == 0)
  {
	kv_list.push_back(p); // pushes back
  }
  else 
  {
	pos = -1; // number that cannot be a possible index
	this->binsearch(key,pos); // calls binsearch
    kv_list.insert(kv_list.begin() + pos, p); // inserts 
  }
}

//remove a key-value pair from the collection
template<typename K,typename V>
void BinSearchCollection<K,V>::remove(const K& key)
{
  int pos;
  bool find = this->binsearch(key,pos); // calls binsearch
  if(find)
  {  
	kv_list.erase(kv_list.begin() + pos); // erases 
	pos = -1; // number that cannot be a possible index
  }
}

//find and return the value associated with the key
template<typename K,typename V>
bool BinSearchCollection<K,V>::find(const K& key, V& val) const
{	
  int size = kv_list.size();
  int pos = -1; // number that cannot be a possible index
  if (size == 0)
  {
	return false; 
  }
  if (this->binsearch(key,pos) == true) // calls binsearch
  {
	val = kv_list.at(pos).second; // assigns val to val at pos
    return true;
  }
  else 
    return false;
}

//find and return the list of keys >= to k1 and <= to k2
template<typename K,typename V>
void BinSearchCollection<K,V>::find(const K& k1, const K& k2, vector<K>& keys) const
{
  int key1 = 0; // set index1
  int key2 = 0; // set index2
  bool find = this->binsearch(k1,key1); // sets find to T or F 
  bool find2 = this->binsearch(k2,key2); // sets find to T or F
  for(int i = key1; i <= key2; i++)
  {
	keys.push_back(kv_list[i].first); // pushes back key
  }
}

//return all of the keys in the collection
template<typename K,typename V>
void BinSearchCollection<K,V>::keys(vector<K>& keys) const
{
  int i = 0; // index
  int size = kv_list.size();	
  while (i < size) // loop
  {
	keys.push_back(kv_list.at(i).first); // pushes back key
	i++; // increment 
  }
}

//return all of the keys in ascending (sorted) order
template<typename K,typename V>
void BinSearchCollection<K,V>::sort(vector<K>& keys) const
{
  return; // function not needed bc of helper function 
}

//return the number of keys in collection
template<typename K,typename V>
int BinSearchCollection<K,V>::size() const
{
  return kv_list.size(); //gets the size of the kv_list
}

//helper function for binary search
template<typename K,typename V>
bool BinSearchCollection<K,V>::binsearch(const K& key, int& index) const
{
  bool find; 
  int first = 0; // first  
  int last = kv_list.size()-1; // last 
  int size = kv_list.size();
  do
  {
	K mid = kv_list.at((first + last)/2).first; // makes a variable mid of type K
    	if (key == mid) // case 1
	{
	  index = (first + last)/2; // sets index 
	  find = true;
	  return true;
	} 
	if (key < mid) // case 2  
	{
	  if (size == 1)
	  {
		index = ((first + last) / 2); // sets index 
		return false;
	  }
	  last = (last + first) / 2; // cuts in half
	  find = false; 
	  size = size / 2; // updates size
	}
	if (key > mid) // case 3 
	{
	  if (size == 1)
	  {
		index = (first + last) / 2 + 1; // sets index 
		return false;
	  }
	  first = ((first + last) / 2) + 1;// cuts in half
	  find = false;
	  size = size / 2; // updates size 
	}
  }
  while(find != true && size >= 1); // condition
  return false;
}

#endif