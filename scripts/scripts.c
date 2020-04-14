#include <stdio.h>
#include <stdlib.h>
#include "scripts.h"
#include "AnimalCrossing/movement.h"
#include "AnimalCrossing/tools.h"
// #include "AnimalCrossing/harvestFromTree.h"

/*
 * The main game script to be executed
 */
struct Node* loadScript(void) {
    struct Node* head = initializeNode(NOTHING, 0);
    struct Node* curr = head;

    // move down
    curr = appendAction(curr, DOWN, 20, 20);

    // face up
    curr->child = FaceUp();

    // move left
    curr = appendAction(curr, LEFT, 20, 20);

    // swing axe
    curr->child = GetAxe();
    curr = appendAction(curr, A, 5, 50);

    // move up
    curr = appendAction(curr, UP, 20, 20);

    // face down
    curr->child = FaceDown();

    // move right
    curr = appendAction(curr, RIGHT, 20, 20);

    // dig hole
    curr->child = GetShovel();
    curr = appendAction(curr, A, 5, 50);

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

