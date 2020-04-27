#include <stdio.h>
#include <scripts/scripts.h>

static struct Node* buyBulk = NULL;
static struct Node* selectBulk = NULL;

struct Node* BuyBulk(void) {
    if (buyBulk == NULL) {
        struct Node* start = initializeNode(NOTHING, 0, 0);
        struct Node* curr = start;
        // TODO: figure out why this extra first command needed
        curr = appendAction(curr, X, 0, 0);
        // Select item to buy
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 35, 0);
        // I can sell in singles or bulk, how many would you like
        curr = appendAction(curr, A, 5, 5);
        // Show choices
        curr = appendAction(curr, DOWN, 10, 0);
        // I'll take 5
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 35, 0);
        // Excellent purchase! ...purchase!
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 20, 0);
        // Anything else look interesting?
        curr = appendAction(curr, A, 5, 5);
        
        buyBulk = initializeNode(NOTHING, 0, 0);
        repeatAction(buyBulk, 60);
        buyBulk->child = start;
    }

    return buyBulk;
}

struct Node* SelectBulk(void) {
    if (selectBulk == NULL) {
        selectBulk = initializeNode(NOTHING, 0, 0);
        struct Node* curr = selectBulk;

        // start from bottom-left of inventory
        curr = appendAction(curr, DOWN, 2, 2);
        repeatAction(curr, 4);
        curr = appendAction(curr, LEFT, 2, 2);

        // repeat column selection 4 times
        curr = appendAction(curr, UP, 2, 10);
        repeatAction(curr, 4);

        // repeat row/item selection 10 times
        curr->child = initializeNode(NOTHING, 0, 0);
        repeatAction(curr->child, 10);
        curr->child->child = initializeNode(NOTHING, 0, 0);
        appendAction(appendAction(curr->child->child, A, 2, 5), RIGHT, 2, 2);
    }

    return selectBulk;
}
