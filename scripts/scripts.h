#ifndef _GAME_SCRIPTS_
#define _GAME_SCRIPTS_

#include <stdint.h>
#include "common.h"

struct Node {
    Command command;
    // int repeats;
    struct Node *next;
    struct Node *child;
};

struct Node* loadScript(void);
struct Node* initializeNode(Buttons_t button, uint16_t duration);
struct Node* appendAction(struct Node* curr, Buttons_t button, uint16_t duration, uint16_t waitTime);
struct Node* noOp(struct Node* curr, uint16_t waitTime);

#endif