#include <stdio.h>
#include <scripts/scripts.h>

#include "tools.h"

static struct Node* stowTool = NULL;
static struct Node* getNet = NULL;
static struct Node* getShovel = NULL;
static struct Node* getAxe = NULL;
static struct Node* getStoneAxe = NULL;
static struct Node* getSlingshot = NULL;

struct Node* getTool(Tools_t tool) {
    struct Node* head = initializeNode(NOTHING, 0);
    struct Node* curr = head;

    // TODO: need to find the smallest delay times where this is reliable
    curr = appendAction(curr, PAD_UP, 10, 10);
    curr = appendAction(curr, tool, 10, 10);
    curr = appendAction(curr, A, 5, 30);

    return head;
}

struct Node* StowToolReset() {
    if (stowTool == NULL) {
        stowTool = initializeNode(NOTHING, 0);
        struct Node* curr = stowTool;

        // cancel dialogs
        for (int i = 0; i < 3; i++) {
            curr = appendAction(curr, B, 5, 10);
        }

        // stow
        curr = appendAction(curr, PAD_DOWN, 5, 15);
    }

    return stowTool;
}

struct Node* GetNet() {
    if (getNet == NULL) {
        getNet = getTool(NET);
    }

    return getNet;
}

struct Node* GetShovel() {
    if (getShovel == NULL) {
        getShovel = getTool(SHOVEL);
    }

    return getShovel;
}

struct Node* GetAxe() {
    if (getAxe == NULL) {
        getAxe = getTool(AXE);
    }

    return getAxe;
}

struct Node* GetStoneAxe() {
    if (getStoneAxe == NULL) {
        getStoneAxe = getTool(STONE_AXE);
    }

    return getStoneAxe;
}

struct Node* GetSlingShot() {
    if (getSlingshot == NULL) {
        getSlingshot = getTool(SLINGSHOT);
    }

    return getSlingshot;
}
