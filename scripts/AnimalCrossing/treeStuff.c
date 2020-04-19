#include <stdio.h>
#include <scripts/scripts.h>

#include "tools.h"
#include "movement.h"

static struct Node* harvestFromTree = NULL;
static struct Node* collectAroundTree = NULL;
static struct Node* goToTreeAbove = NULL;

static int shakeTime = 30;
static int pickupTime = 30;
static int movementDist = 13;

struct Node* HarvestFromTree(void) {
    if (harvestFromTree == NULL) {
        harvestFromTree = initializeNode(NOTHING, 0);
        struct Node* curr = harvestFromTree;

        // put tool away
        curr = appendAction(curr, PAD_DOWN, 10, 20);

        // shake tree
        curr->child = FaceUp();
        curr = appendAction(curr, A, 15, shakeTime);
    }

    return harvestFromTree;
}

struct Node* CollectAroundTree(void) {
    if (collectAroundTree == NULL) {
        collectAroundTree = initializeNode(NOTHING, 0);
        struct Node* curr = collectAroundTree;

        // pick up anything
        curr = appendAction(curr, Y, 5, 5);
        curr = appendAction(curr, Y, 5, pickupTime);

        // go to next fruit
        curr->child = FaceLeft();
        curr = appendAction(curr, LEFT, movementDist, movementDist);
        curr->child = FaceUp();
        curr = appendAction(curr, Y, 5, pickupTime);
        curr = appendAction(curr, UP, movementDist, movementDist);
        curr = appendAction(curr, Y, 5, pickupTime);

        // go to last fruit
        curr = appendAction(curr, UP, movementDist, movementDist);
        curr->child = FaceRight();
        curr = appendAction(curr, RIGHT, movementDist, movementDist);
        curr = appendAction(curr, RIGHT, movementDist, movementDist);
        curr->child = FaceDown();
        curr = appendAction(curr, Y, 5, pickupTime);
        curr = appendAction(curr, DOWN, movementDist, movementDist);
        curr = appendAction(curr, Y, 5, pickupTime);

        // go back to front
        curr = appendAction(curr, DOWN, movementDist, movementDist);
        curr->child = FaceLeft();
        curr = appendAction(curr, Y, 5, pickupTime);
        curr = appendAction(curr, LEFT, movementDist, movementDist);
    }

    return collectAroundTree;
}

struct Node* GoToTreeAbove(void) {
    if (goToTreeAbove == NULL) {
        goToTreeAbove = initializeNode(NOTHING, 0);
        struct Node* curr = goToTreeAbove;

        // go to tree above
        curr->child = FaceRight();
        curr = appendAction(curr, RIGHT, movementDist, movementDist);
        curr->child = FaceUp();
        curr = appendAction(curr, UP, movementDist, movementDist);
        curr = appendAction(curr, UP, movementDist, movementDist);
        curr->child = FaceLeft();
        curr = appendAction(curr, LEFT, movementDist, movementDist);
    }

    return goToTreeAbove;
}

/*
 * Note: be careful calling this as it will allocate new memory each time
 * Eventually TODO: add a repeat field to nodes and update the runner.
 */
struct Node* HarvestFruitGrid(int rows, int cols) {
    struct Node* head = initializeNode(NOTHING, 0);
    struct Node* curr = head;
    
    // put tool away
    curr = appendAction(curr, PAD_DOWN, 5, 15);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // collect from a tree immediately in front of character
            curr->child = HarvestFromTree();
            curr = noOp(curr, 0);
            curr->child = CollectAroundTree();
            curr = noOp(curr, 0);

            // go left and then repeat
            if ((j+1) < cols) {
                curr = appendAction(curr, LEFT, 24, 28);
            }
        }

        // go back to start of row
        curr->child = FaceRight();
        curr = appendAction(curr, RIGHT, (cols-1) * 24, cols * 24);

        if ((i+1) < rows) {
            curr = noOp(curr, 0);
            curr->child = GoToTreeAbove();
        }

        curr = noOp(curr, 5);
        curr = noOp(curr, 5);
    }

    return head;
}