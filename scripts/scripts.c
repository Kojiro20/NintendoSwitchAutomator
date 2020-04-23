#include <stdio.h>
#include <stdlib.h>
#include "scripts.h"
#include "AnimalCrossing/movement.h"
#include "AnimalCrossing/tools.h"
#include "AnimalCrossing/treeStuff.h"
#include "AnimalCrossing/shop.h"

/*
 * The main game scripts to be executed
 */
struct Node* loadReset() {
    struct Node* head = initializeNode(NOTHING, 0);
    appendAction(head, NOTHING, 5, 25);
    return head;
}

struct Node* loadButtonMash() {
    struct Node* head = initializeNode(NOTHING, 0);
    appendAction(head, A, 5, 0);
    return head;
}

struct Node* loadHarvestGrid(int rows, int cols) {
    struct Node* head = initializeNode(NOTHING, 0);
    struct Node* curr = head;
    
    curr->child = StowToolReset();
    curr = noOp(curr, 15);
    curr->child = HarvestFruitGrid(rows, cols);
    stop(curr);
    return head;
}

struct Node* loadBranchCollector() {
    struct Node* head = initializeNode(NOTHING, 0);
    struct Node* curr = head;
    
    curr->child = ShakeTreeAndCollect();
    return head;
}

struct Node* loadBranchSeller() {
    struct Node* head = initializeNode(NOTHING, 0);
    struct Node* curr = head;
    
    curr->child = StowToolReset();
    curr = noOp(curr, 15);
    curr->child = ShakeTreeAndSellBranches();
    return head;
}

struct Node* loadBuyBulk() {
    struct Node* head = initializeNode(NOTHING, 0);
    struct Node* curr = head;

    curr->child = BuyBulk();

    return head;
}

struct Node* loadSelectBulk() {
    struct Node* head = initializeNode(NOTHING, 0);
    struct Node* curr = head;

    curr->child = SelectBulk();
    stop(curr);

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

void stop(struct Node* curr) {
    curr = noOp(curr, 50);
    curr->next = curr;
}

/*
 * Helper for adding a new no-op node (in case a new child branch is needed)
 */
struct Node* noOp(struct Node* curr, uint16_t waitTime) {
    struct Node* delay = initializeNode(NOTHING, waitTime);
    curr->next = delay;
    return delay;
}

