#include <stdio.h>
#include <scripts/scripts.h>

static struct Node* buyBulk = NULL;
static struct Node* selectBulk = NULL;

struct Node* BuyBulk() {
    if (buyBulk == NULL) {
        buyBulk = initializeNode(NOTHING, 0);
        struct Node* curr = buyBulk;
        // TODO: figure out why this extra first command needed
        curr = appendAction(curr, X, 0, 0);

        // TODO: figure out a way to make this loop work (seems the 60 is too large)
        // for (int i = 0; i < 60; i++) {
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
        // }
    }

    return buyBulk;
}

struct Node* SelectBulk() {
    if (selectBulk == NULL) {
        selectBulk = initializeNode(NOTHING, 0);
        struct Node* curr = selectBulk;
        curr = appendAction(curr, X, 0, 0);

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 10; j++) {
                curr = appendAction(curr, A, 5, 0);
                curr = appendAction(curr, RIGHT, 10, 0);
            }
            curr = appendAction(curr, DOWN, 10, 0);
        }
    }

    return selectBulk;
}
