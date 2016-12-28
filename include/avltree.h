/**
 * Dennis Kao (Nov 19, 2016)
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    char key[256];
    int count;
    struct Node *left;
    struct Node *right;
};
typedef struct Node Node;

/**
 * newNode
 * Creates a new node with the value of key
 * @param key - the string to be stored
 * @return adress of a new node
 */
Node *newNode(char key[256]);

/**
 * depth
 * Recursively determines the depth of a tree
 * @param root - the address of the root of the tree
 * @return the height of the tree
 */
int depth(Node *root);

/**
 * balanceFactorOf
 * Determines the balance factor of a node from its left and right subtree
 * @param node - node you want to know the balance factor of
 * @return the balance factor of the node
 */
int balanceFactorOf (Node *node);

/**
 * search
 * Returns the address of the node containing key in the tree
 * @param root - root of tree
 * @param key - string to be searched
 * @return address of the node containing the key, returns NULL if node DNE
 */
Node *search(Node *root, char key[256]);

/**
 * destroy
 * Free's all memory used by the tree in a postorder traversal
 * @param root - root of tree
 * @return none
 */
void destroy(Node *root);

/**
 * size
 * Returns the number of nodes in a tree
 * @param root - root of tree
 * @return size of the tree
 */
int size(Node *root);

/**
 * rightLeftRotation
 * Preforms a right left rotation
 * @param node - the right heavy node
 * @return the address of the new node which replaces the right heavy node
 */
Node *rightLeftRotation(Node *node);

/**
 * leftRightRotation
 * Preforms a left right rotation
 * @param node - the left heavy node
 * @return the address of the new node which replaces the left heavy node
 */
Node *leftRightRotation(Node *node);

/**
 * singleLeftRotation
 * Preforms a left rotation
 * @param node - the right heavy node
 * @return the address of the new node which replaces the right heavy node
 */
Node *singleLeftRotation(Node *node);

/**
 * singleRightRotation
 * Preforms a right rotation
 * @param node - the left heavy node
 * @return the address of the new node which replaces the left heavy node
 */
Node *singleRightRotation(Node *node);

/**
 * balance
 * Balances an AVL tree
 * @param root - root of tree
 * @return new root of tree
 */
Node *balance(Node *root);

/**
 * insert
 * Inserts a node into its appropriate place in a tree, then balances the tree
 * The user should check if the node already exists in the tree with search()
 * @param root - root of tree
 * @param toBeInserted - node to be inserted
 * @return new root of tree
 */
Node *insert(Node *root, Node *toBeInserted);

/**
 * initializeTree
 * Parses a .txt file with whitespace seperated keys and stores it into an AVL tree
 * @param input - file to be parsed
 * @param a pointer to the root of a tree
 * @return root of the tree
 */
Node *initializeTree(FILE *input, Node *root);

/**
 * isAllNumbers
 * Checks if a null terminated string contains only number characters
 * @param string - string to be checked
 * @return 0 if false, 1 if true
 */
int isAllNumbers(char string[256]);

/**
 * printFrequencyAbove
 * Prints information of all keys above a given frequency
 * @param root - root of tree
 * @param int - the frequency to be tested against
 * @return size of the tree
 */
void printFrequencyAbove(Node *root, int frequency);

/**
 * numChildren
 * Determines the number of children a node has
 * @param node - the address of the node to be tested
 * @returns 0,1,2 depending on the number of children
 */
int numChildren(Node *node);

/**
 * successor
 * Finds the in order sucessor of a node
 * @param Node - node to find the sucessor of
 * @return the address to the sucessor of the node
 */
Node *successor(Node *node);

/**
 * parent
 * Finds the parent of a node
 * @param root - root of tree
 * @param child - the node we want to find the parent of
 * @return the parent of the node, or NULL if child has no parent
 */
Node *parent(Node *root, Node *child);

/**
 * removeNode
 * Free's the specified node in a tree and rearrages the surrouding nodes.
 * The tree will have to be balanced using balance() afterwards,
 * The removal of a node in a one node tree will have to be accounted for outside
 * this function.
 *
 * @param root - root of tree
 * @param toBeRemoved - address of the node to be removed, you can use search() to find this
 * @return none
 */
void removeNode(Node *root, Node *toBeRemoved);
