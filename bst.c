/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name:
 * Email:
 */

#include <stdlib.h>
#include <stdio.h>

#include "bst.h"
#include "stack.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  printf("running create");
  struct bst* new_bst = (struct bst*)malloc(sizeof(struct bst*));
  new_bst->root = NULL;
  printf("complete");
  return new_bst;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
  if(bst != NULL){
    bst_free_rec(bst->root);
  }
  free(bst);
  return;
}

void bst_free_rec(struct bst_node* bst_node){
  if(bst_node == NULL){
    return;
  }
  bst_free_rec(bst_node->right);
  bst_free_rec(bst_node->left);
  free(bst_node);
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
  int size = 0;
  size = bst_node_size(bst->root);
  return size;
}

int bst_node_size(struct bst_node* bst_node){
  if(bst_node == NULL){
    return 0;
  }
  else{
    printf("\nFound node with key: %d", bst_node->key);
    return (bst_node_size(bst_node->right) + 1 + bst_node_size(bst_node->left));
  }
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
  bst->root = bst_insert_inner(bst->root, key, value);
  return;
}

struct bst_node* bst_insert_inner(struct bst_node* bst_node, int key, void* value) {
  if(bst_node == NULL){
    struct bst_node* bst_new = (struct bst_node*)malloc(sizeof(struct bst_node));
    bst_new->key = key;
    bst_new->value = value;
    bst_new->right = NULL;
    bst_new->left = NULL;
    return bst_new;
  }
  fflush(stdout);
  if(key > bst_node->key){
    bst_node->right = bst_insert_inner(bst_node->right, key, value);
  }
  else if(key < bst_node->key){
    bst_node->left = bst_insert_inner(bst_node->left, key, value);
  }
  return bst_node;
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  // printf("\nkey to delete: %d", key);
  struct bst_node* node_to_delete = bst->root;
  struct bst_node* parent = NULL;
  while(node_to_delete != NULL){
    printf("\nnode key: %d", node_to_delete->key);
    if(key == node_to_delete->key){
      break;
    }
    if(key > node_to_delete->key){
      parent = node_to_delete;
      node_to_delete = node_to_delete->right;
    }
    else{
      parent = node_to_delete;
      node_to_delete = node_to_delete->left;
    }
  }
  printf("\nfound node");
  fflush(stdout);
  struct bst_node* successor = node_to_delete;
  struct bst_node* parent_s = parent;
  if(successor->right != NULL && successor->left !=NULL){
    printf("\nsetting successor");
    successor = successor->right;
    while(successor->left != NULL){
      printf("\nsetting successor to successor left");
      parent_s = successor;
      successor = successor->left;
    }
    if(successor->right != NULL){
      if(node_to_delete != parent_s && parent_s){
        parent_s->left = successor->right;
      }
    }
    if(successor != node_to_delete->left){
      successor->left = node_to_delete->left;
    }
    if(successor != node_to_delete->right){
      successor->right = node_to_delete->right;
    }
    if(parent != NULL){
      if(node_to_delete->key > parent->key){
        parent->right = successor;
      }
      else{
        parent->left = successor;
      }
    }
    else{
      bst->root = successor;
    }
  }
  else if(successor->right != NULL){
    printf("\nonly has right child");
    if(node_to_delete->key > parent->key){
      parent->right = successor->right;
    }
    else{
      parent->left = successor->right;
    }
  }
  else if(successor->left != NULL){
    printf("\nonly has left child");
    if(node_to_delete->key < parent->key){
      parent->left = successor->left;
    }
    else{
      parent->right = successor->left;
    }
  }
  else{
    printf("\nno children");
    if(parent != NULL){
      if(node_to_delete->key < parent->key){
        parent->left = NULL;
      }
      else{
        parent->right = NULL;
      }
    }
    else{
      bst->root = NULL;
    }
  }
  printf("\nfreeing node");
  free(node_to_delete);
  printf("\nfinished freeing");
  bst_size(bst);
  return;
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  struct bst_node* temp = bst->root;
  while(temp != NULL){
    // printf("\ntesting key: %d", key);
    // printf("\ntest key: %d", temp->key);
    if(temp->key == key){
      return temp->value;
    }
    else if(temp->key < key){
      // printf("\nGreater");
      temp = temp->right;
    }
    else{
      // printf("\nLess than");
      temp = temp->left;
    }
  }
  return NULL;
}

/*****************************************************************************
 **
 ** BST iterator definition (extra credit only)
 **
 *****************************************************************************/

/*
 * Structure used to represent a binary search tree iterator.  It contains
 * only a reference to a stack to be used to implement the iterator.
 *
 * You should not modify this structure.
 */
struct bst_iterator {
  struct stack* stack;
};

/*
 * This function should allocate and initialize an iterator over a specified
 * BST and return a pointer to that iterator.
 *
 * Params:
 *   bst - the BST for over which to create an iterator.  May not be NULL.
 */
struct bst_iterator* bst_iterator_create(struct bst* bst) {
  return NULL;
}

/*
 * This function should free all memory allocated to a given BST iterator.
 * It should NOT free any memory associated with the BST itself.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   iter - the BST iterator to be destroyed.  May not be NULL.
 */
void bst_iterator_free(struct bst_iterator* iter) {
  return;
}

/*
 * This function should indicate whether a given BST iterator has more nodes
 * to visit.  It should specifically return 1 (true) if the iterator has at
 * least one more node to visit or 0 (false) if it does not have any more
 * nodes to visit.
 *
 * Param:
 *   iter - the BST iterator to be checked for remaining nodes to visit.  May
 *     not be NULL.
 */
int bst_iterator_has_next(struct bst_iterator* iter) {
  return 0;
}

/*
 * This function should return both the value and key associated with the
 * current node pointed to by the specified BST iterator and advnce the
 * iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the
 * current node should be returned the normal way, while its value should be
 * returned via the argument `value`.  Specifically, the argument `value`
 * is a pointer to a void pointer.  The current BST node's value (a void
 * pointer) should be stored at the address represented by `value` (i.e. by
 * dereferencing `value`).  This will look something like this:
 *
 *   *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator.  The key and value associated with this iterator's
 *     current node should be returned, and the iterator should be updated to
 *     point to the next node in the BST (in in-order order).  May not be NULL.
 *   value - pointer at which the current BST node's value should be stored
 *     before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node
 *   pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator* iter, void** value) {
  if (value) {
    *value = NULL;
  }
  return 0;
}
