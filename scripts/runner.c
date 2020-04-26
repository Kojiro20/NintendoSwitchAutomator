#include <stdio.h>
#include "common.h"
#include "scripts.h"

#define STACK_DEPTH 10
#define SCRIPT_COUNT 10

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

    // Initialize starting nodes
    for (int i = 0; i < SCRIPT_COUNT; i++) {
        scripts[i] = initializeNode(NOTHING, 0);
    }

    // Initial entry does nothing and is used as a reset when scripts are off
    appendAction(scripts[0], NOTHING, 5, 25);

    // One button press: button mash `A`
    appendAction(scripts[1], NOTHING, 5, 25);

    // Two button presses: shake a tree 30x and collect everything that falls
    scripts[2]->child = ShakeTreeAndCollect();

    // Three button presses: buy the last purchased item in bulk from nooks crany
    scripts[3]->child = BuyBulk();

    // Four button presses: select all inventory
    scripts[4]->child = SelectBulk();

    // Five button presses: collect everything on the ground in a 10x10 starting bottom right
    // scripts[5] = TBD
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
