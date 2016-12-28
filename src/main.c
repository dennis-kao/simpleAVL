/**
 * Dennis Kao (Nov 19, 2016)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avltree.h"

int main () {

  char line[20];
  char fileName[20];
  FILE *input;
  Node *found;
  Node *root = NULL;
  Node *new;

  printf("======================================================\n");
  printf("\tWELCOME\n");
  printf("\tTHIS PROGRAM WAS WRITTEN BY: DENNIS KAO\n");
  printf("\tID: 0843603\n");
  printf("======================================================\n");

  do {

    printf("\t1. Initialization\n");
    printf("\t2. Find\n");
    printf("\t3. Insert\n");
    printf("\t4. Remove\n");
    printf("\t5. Check Height and Size\n");
    printf("\t6. Find All (above a given frequency)\n");
    printf("\t7. Exit\n");
    printf("avl/> ");

    scanf("%s", line);

    switch(line[0]) {

      case '1':

        printf("filename: ");
        scanf("%s", fileName);

        input = fopen(fileName, "r");
        if (input == NULL) {
          printf("Could not open input file: %s. Please try again.\n", fileName);
          break;
        }

        root = initializeTree(input, root);
        break;

      case '2':

        printf("find key: ");
        scanf("%s", line);

        found = search(root, line);

        if (found == NULL) printf("no_such_key\n");
        else printf("key: %s, frequency: %d\n", found->key, found->count);

        break;

      case '3':

        printf("insert key: ");

        scanf("%s", line);

        found = search(root, line);

        if (found == NULL) {

          new = newNode(line);

          root = insert(root, new);
          found = search(root, line); //always non null
        }
        else found->count++;

        printf("key: %s, frequency: %d\n", found->key, found->count);

        break;

      case '4':

        printf("remove key: ");

        scanf("%s", line);

        found = search(root, line);

        if (found == NULL) {
          printf("no_such_key\n");
        }
        else if (found->count > 1) {
          found->count--;
          printf("key: %s, frequency: %d\n", found->key, found->count);
        }
        else if (found->count == 1) {

          if (root == found && numChildren(root) == 0) {
            removeNode(root, found);
            root = NULL;
          }
          else {
            removeNode(root, found);
            root = balance(root);
          }

          printf("key: %s, frequency: 0\n", line);
        }

        break;

      case '5':
        printf("height: %d, size: %d\n", depth(root)-1, size(root));
        break;

      case '6':
        printf("frequency: ");

        scanf("%s", line);

        if (isAllNumbers(line)) {
          printFrequencyAbove(root, atoi(line));
        }
        else {
          printf("Invalid input.\n");
        }
        break;

      case '7':
        destroy(root);
        fclose(input);
        printf("Tree destroyed successfully. File closed successfully. Program exiting.\n");
        break;

      default:
        printf("Invalid input, please try again.\n");
        break;
    }
  } while (line[0] != '7');

  return 0;
}
