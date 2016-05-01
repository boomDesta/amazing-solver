#ifndef _AVLDICT_CPP
#define _AVLDICT_CPP

//AVLDict.cpp
#include "AVLDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of a dictionary ADT as an AVL tree
//
AVLDict::AVLDict() {
  root = NULL;

  // Initialize array of counters for depth statistics
  depth_stats = new int[MAX_STATS]();
}

void AVLDict::destructor_helper(node * x) {
  if (x == NULL) return; // Nothing to destroy.
  destructor_helper(x->left);
  destructor_helper(x->right);
  delete x->key;
  delete x;
}

AVLDict::~AVLDict() {
  // Clean up the tree.
  // This is most easily done recursively.
  destructor_helper(root);

  // It's not good style to put this into a destructor,
  // but it's convenient for this assignment...
  cout << "Depth Statistics for find():\n";
  for (int i=0; i<MAX_STATS-1; i++)
    cout << i << ": " << depth_stats[i] << endl;
  cout << "More: " << depth_stats[MAX_STATS-1] << endl;
  int s=0;
  for(int i=0;i<30;i++){
    s=s+depth_stats[i];
  }
  int average = s/30;
  cout<<"average"<<average<<endl;
  delete [] depth_stats;
}

// 221 Students:  DO NOT CHANGE THIS FUNCTION
// You need to call this function from your find (or from a helper function).
// Pass in the depth in the tree that the find stopped at.
// E.g., you'd call record_stats(0) if the entire dictionary were
// a NULL tree and you did a find on it.
// You'd call record_stats(1) if the entire dictionary were a single
// node, and you did a find on that dictionary, successful or not.
// (Another way to understand this is the number of nodes on the chain
// from the root to the node where the find succeeded,
// or to a leaf if the find didn't succeed.)
void AVLDict::record_stats(int depth) {
  if (depth > MAX_STATS-1) depth = MAX_STATS-1;
  depth_stats[depth]++;
}

bool AVLDict::find(MazeState *key, MazeState *&pred) {
  int d=0;
  node* t = root;
  while(t!=NULL){
    d++;
    if(key->getUniqId() == t->key->getUniqId()){
      record_stats(d);
      pred = t->data;
      return true;
    }
    else if(key->getUniqId()> t->key->getUniqId()) t=t->right;
    else t=t->left;
  }
  record_stats(d);
  return false;
  // TODO:  Write this function!

}

bool AVLDict::update_height( node * x ) {
  // TODO:  Write this function!
  if( x == NULL ) return false;
  int m = std::max(height(x->left), height(x->right)) + 1;
  if( x->height != m ) {
    x->height = m;
    return true;
  }
  return false;

}

void AVLDict::rotate_left( node *& a ) {
  // "rotates" the subtree rooted at a to the left (counter-clockwise)

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << "Rotate Left: " << a->getUniqId() << std::endl;
#endif
// End of "DO NOT CHANGE" Block
  node * temp = a->right;
  a->right = temp->left;
  temp->left = a;
  update_height(a);
  update_height(temp);
  a = temp;
  // TODO:  Write this function!

}

void AVLDict::rotate_right( node *& b ) {
  // "rotates" the subtree rooted at b to the right (clockwise)

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
cout << "Rotate Right: " << b->getUniqId() << endl;
#endif
// End of "DO NOT CHANGE" Block
  node * temp = b->left;
  b->left = temp->right;
  temp->right = b;
  update_height(b);
  update_height(temp);
  b = temp;
  // TODO:  Write this function!

}
void AVLDict::balance(node *&x) {
  int d = height(x->left) - height(x->right);
  if(d>=2){
    node *temp = x->left;
    if(height(temp->left) - height(temp->right) >= 0)
      rotate_right(x);
    else
      double_rotate_right(x);
  }

  if((height(x->right) - height(x->left))>=2){
    node * temp= x->right;
    if(height(temp->left)-height(temp->right) <= 0)
      rotate_left(x);
    else
      double_rotate_left(x);
  }
}
void AVLDict::double_rotate_left(node *&a) {
  rotate_right(a->right);
  rotate_left(a);
}
void AVLDict::double_rotate_right(node *&b) {
  rotate_left(b->left);
  rotate_right(b);
}
void AVLDict::insert(node* k, node *&r) {
  if( r == NULL ) {
    r = k;
    return;
  }
  if( k->key->getUniqId() < r->key->getUniqId() ) {
    insert( k, r->left );
  }
  else if( k->key->getUniqId() > r->key->getUniqId() ) {
    insert( k, r->right );
  }
  if( update_height(r) ) balance(r);
}
// You may assume that no duplicate MazeState is ever added.
void AVLDict::add(MazeState *key, MazeState *pred) {
  node * t = new node();
  t->key = key;
  t->data = pred;
  t->left = NULL;
  t->right = NULL;
  t->height = 0;
  insert(t,root);


  // TODO:  Write this function!
}

#endif 
