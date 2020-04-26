#include <stdio.h>
#include "common.h"
#include "scripts.h"

#define STACK_DEPTH 5
#define SCRIPT_COUNT 5

static struct Node* head = NULL;
static struct Node* curr = NULL;
static struct Node* scripts[SCRIPT_COUNT];
static struct Node* stack[STACK_DEPTH];
static int stackIndex = 0;

/*
 * This is called once by joystick as the program initializes
 */
void InitializeGameScripts(void) {
    stackIndex = 0;

    // avoid null refs, default to reset state
    struct Node* reset = loadReset();
    for (int i = 0; i < SCRIPT_COUNT; i++) {
        scripts[i] = reset;
    }

    // initialize scripts
    scripts[1] = loadButtonMash();
    // scripts[2] = loadHarvestGrid(3, 10);
    scripts[2] = loadBranchCollector();
    // scripts[2] = loadBuyBulk();
    // scripts[3] = loadSelectBulk();
}

/*
 * This is called each time a new script is selected
 */
void SelectScript(int scriptNum) {
    if (scriptNum >= SCRIPT_COUNT) {
        scriptNum == 0;
    }

    head = scripts[scriptNum];
    curr = NULL;
    stackIndex = 0;
}

/*
 * This is called in the run-loop each time the joystick is ready
 * for a new command. It traverses a nested linked list, visiting
 * the current node - all children, then the next node.
 */
Command GetNextCommand(void) {

    // scan for the next non-empty next pointer on the stack
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
