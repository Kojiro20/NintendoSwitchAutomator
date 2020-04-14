#include <stdio.h>
#include <scripts/scripts.h>

#include "tools.h"

static struct Node* getNet = NULL;
static struct Node* getShovel = NULL;
static struct Node* getAxe = NULL;
static struct Node* getStoneAxe = NULL;

struct Node* getTool(Tools_t tool) {
    struct Node* head = initializeNode(NOTHING, 0);
    struct Node* curr = head;

    curr = appendAction(curr, PAD_UP, 5, 15);
    curr = appendAction(curr, tool, 5, 10);
    curr = appendAction(curr, A, 10, 25);

    return head;
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
