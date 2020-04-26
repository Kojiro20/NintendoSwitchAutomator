#ifndef _AC_TOOLS_
#define _AC_TOOLS_

#include <scripts/scripts.h>

// tools enumeration (mapping may change per player)
typedef enum {
    NET = UP,
    SHOVEL = DOWN,
    AXE = DOWN_RIGHT,
    STONE_AXE = DOWN_LEFT,
    SLINGSHOT = UP_RIGHT,
} Tools_t;

struct Node* StowToolReset(void);
struct Node* GetNet(void);
struct Node* GetShovel(void);
struct Node* GetAxe(void);
struct Node* GetStoneAxe(void);
struct Node* GetSlingShot(void);

#endif