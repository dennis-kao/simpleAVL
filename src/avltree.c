/**
 * Dennis Kao (Nov 19, 2016)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avltree.h"

Node *newNode(char key[20]) {

    Node *new = malloc(sizeof(Node));

    if (new == NULL) return NULL;

    strcpy(new->key, key);

    new->left = NULL;
    new->right = NULL;
    new->count = 1;

    return new;
}

int depth(Node *root) {

  int leftDepth = 0;
  int rightDepth = 0;

  if (root == NULL) return 0;

  if (root->left != NULL) leftDepth = depth(root->left);
  if (root->right != NULL) rightDepth = depth(root->right);

  if (leftDepth > rightDepth) return leftDepth+1;
  else return rightDepth+1;
}

int balanceFactorOf (Node *node) {

  int leftDepth = 0;
  int rightDepth = 0;

  if (node == NULL) return 0;

  if (node->left != NULL) leftDepth = depth(node->left);
  if (node->right != NULL) rightDepth = depth(node->right);

  return leftDepth - rightDepth;
}

Node *search(Node *root, char key[256]) {

  if (root == NULL) return NULL;

  if (strcmp(key, root->key) == 0) return root;
  else {

    if (search(root->left, key) != NULL) return search(root->left, key);
    if (search(root->right, key) != NULL) return search(root->right, key);

    return NULL;
  }
}

void destroy(Node *root) {

  if (root == NULL) return;

  destroy(root->left);
  destroy(root->right);
  free(root);
}

int size(Node *root) {

  int leftSize = 0;
  int rightSize = 0;

  if (root == NULL) return 0; //external node, no size

  leftSize = size(root->left);
  rightSize = size(root->right);

  return 1 + leftSize + rightSize; //size of node itself, left and right subtree
}

Node *rightLeftRotation(Node *node) {

  Node *x = node; //original node
  Node *y = node->right; //right subtree of x
  Node *z = node->right->left; //left subtree of y

  x->right = z->left;
  y->left = z->right;
  z->left = x;
  z->right = y;

  return z;
}

Node *leftRightRotation(Node *node) {

  Node *x = node; //original node
  Node *y = node->left; //left subtree of x
  Node *z = node->left->right; //right subtree of y

  x->left = z->right;
  y->right = z->left;
  z->right = y;
  z->left = x;

  return z;
}

Node *singleLeftRotation(Node *node) {

  Node *originalNode = node;
  Node *rightSubtree = node->right;

  originalNode->right = rightSubtree->left;
  rightSubtree->left = originalNode;

  return rightSubtree;
}

Node *singleRightRotation(Node *node) {

  Node *originalNode = node;
  Node *leftSubtree = node->left;

  originalNode->left = leftSubtree->right;
  leftSubtree->right = originalNode;

  return leftSubtree;
}

Node *balance(Node *root) {

  if (root == NULL) return root;

  if (root->left != NULL) root->left = balance(root->left);
  if (root->right != NULL) root->right = balance(root->right);

  if (balanceFactorOf(root) == -2) { //right heavy

    if (balanceFactorOf(root->right) == -1) return singleLeftRotation(root); //is the tree's left subtree right heavy?
    else return rightLeftRotation(root);
  }
  else if (balanceFactorOf(root) == 2) { //tree is left heavy

    if (balanceFactorOf(root->left) == 1) return singleRightRotation(root); //is the tree's right subtree left heavy?
    else return leftRightRotation(root);
  }
  else return root; //tree is balanced, == 0,1,-1
}

Node *insert(Node *root, Node *toBeInserted) {

  Node *parent = NULL;
  Node *originalRoot = root;
  Node *alreadyExists = search(root, toBeInserted->key);

  if (root == NULL) return toBeInserted;
  else if (alreadyExists != NULL) {
    alreadyExists->count++;
    return originalRoot;
  }
  else {

    //move through tree until an appropriate spot is toBeRemoved
    while (root != NULL) {
      parent = root;

      if (strcmp(root->key, toBeInserted->key) > 0) root = root->left; //move left if current node > TBI
      else if (strcmp(root->key, toBeInserted->key) < 0) root = root->right;
    }

    //actually insert the node where it needs to be
    //need to strcmp() again because we dont know which subtree of the parent it is in
    if (strcmp(parent->key, toBeInserted->key) > 0) {
      parent->left = toBeInserted;
    }
    else if (strcmp(parent->key, toBeInserted->key) < 0) {
      parent->right = toBeInserted;
    }

    return balance(originalRoot);
  }
}

Node *initializeTree(FILE *input, Node *root) {

  char line[256];
  Node *new;

  while (fscanf(input, " %256s", line) == 1) {

    new = newNode(line);

    if (new == NULL) {
      printf("Insufficient memory! Could not make node.\n");
      return NULL;
    }

    root = insert(root, new);
  }

  return root;
}

int isAllNumbers(char string[256]) {

  for (int i = 0; i < 256; i++) {

    if (string[i] == '\0') break;

    if (isdigit(string[i]) == 0) return 0;
  }

  return 1;
}

void printFrequencyAbove(Node *root, int frequency) {

  if (root == NULL) return;

  printFrequencyAbove(root->left, frequency);
  printFrequencyAbove(root->right, frequency);

  if (root->count > frequency) printf("key: %s, frequency: %d\n", root->key, root->count);
}

int numChildren(Node *node) {

  if (node->left != NULL && node->right != NULL) return 2;
  else if (node->left != NULL) return 1;
  else if (node->right != NULL) return 1;
  else return 0;
}

Node *successor(Node *node) {

  Node *z = node->right;

  while (z->left != NULL) z = z->left;

  return z;
}

Node *parent(Node *root, Node *child) {

  if (root == NULL) return NULL;

  Node *ls = parent(root->left, child);
  Node *rs = parent(root->right, child);

  if (ls != NULL) return ls;
  if (rs != NULL) return rs;

  /*C's Short Circuiting - C Doesn't execute second conditional if first conditional is false (child is NULL)*/
  if (root->left != NULL && strcmp(root->left->key, child->key) == 0) return root;
  if (root->right != NULL && strcmp(root->right->key, child->key) == 0) return root;

  return NULL;
}

void removeNode(Node *root, Node *toBeRemoved) {

  if (root == NULL) return;

  if (numChildren(toBeRemoved) == 0) {

    Node *removeParent = parent(root, toBeRemoved);

    if (removeParent->left == toBeRemoved) removeParent->left = NULL;
    else if (removeParent->right == toBeRemoved) removeParent->right = NULL;

    free(toBeRemoved);
  }

  else if (numChildren(toBeRemoved) == 1) {

    //add the one child to the parent
    if (toBeRemoved->left != NULL) {
      toBeRemoved->count = toBeRemoved->left->count;
      strcpy(toBeRemoved->key, toBeRemoved->left->key);

      free(toBeRemoved->left);
      toBeRemoved->left = NULL;
    }
    else if (toBeRemoved->right != NULL) {
      toBeRemoved->count = toBeRemoved->right->count;
      strcpy(toBeRemoved->key, toBeRemoved->right->key);

      free(toBeRemoved->right);
      toBeRemoved->right = NULL;
    }
  }

  else if (numChildren(toBeRemoved) == 2) {

    Node *suc = successor(toBeRemoved);

    toBeRemoved->count = suc->count;
    strcpy(toBeRemoved->key, suc->key);

    if (suc->right != NULL) { //numChildren = 1

      Node *sucRight = suc->right;

      suc->count = sucRight->count;
      strcpy(suc->key, sucRight->key);

      suc->right = NULL;
      free(sucRight);
    }

    else { //numChildren = 0

      Node *sucParent = parent(root, suc);

      if (sucParent->left == suc) sucParent->left = NULL;
      else if (sucParent->right == suc) sucParent->right = NULL;

      free(suc);
    }
  }
}
