#include <stdio.h>
#include <scripts/scripts.h>

#include "tools.h"
#include "movement.h"

static struct Node* harvestFromTree = NULL;
static struct Node* collectAroundTree = NULL;
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
        curr = appendAction(curr, UP, movementDist, movementDist);
        curr = appendAction(curr, Y, 5, pickupTime);

        // go to last fruit
        curr = appendAction(curr, UP, movementDist, movementDist);
        curr->child = FaceRight();
        curr = appendAction(curr, RIGHT, movementDist, movementDist);
        curr = appendAction(curr, RIGHT, movementDist, movementDist);
        curr->child = FaceDown();
        curr = appendAction(curr, DOWN, movementDist, movementDist);
        curr = appendAction(curr, Y, 5, pickupTime);

        // go back to front
        curr = appendAction(curr, DOWN, movementDist, movementDist);
        curr->child = FaceLeft();
        curr = appendAction(curr, LEFT, movementDist, movementDist);
    }

    return collectAroundTree;
}