/*
Brian Steuber
CPSC 223-01
HW11
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
  
  // prints out color/tree
  void print() const;
  
private:

  // binary search tree node structure
  struct Node {
	K key;
	V value;
	Node* left;
	Node* right;
	bool is_black; // true if black, false if red
	bool is_dbl_black_left; // for remove rotations 
	bool is_dbl_black_right;
  };
  
  // root node of the search tree
  Node* root;
  
  // number of k-v pairs in the collection
  int collection_size;
  
  // helper to recursively empty search tree
  void make_empty(Node* subtree_root);
  
  // recursive helper to remove node with given key
  Node* remove(const K& key, Node* parent, Node* subtree_root, bool& found);
  
  // helper to perform a single rebalance step on a red-black tree on remove
  Node* remove_color_adjust(Node* parent);
  
  // find inorder successor
  Node* inorder_successor(Node* subtree_root);
  
  // recursive helper to do red-black insert key-val pair (backtracking)
  Node* insert(const K& key, const V& val, Node* subtree_root);
  
  // helper functions to perform a single right rotation
  Node* rotate_right(Node* k2);
  
  // helper functions to perform a single left rotation
  Node* rotate_left(Node* k2);
  
  // recursive helper function for print
  void print(const Node* subtree_root) const;
  
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
  // check if anything to remove
  if ( root == nullptr )
    return;
  // create a " fake " root to pass in as parent of root
  Node* root_parent = new Node;
  root_parent->key = root->key;
  root_parent->left = nullptr;
  root_parent->right = root;
  root_parent->is_black = true;
  root_parent->is_dbl_black_left = false;
  root_parent->is_dbl_black_right = false;
  // call remove
  bool found = false;
  root_parent = remove(key, root_parent, root, found);
  // update results
  if (found) 
  {
    collection_size--;
    root = root_parent->right;
    if (root) 
    {
      root -> is_black = true;
      root -> is_dbl_black_right = false;
      root -> is_dbl_black_left = false;
    }
  }
  delete root_parent;
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
RBTCollection<K,V>::remove(const K& key, Node* parent, Node* subtree_root, bool& found)
{
  if(subtree_root && key < subtree_root->key)
    subtree_root = remove(key, subtree_root, subtree_root->left, found);
  else if(subtree_root && key > subtree_root->key)
    subtree_root = remove(key, subtree_root, subtree_root->right, found);
  else if(subtree_root && key == subtree_root->key)
  {
    found = true;
    // leaf node 
    if(!subtree_root->left && !subtree_root->right)
	{
      if(subtree_root->is_black && subtree_root->key < parent->key)
	  {
        parent->is_dbl_black_left = true;
        parent->left = nullptr;
      }
      else if(subtree_root->is_black && subtree_root->key > parent->key)
	  {
        parent->is_dbl_black_right = true;
        parent->right = nullptr;
      }
      else if(subtree_root->key < parent->key)
        parent->left = nullptr;
      else
        parent->right = nullptr;
	  delete subtree_root;
    }
    // left non empty but right empty 
    else if(subtree_root->left && !subtree_root->right)
    {
      if(subtree_root->is_black && subtree_root->key < parent->key)
	  {
        parent->is_dbl_black_left = true;
        parent->left = subtree_root->left;
      }
      else if(subtree_root->is_black && subtree_root->key > parent->key)
	  {
        parent->is_dbl_black_right = true;
        parent->right = subtree_root->left;
      }
      else if(subtree_root->key < parent->key)
        parent->left = subtree_root->left;
      else
        parent->right = subtree_root->left;
      delete subtree_root;
    }
    // left empty but right non empty
    else if(!subtree_root->left && subtree_root->right)
    {
      if(subtree_root->is_black && subtree_root->key < parent->key)
	  {
        parent->is_dbl_black_left = true;
        parent->left = subtree_root->right;
      }
      else if(subtree_root->is_black && subtree_root->key > parent->key)
	  {
        parent->is_dbl_black_right = true;
        parent->right = subtree_root->right;
      }
      else if(subtree_root->key < parent->key)
        parent->left = subtree_root->right;
      else
        parent->right = subtree_root->right;
      delete subtree_root;
    }
    // left and right non empty 
    else
    {
      //find in order successor (right, then interate left)
      Node* temp = (inorder_successor(subtree_root));
      //then call remove again on inorder successor key and subtree root's
      //right child once the key and value copy is complete
      subtree_root->key = temp->key;
      subtree_root->value = temp->value;
      subtree_root = remove(temp->key, subtree_root, subtree_root->right, found);
    }
  }

  if (!found)
    return parent;

  //backtracking, adjust color at parent
  return remove_color_adjust(parent);
}

// helper to perform a single rebalance step on a red-black tree on remove
template<typename K, typename V>
typename RBTCollection<K,V>::Node*
RBTCollection<K,V>::remove_color_adjust(Node* subtree_root)
{
  //subtree root is "grandparent" g, with left child gl and right child gr
  Node* g = subtree_root;
  Node* gl = g->left;
  Node* gr = g->right;
  //parent p is either gl or gr
  Node* p = nullptr;
  bool left_parent = false;
  if(gl && (gl->is_dbl_black_left || gl->is_dbl_black_right))
  { 
    p = gl;
    left_parent = true;
  }
  else if(gr && (gr->is_dbl_black_left || gr->is_dbl_black_right))
    p = gr;
  else
    return subtree_root;
  // parent's left child is a double black node 
  if(p->is_dbl_black_left)
  {
    //case 1: red sibling
    if(p->right && !p->right->is_black)
	{
      p = rotate_left(p);
      p->left->is_black = false;
      return remove_color_adjust(p->left);
    }
    //case 2: black sibling with red child outside
    else if(p->right && p->right->right && !p->right->right->is_black)
	{
      p = rotate_left(p);
      if(p->left->is_black)
	    p->is_black = true;
      else
	  {
		p->left->is_black = true;
        p->is_black = false;
      }
    }
    //case 2: black sibling with red child inside
    else if(p->right && p->right->left && !p->right->left->is_black)
	{
      p->right = rotate_right(p->right); 
      p = rotate_left(p);
      if(p->left->is_black)
        p->is_black = true;
      else
	  {
        p->left->is_black = true;
        p->is_black = false;
      }
    }
    //case 3: black sibling with black children, red parent
    else if(!p->is_black)
	{
      p->is_black = true;
      if(p->right)
        p->right->is_black = false;
	}
    //case 3: black sibling with black children, black parent 
    else
	{
      if(left_parent)
        g->is_dbl_black_left = true;
      else 
        g->is_dbl_black_right = true;
      if(p->right)
        p->right->is_black = false;
    }
  }
  //parent's right child is a double black node 
  if(p->is_dbl_black_right)
  {
    //case 1: red sibling
    if(p->left && !p->left->is_black)
	{
      p = rotate_right(p);
      p->right->is_black = false;
      return remove_color_adjust(p->right); 
    }
    //case 2: black sibling with red child outside
    else if(p->left && p->left->left && !p->left->left->is_black)
	{
      p = rotate_right(p);
      if(p->right->is_black)
        p->is_black = true;
      else
	  {
        p->right->is_black = true;
        p->is_black = false;
      }
    }
    //case 2: black sibling with red child inside
    else if(p->left && p->left->right && !p->left->right->is_black)
	{
      p->left = rotate_left(p->left);
      p = rotate_right(p);
      if(p->right->is_black)
	    p->is_black = true;
      else
	  {
        p->right->is_black = true;
        p->is_black = false;
      }
    }
    //case 3: black sibling with black children, red parent
    else if(!p->is_black)
	{
      p->is_black = true;
      if(p->left)
        p->left->is_black = false;
    }
    //case 3: black sibling with black children, black parent
    else
	{
      if(left_parent)
        g->is_dbl_black_left = true;
      else
        g->is_dbl_black_right = true;
      if(p->left)
        p->left->is_black = false;
    }
  }

  // connect up the subtree_root to the parent 
  if(left_parent)
    subtree_root->left = p;
  else
  subtree_root->right = p;
  return subtree_root;
}

// find the inorder successor
template<typename K, typename V>
typename RBTCollection<K,V> ::Node* 
RBTCollection<K,V>::inorder_successor(Node* subtree_root)
{
  Node* right = subtree_root->right;
  while(right && right->left != nullptr)
	right = right->left;
  return right;
}

// function to print and get color 
template<typename K, typename V>
void RBTCollection<K,V>::print() const
{
  print(root);
}

// helper function for print 
template<typename K, typename V>
void RBTCollection<K,V>::print(const Node* subtree_root) const
{
  if (subtree_root == nullptr)
	return;
  else 
  {
	cout << subtree_root->key;
	if (subtree_root->is_black == true)
      cout << " (black)" << endl;
    else 
	  cout << " (red)" << endl;
    if (subtree_root->left != nullptr)
	{
      cout << " left child of " << subtree_root->key << " is ";
	  print(subtree_root->left);
	}
	if (subtree_root->right != nullptr)
	{
      cout << " right child of " << subtree_root->key << " is ";
      print(subtree_root->right);
	}
  }
  return;
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
  
  
  
  
  
  