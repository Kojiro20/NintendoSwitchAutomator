#include <stdio.h>
#include <scripts/scripts.h>

#include "tools.h"
#include "movement.h"

static struct Node* harvestFromTree = NULL;
static struct Node* collectAroundTree = NULL;
static int shakeTime = 35;
static int pickupTime = 25;
static int movementDist = 1;

struct Node* HarvestFromTree(void) {
    if (harvestFromTree == NULL) {
        harvestFromTree = initializeNode(NOTHING, 0);
        struct Node* curr = harvestFromTree;

        // put tool away
        curr = appendAction(curr, PAD_DOWN, 10, 20);

        // shake tree
        curr->child = FaceUp();
        curr = appendAction(curr, A, 15, shakeTime);

        // catch wasps if any fell
        curr->child = GetNet();
        curr = appendAction(curr, A, 15, shakeTime);
        curr = appendAction(curr, PAD_DOWN, 10, 20);

        // shake 3 more times
        curr->child = FaceUp();
        for (int i = 0; i < 3; i++) {
            curr = appendAction(curr, A, 5, shakeTime);
        }

        // chop 3 times with stone axe
        curr = noOp(curr, 10);
        curr->child = GetStoneAxe();
        curr = noOp(curr, 10);
        curr->child = FaceUp();
        for (int i = 0; i < 3; i++) {
            curr = appendAction(curr, A, 5, shakeTime);
        }
    }

    return harvestFromTree;
}

struct Node* CollectAroundTree(void) {
    if (collectAroundTree == NULL) {
        collectAroundTree = initializeNode(NOTHING, 0);
        struct Node* curr = collectAroundTree;

        // put tool away
        curr = appendAction(curr, PAD_DOWN, 10, 20);

        // pick up anything
        curr = appendAction(curr, Y, 5, pickupTime);

        // go left once
        curr->child = FaceLeft();
        curr = appendAction(curr, LEFT, movementDist, movementDist);
        curr = appendAction(curr, Y, 5, pickupTime);

        // go up twice
        curr->child = FaceUp();
        curr = appendAction(curr, UP, movementDist, movementDist);
        curr = appendAction(curr, Y, 5, pickupTime);
        curr = appendAction(curr, UP, movementDist, movementDist);
        curr = appendAction(curr, Y, 5, pickupTime);

        // go right twice
        curr->child = FaceRight();
        curr = appendAction(curr, RIGHT, movementDist, movementDist);
        curr = appendAction(curr, Y, 5, pickupTime);
        curr = appendAction(curr, RIGHT, movementDist, movementDist);
        curr = appendAction(curr, Y, 5, pickupTime);

        // go down twice
        curr->child = FaceDown();
        curr = appendAction(curr, DOWN, movementDist, movementDist);
        curr = appendAction(curr, Y, 5, pickupTime);
        curr = appendAction(curr, DOWN, movementDist, movementDist);
        curr = appendAction(curr, Y, 5, pickupTime);

        // go back to starting position
        curr->child = FaceLeft();
        curr = appendAction(curr, LEFT, 16, 16);
    }

    return collectAroundTree;
}