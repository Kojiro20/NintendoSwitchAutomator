#include <stdio.h>
#include <stdlib.h>
#include "scripts.h"
#include "AnimalCrossing/movement.h"
#include "AnimalCrossing/tools.h"
#include "AnimalCrossing/treeStuff.h"

/*
 * The main game script to be executed
 */
struct Node* loadScript(int scriptNum) {
    struct Node* head = initializeNode(NOTHING, 10);
    struct Node* curr = head;

    int rows = 3;
    int cols = 3;

    switch (scriptNum) {
        case 1:
            // collect stars
            curr = appendAction(curr, A, 5, 10);
            break;
        case 2:

            curr->child = HarvestFruitGrid(3, 10);
            curr = noOp(curr, 10000000);

            break;

        case 3:
            curr = appendAction(curr, B, 5, 10);
            curr = appendAction(curr, PAD_DOWN, 5, 10);
            curr->child = RunInCircle();
        default:
            // collect stars
            curr->child = RunInCircle();
    }

    return head;
}

/*
 * Helper to initialize new nodes
 */
struct Node* initializeNode(Buttons_t button, uint16_t duration) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->command = (Command) { (Buttons_t) button, duration };
    node->next = NULL;
    node->child = NULL;
    return node;
}

/*
 * Helper to append a new action
 */
struct Node* appendAction(struct Node* curr, Buttons_t button, uint16_t duration, uint16_t waitTime) {
    struct Node* next = initializeNode(button, duration);
    curr->next = next;

    // follow each action with a no-op to reset joystick and buttons
    return noOp(next, waitTime);
}

/*
 * Helper for adding a new no-op node (in case a new child branch is needed)
 */
struct Node* noOp(struct Node* curr, uint16_t waitTime) {
    struct Node* delay = initializeNode(NOTHING, waitTime);
    curr->next = delay;
    return delay;
}

