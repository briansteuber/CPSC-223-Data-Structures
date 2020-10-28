/*
Brian Steuber
CPSC 223-01
HW10
This rbt_collection.h file implements
the abstract class in collection.h.
*/

#ifndef RBT_COLLECTION_H
#define RBT_COLLECTION_H

#include <vector>
#include <algorithm>
#include <functional>
#include "collection.h"

using namespace std;

template<typename K, typename V>
class RBTCollection : public Collection<K,V>
{
public:

  // create an empty linked list
  RBTCollection();
  
  // copy a linked list
  RBTCollection(const RBTCollection<K,V>& rhs);
  
  // assign a linked list 
  RBTCollection<K,V>& operator=(const RBTCollection<K,V>& rhs);
  
  // delete a linked list
  ~RBTCollection();
  
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
  int size() const;
  
  // return the height of the tree
  int height() const;
  
private:

  // binary search tree node structure
  struct Node {
	K key;
	V value;
	Node* left;
	Node* right;
	bool is_black; // true if black, false if red
  };
  
  // root node of the search tree
  Node* root;
  
  // number of k-v pairs in the collection
  int collection_size;
  
  // helper to recursively empty search tree
  void make_empty(Node* subtree_root);
  
  // recursive helper to remove node with given key
  Node* remove(const K& key, Node* subtree_root);
  
  // recursive helper to do red-black insert key-val pair (backtracking)
  Node* insert(const K& key, const V& val, Node* subtree_root);
  
  // helper functions to perform a single right rotation
  Node* rotate_right(Node* k2);
  
  // helper functions to perform a single left rotation
  Node* rotate_left(Node* k2);
  
  // helper to recursively build sorted list of keys 
  void inorder(const Node* subtree, vector<K>& keys) const;
  
  // helper to recursively build sorted list of keys 
  void preorder(const Node* subtree, vector<K>& keys) const;
  
  void preorder_copy(Node* lhs_subtree, const Node* rhs_subtree);
  
  // helper to recursively find range of keys
  void range_search(const Node* subtree_root, const K& k1, const K& k2,
                    vector<K>& keys) const;
  
  // return the height of the tree rooted at subtree_root
  int height(const Node* subtree_root) const;
  
};

// create an empty linked list
template<typename K, typename V>
RBTCollection<K,V>::RBTCollection() : collection_size(0), root(nullptr)
{
  
}

// copy a linked list
template<typename K, typename V>
RBTCollection<K,V>::RBTCollection(const RBTCollection<K,V>& rhs)
  : collection_size(0), root(nullptr)
{
  *this = rhs;
}

// assign a linked list
template<typename K, typename V>
RBTCollection<K,V>& RBTCollection<K,V>::operator=(const RBTCollection<K,V>& rhs)
{
  if (this == &rhs)
	return *this;
  // delete current
  make_empty(root);
  //build tree
  vector<K> ks;
  preorder(rhs.root, ks);
  //TODO
  for (int i = 0; i < rhs.collection_size; i++)
  {
    V val;
	rhs.find(ks[i], val);
	insert(ks[i], val);
  }
  return *this;
}

// delete a linked list
template<typename K, typename V>
RBTCollection<K,V>::~RBTCollection()
{
  make_empty(root); 
}

// insert a key-value pair into the collection
template<typename K, typename V>
void RBTCollection<K,V>::insert(const K& key, const V& val)
{
  root = insert(key, val, root); // call to insert helper
  root->is_black = true; // sets root to black
  collection_size++; // increment 
}

// remove a key-value pair from the collection
template<typename K, typename V>
void RBTCollection<K,V>::remove(const K& key)
{
  root = remove(key, root);
}

// find the value associated with the key
template<typename K, typename V>
bool RBTCollection<K,V>::find(const K& key, V& val) const
{
  // TODO
  // NOTE: You cannot use recursion or any helper for find  
  Node* cur = root;
  if (root == nullptr)
  {
	return false;
  }
  while(cur != nullptr)
  {
	if(key < cur->key)
	  cur = cur->left; // go left
	else if(key > cur->key)
	  cur = cur->right; // go right
	else 
	{
	  val = cur->value; // found
	  return true;
	}
  }
  return false; // not found 
}

// find the keys associated with the range
template<typename K, typename V> 
void RBTCollection<K,V>::find(const K& k1, const K& k2, vector<K>& keys) const
{
  // defer to the range search (recursive) helper function
  range_search(root,k1,k2,keys); 
}

// return all keys in the collection
template<typename K, typename V> 
void RBTCollection<K,V>::keys(vector<K>& keys) const
{
  // defer to the inorder (recursive) helper function
  inorder(root, keys);
}

// return collection keys in sorted order
template<typename K, typename V> 
void RBTCollection<K,V>::sort(vector<K>& keys) const
{
  // defer to the inorder (recursive) helper function
  inorder(root, keys); 
}

//return the number of keys in the collection
template<typename K, typename V> 
int RBTCollection<K,V>::size() const
{
  return collection_size; 
}

// return the height of the tree
template<typename K, typename V> 
int RBTCollection<K,V>::height() const
{
  //defer to the height (recursive) helper function
  return height(root); 
}

// helper to recursively empty search tree
template<typename K, typename V>
void RBTCollection<K,V>::make_empty(Node* subtree_root)
{
  //TODO
  //recursive helper function
  if (subtree_root == nullptr) 
	return;
  if (subtree_root->left != nullptr)
	make_empty(subtree_root->left);
  if (subtree_root->right != nullptr)
	make_empty(subtree_root->right);
  subtree_root->left = nullptr;
  subtree_root->right = nullptr;
  subtree_root = nullptr;
  collection_size--;
}

// helper function for remove
template<typename K, typename V>
typename RBTCollection<K,V> :: Node*
RBTCollection<K,V>::remove(const K& key, Node* subtree_root)
{
  if (subtree_root == nullptr) // empty tree
    return subtree_root;
  else if (subtree_root && key < subtree_root->key) // key < root
	subtree_root->left = remove(key, subtree_root->left);
  else if (subtree_root && key > subtree_root->key) // key > root
	subtree_root->right = remove(key, subtree_root->right);
  else if (subtree_root && key == subtree_root->key) // key == root
  {	
	// Leaf
	if (subtree_root->left == nullptr && subtree_root->right == nullptr)
	{
	 delete subtree_root;
	 subtree_root = nullptr;
	 collection_size--;
	}

	//Case 1: there is a left child but no right child
	else if (subtree_root->left != nullptr && subtree_root->right == nullptr)
	{
	  Node* ptr = subtree_root;
	  subtree_root = subtree_root->left;
	  delete ptr;
	  ptr = nullptr;
	  collection_size--;
	}
	
	//Case 2: there is no left child but there is a right child
	else if (subtree_root->left == nullptr && subtree_root->right != nullptr)
	{
	  Node* ptr = subtree_root;
	  subtree_root = subtree_root->right;
	  delete ptr;
	  ptr = nullptr;
	  collection_size--;
	}
	//Case 3: two children 
	else if (subtree_root->left != nullptr && subtree_root->right != nullptr)
	{
	  Node* successor = subtree_root->right;
	  Node* before = new Node;
	  while (successor->left != nullptr) // left side
	  {
		before = successor; 
		successor = successor->left;
	  }
	  if (successor->right != nullptr) // right side
		before->left = successor->right;
      else // not present
 		before->left = nullptr;
	  if (subtree_root->right != successor)
		successor->right = subtree_root->right;
	  successor->left = subtree_root->left;
      subtree_root = successor;
      collection_size--;
      return subtree_root;		  
	}
  }
  return subtree_root;
}

// recursive helper to do red-black insert key-val pair (backtracking)
template<typename K, typename V>
typename RBTCollection<K,V> :: Node* 
RBTCollection<K,V>::insert(const K& key, const V& val, Node* subtree_root)
{
  if (collection_size == 0 || subtree_root == nullptr) // empty
  {
	Node* ins = new Node; // "root" node
	ins->key = key; // assigns key 
	ins->value = val; // assigns value
	ins->is_black = false; // assigns color
	ins->left = nullptr; // assigns left to null
	ins->right = nullptr; // assigns right to null
	subtree_root = ins; // assignment to ins
  }
  else // not empty
  {
	if (key < subtree_root->key) // less than comparison
	  subtree_root->left = insert(key, val, subtree_root->left); // left recursive step
    else // greater than or equal to comparison
	  subtree_root->right = insert(key, val, subtree_root->right); // right recursive
  }
  
  if (subtree_root->is_black) // if the root is black: def of rbt
  {
	if((subtree_root->left && !subtree_root->left->is_black) && (subtree_root->right && !subtree_root->right->is_black)) // case 1
	{
	  if(subtree_root->left->left && !subtree_root->left->left->is_black) // case 1: left left 
	  {
		subtree_root->is_black = false;
		subtree_root->left->is_black = true;
		subtree_root->right->is_black = true;
	  }
	  else if (subtree_root->right->right && !subtree_root->right->right->is_black) // case 1: right right 
	  {
		subtree_root->is_black = false;
		subtree_root->left->is_black = true;
		subtree_root->right->is_black = true;
	  }
	  else if (subtree_root->left->right && !subtree_root->left->right->is_black) // case 1: left right 
	  {
		subtree_root->is_black = false;
		subtree_root->left->is_black = true;
		subtree_root->right->is_black = true;
	  }
	  else if (subtree_root->right->left && !subtree_root->right->left->is_black) // case 1: right left 
	  {
		subtree_root->is_black = false;
		subtree_root->left->is_black = true;
		subtree_root->right->is_black = true;
	  }
	}
	else // cases 2 & 3 
	{
	  if ((subtree_root->left && !subtree_root->left->is_black) && (subtree_root->left->left && !subtree_root->left->left->is_black)) // case 2: rotate right
	  {
		subtree_root = rotate_right(subtree_root);
		subtree_root->is_black = true;
		subtree_root->right->is_black = false;
	  }
	  else if ((subtree_root->right && !subtree_root->right->is_black) && (subtree_root->right->right && !subtree_root->right->right->is_black)) // case 2: rotate left
	  {
		subtree_root = rotate_left(subtree_root);
		subtree_root->is_black = true;
		subtree_root->left->is_black = false;
	  }
	  else if ((subtree_root->left && !subtree_root->left->is_black) && (subtree_root->left->right && !subtree_root->left->right->is_black)) // case 3: left right rotation
	  {
		subtree_root->left = rotate_left(subtree_root->left);
		subtree_root = rotate_right(subtree_root);
		subtree_root->is_black = true;
		subtree_root->right->is_black = false;
	  }
	  else if ((subtree_root->right && !subtree_root->right->is_black) && (subtree_root->right->left && !subtree_root->right->left->is_black)) // case 3: right left rotation
	  {
		subtree_root->right = rotate_right(subtree_root->right);
		subtree_root = rotate_left(subtree_root);
		subtree_root->is_black = true;
		subtree_root->left->is_black = false;
	  }
	}
  }
  return subtree_root;
}
	  
// helper functions to perform a single right rotation
template<typename K, typename V>
typename RBTCollection<K,V> :: Node* 
RBTCollection<K,V>::rotate_right(Node* k2)
{
  Node* k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  return k1;
}

// helper functions to perform a single left rotation
template<typename K, typename V>
typename RBTCollection<K,V> :: Node* 
RBTCollection<K,V>::rotate_left(Node* k2)
{
  Node* k1 = k2->right;
  k2->right = k1->left;	
  k1->left = k2;
  return k1;
}

// helper to recursively build sorted list of keys
template<typename K, typename V> 
void RBTCollection<K,V>::inorder(const Node* subtree, vector<K>& keys) const
{
  //TODO
  //this is a recursive helper function
  if(subtree == nullptr)
	return;
  else
  {
	if(subtree->left != nullptr)
	  inorder(subtree->left, keys); // recursive call to left
    keys.push_back(subtree->key); 
	if(subtree->right != nullptr)
	  inorder(subtree->right, keys);  // recursive call to right
  }
  return;
}

// helper to recursively build sorted list of keys
template<typename K, typename V> 
void RBTCollection<K,V>::preorder(const Node* subtree, vector<K>& keys) const
{
  //TODO
  //this is a recursive helper function 
  if(subtree == nullptr)
	return;
  else
  {
    keys.push_back(subtree->key);
	if(subtree->left != nullptr)
      preorder(subtree->left, keys); // recursive call to left 
	if(subtree->right != nullptr)
	  preorder(subtree->right, keys);  // recursive call to right
  }
  return;
}

// helper to recursively find range of keys
template<typename K, typename V> void 
RBTCollection<K,V>::
range_search(const Node* subtree, const K& k1, const K& k2, vector<K>& keys) const
{
  //TODO
  //this is a recursive helper function
  if(subtree == nullptr)
	return;
  range_search(subtree->left, k1, k2, keys); // recursive call to left
  if(subtree->key >= k1 && subtree->key <= k2)
	keys.push_back(subtree->key);
  range_search(subtree->right, k1, k2, keys); // recursive call to left
}

// return the height of the tree rooted at subtree_root
template<typename K, typename V> 
int RBTCollection<K,V>::height(const Node* subtree_root) const
{
  //TODO
  //this is a recursive helper function
  if(subtree_root->left == nullptr && subtree_root->right == nullptr)
	return 1;
  int height_left = 0, height_right = 0;
  if(subtree_root->left != nullptr)
	height_left = height(subtree_root->left); // recursive call to left
  if(subtree_root->right != nullptr)
	height_right = height(subtree_root->right); // recursive call to right
  if(height_left >= height_right)
	return 1 + height_left; // height comparison
  else
	return 1 + height_right; // height comparison
  return 1;
}

#endif
  
  
  
  
  
  