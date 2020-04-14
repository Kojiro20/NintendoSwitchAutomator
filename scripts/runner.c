#include <stdio.h>
#include "common.h"
#include "scripts.h"

#define STACK_DEPTH 5

static struct Node* head = NULL;
static struct Node* curr = NULL;
static struct Node* stack[STACK_DEPTH];
static int stackIndex = 0;

void InitializeGameScript(void) {
    stackIndex = 0;
    head = loadScript();
}

Command GetNextCommand(void) {
    while (curr == NULL) {
        if (stackIndex == 0) {
            curr = head; // reset if we reached the end, this could also stop
        } else {
            stackIndex--;
            curr = stack[stackIndex]->next;
        }
    }

    // execute the current node's command
    Command res = curr->command;

    // if a child branch exists, follow it and add this node to the stack
    if (curr->child != NULL) {
        stack[stackIndex] = curr;
        stackIndex++;
        curr = curr->child;
    } else {
        curr = curr->next;
    }

    return res;
}
