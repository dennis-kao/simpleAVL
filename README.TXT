/**
 * Dennis Kao (Nov 19, 2016)
 */

======================================
Compilation and execution
======================================
The program can be compiled by navigating to the root directory (/simpleAVL) and
typing: "make". The program can then by run by the command "make run".

======================================
Features
======================================
This program features a looping menu with the following options:

"
1. Initialization
2. Find
3. Insert
4. Remove
5. Check Height and Size
6. Find All (above a given frequency)
7. Exit
"

It them prompts input from the user with the line:

"avl/> "

Initializing (1) the tree will prompt the user to input a text file with strings
separated by whitespace characters. The input file should be placed in the root
of the directory (/simpleAVL). The program will then store these characters
as individual nodes in an AVL tree. If a key has already been read in the tree,
the "count" within the node will be incremented by one.

Find (2) will attempt to find and display the count of a user inputted string in
the AVL tree.

Insert (3) will attempt to insert a key to the tree. If the key already exists,
its count is incremented by 1.

Remove (4) will attempt to decrement the count of a node by one. If the count is
1, then the node will be freed and the tree is rebalanced.

Check Height and Size (5) will cause the program to calculate and print out the
height of the (balanced) tree along with the number of nodes within the tree.

Find All (6) will print the information of all nodes above a user specified
frequency in the AVL tree.

Exit (7) will free all memory used by the AVL tree, close the input file and
cause the program to exit.

======================================
Limitations
======================================
The program can only store strings of length 255 or less.
The user should not attempt to initialize a tree twice.

The input file should be placed in the root of the directory (/simpleAVL).
