#ifndef _GAME_SCRIPTS_
#define _GAME_SCRIPTS_

#include <stdint.h>
#include "common.h"

/*
 * Internal scripting tools. Anything generic to all games would go here.
 * Game-specific macros belong in subfolders.
 */

// TODO: it should be possible to add a 'repeat' field to nodes
// allowing things to be repeated without extra memory use.
struct Node {
    Command command;
    // int repeats;
    struct Node *next;
    struct Node *child;
};

struct Node* loadReset();
struct Node* loadButtonMash();
struct Node* loadHarvestGrid(int rows, int cols);
struct Node* loadBranchSeller();
struct Node* loadBranchCollector();
struct Node* loadBuyBulk();
struct Node* loadSelectBulk();
struct Node* loadScript(int scriptNum);
struct Node* initializeNode(Buttons_t button, uint16_t duration);
struct Node* appendAction(struct Node* curr, Buttons_t button, uint16_t duration, uint16_t waitTime);
struct Node* noOp(struct Node* curr, uint16_t waitTime);
void stop(struct Node* curr);

#endif