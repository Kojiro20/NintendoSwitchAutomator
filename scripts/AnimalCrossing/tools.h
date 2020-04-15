#ifndef _SCRIPTS_AC_TOOLS_
#define _SCRIPTS_AC_TOOLS_

#include <scripts/scripts.h>

// tools enumeration (mapping may change per player)
typedef enum {
    NET = UP,
    SHOVEL = DOWN,
    AXE = DOWN_RIGHT,
    STONE_AXE = DOWN_LEFT,
} Tools_t;

struct Node* GetNet(void);
struct Node* GetShovel(void);
struct Node* GetAxe(void);
struct Node* GetStoneAxe(void);

#endif