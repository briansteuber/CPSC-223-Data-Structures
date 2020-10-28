/*
Brian Steuber
CPSC 223-01
HW3
This vector_collection.h file implements
the abstract class in collection.h.
This file allows the hw3_tests.cpp to 
access the functions in order to test
difference cases for the key value 
data type.
*/

#ifndef VECTOR_COLLECTION_H
#define VECTOR_COLLECTION_H
#include <vector>
#include <algorithm>
#include "collection.h"

using namespace std;

template<typename K, typename V>
class VectorCollection : public Collection<K,V>
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
  vector<pair<K,V>> kv_list;
  
};

//inserts a key value pair into the collection
template<typename K,typename V>
void VectorCollection<K,V>::insert(const K& key, const V& val)
{
  pair<K,V> p(key, val);
  kv_list.push_back(p);
}

/*
Removes a key-value pair from the collection.
It does this by traversing the size of the kvlist
and if a member of the list equals the key, 
it immediately erases that key.  
*/
template<typename K, typename V>
void VectorCollection<K,V>::remove(const K& key)
{
  for (int i = 0; i < kv_list.size(); i++)
  {
	if (kv_list.at(i).first == key)
	{
      kv_list.erase(kv_list.begin() + i);
	}
  }
}

/*
Finds and returns the value associated with the key 
*/
template<typename K,typename V>
bool VectorCollection<K,V>::find(const K& key, V& val) const
{
  if (kv_list.empty()) //case if list is empty
  {
    return false;
  }  
  if (kv_list.size() > 0) //if the size is 1 or larger
  {
	for (int i = 0; i < kv_list.size(); i++) //traverse
	{
      if (kv_list.at(i).first == key)
      {
	    val = kv_list.at(i).second; //assigns val to the val of the key pair
		return true;
	  }
	}
  }
  return false;
}

/*
Finds and returns the list of keys >= to k1 and <= to k2
*/
template<typename K,typename V>
void VectorCollection<K,V>::find(const K& k1, const K& k2, vector<K>& keys) const
{
  for (int i = 0; i < kv_list.size(); i++) //traverse 
  {
    if (kv_list.at(i).first >= k1 && kv_list.at(i).first <= k2) //checks to see if the key is >=k1 && <= k2
	{
      keys.push_back(kv_list.at(i).first); //pushes back the key(s)
	}
  }
}

//returns all of the keys in the collection
template<typename K,typename V>
void VectorCollection<K,V>::keys(vector<K>& keys) const
{
  for (int i = 0; i < kv_list.size(); i++) //traverse
  {
    keys.push_back(kv_list.at(i).first); //pushes back all keys in the keylist
  }	
}

//returns all of the keys in ascending (sorted) order
template<typename K,typename V>
void VectorCollection<K,V>::sort(vector<K>& keys) const
{
  	
  for (int i = 0; i < kv_list.size(); i++) //traverse
  {
    keys.push_back(kv_list.at(i).first); //pushes back the key(s) 
  }
  std::sort(keys.begin(), keys.end()); //sort function
}

//return the number of keys in collection
template<typename K,typename V>
int VectorCollection<K,V>::size() const
{
	return kv_list.size(); //gets the size of the kv_list
}

#endif