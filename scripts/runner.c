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
static long state = 0l;
Command delay = { NOTHING, 0 };
char shouldDelay = 0;

/*
 * This is called once by joystick as the program initializes
 */
void InitializeGameScripts(void) {
    stackIndex = 0;

    // Initialize starting nodes
    for (int i = 0; i < SCRIPT_COUNT; i++) {
         scripts[i] = initializeNode(NOTHING, 1, 1);
    }

    // One button press: button mash `A` indefinitely
    scripts[1]->child = initializeNode(A, 5, 25);

    // Two button presses: tell the dodo to open the gates
    scripts[2]->child = OpenGate();

    // Three button presses: tell the todo to travel online (will stop before picking dodo-code or friends)
    scripts[3]->child = Travel();

    // Clone 1x1 Items
    scripts[4]->child = Clone1x1Items();

    // Sell 40 items (N times)
    scripts[5]->child = Sell40ItemsNTimes(3);

    // Clone and sell 80 items
    scripts[6]->child = CloneAndSell80Items();
}

/*
 * This is called each time a new script is selected
 */
void SelectScript(int scriptNum) {
    if (scriptNum >= SCRIPT_COUNT) {
        scriptNum = 0;
    }

    head = scripts[scriptNum];
    curr = NULL;
    stackIndex = 0;
    state = 0l;
}

/*
 * Maintains repeat state and determines if the current node should be repeated
 */
struct Node* getNextWithRepeat(struct Node* node) {
    if (node->repeat == NULL) {
        return node->next;
    }

    // if the node's state is greater than current state, a reset must have occured
    if (node->repeat->repeatState > state) {
        node->repeat->repeatCount = 0;
    }

    // assign state and increment number of iterations
    node->repeat->repeatState = state;
    node->repeat->repeatCount++;

    // if the node's repeat count state is greater than the target, reset
    if (node->repeat->repeatCount > node->repeat->repeatTarget) {
        node->repeat->repeatCount = 1;
    }

    // check if it has been sufficiently repeated
    if (node->repeat->repeatCount == node->repeat->repeatTarget) {
        return node->next;
    } else {
        return node;
    }
}

/*
 * This is called in the run-loop each time the joystick is ready
 * for a new command. It traverses a nested linked list, visiting
 * the current node - all children, then the next node.
 */
Command GetNextCommand(void) {
    state++;
    
    // cycle between returning a no-op and fetching something from the list
    if (shouldDelay) {
        shouldDelay = 0;
        return delay;
    }

    // scan for the next non-empty next pointer on the stack
    while (curr == NULL) {
        if (stackIndex == 0) {
            curr = head; // reset if we reached the end, this could also stop
            state = 0;
        } else {
            stackIndex--;
            curr = getNextWithRepeat(stack[stackIndex]);
        }
    }

    // execute the current node's command
    Command res = curr->command;

    // update the next delay cycle
    delay.duration = curr->waitTime;
    shouldDelay = 1;

    // if a child branch exists, follow it and add this node to the stack
    if (curr->child != NULL) {
        stack[stackIndex] = curr;
        stackIndex++;
        curr = curr->child;
    } else {
        curr = getNextWithRepeat(curr);
    }

    state++;
    return res;
}
