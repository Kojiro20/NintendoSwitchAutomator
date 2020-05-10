#ifndef _GAME_SCRIPTS_
#define _GAME_SCRIPTS_

#include <stdint.h>
#include "common.h"
#include "AnimalCrossing/movement.h"
#include "AnimalCrossing/shop.h"
#include "AnimalCrossing/tools.h"
#include "AnimalCrossing/trees.h"
#include "AnimalCrossing/glitch.h"
#include "AnimalCrossing/dodo.h"

/*
 * Internal scripting tools. Anything generic to all games would go here.
 * Game-specific macros belong in subfolders.
 */
struct RepeatingNode {
    int repeatTarget;
    int repeatCount;
    long repeatState;
};
struct Node {
    Command command;
    struct RepeatingNode *repeat;
    struct Node *next;
    struct Node *child;
    uint16_t waitTime;
};

struct Node* initializeNode(Buttons_t button, uint16_t duration, uint16_t waitTime);
struct Node* appendAction(struct Node* curr, Buttons_t button, uint16_t duration, uint16_t waitTime);
void repeatAction(struct Node* curr, int repeats);
void stop(struct Node* curr);
#endif