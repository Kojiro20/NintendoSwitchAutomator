#include <stdio.h>
#include <stdlib.h>
#include "scripts.h"

/*
 * Helper to initialize new nodes
 */
struct Node* initializeNode(Buttons_t button, uint16_t duration, uint16_t waitTime) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->command = (Command) { (Buttons_t) button, duration };
    node->repeat = NULL;
    node->next = NULL;
    node->child = NULL;
    node->waitTime = waitTime;
    return node;
}

/*
 * Helper to append a new action
 */
struct Node* appendAction(struct Node* curr, Buttons_t button, uint16_t duration, uint16_t waitTime) {
    struct Node* node = initializeNode(button, duration, waitTime);
    curr->next = node;
    return node;
}

/*
 * Helper to repeat a node
 */
void repeatAction(struct Node* curr, int repeats) {
    if (repeats > 0) {
        struct RepeatingNode* repeat = (struct RepeatingNode*)malloc(sizeof(struct RepeatingNode));
        repeat->repeatCount = 0;
        repeat->repeatTarget = repeats;
        repeat->repeatState = 0l;
        curr->repeat = repeat;
    }
}

/*
 * Add a noOp cycle to the end to stop a script that should not repeat
 */
void stop(struct Node* curr) {
    struct Node* end = initializeNode(NOTHING, 50, 50);
    
    // create a cycle
    end->next = end;

    // assign it to the curr node's next pointer
    curr->next = end;
}
