#include <stdio.h>
#include <scripts/scripts.h>

#include "tools.h"
#include "movement.h"

static struct Node* cloneItem = NULL;

struct Node* CloneItem(void) {
    if (cloneItem == NULL) {
        cloneItem = initializeNode(NOTHING, 0, 0);
        struct Node* curr = cloneItem;

        // go into decoration mode
        curr = appendAction(curr, NOTHING, 5, 30);
        curr = appendAction(curr, PAD_DOWN, 5, 80);

        // move cursor to the bottom right
        curr = appendAction(curr, RIGHT, 40, 0);
        curr = appendAction(curr, DOWN, 40, 0);
        
        // press L to select bottom item (table)
        curr = appendAction(curr, L, 5, 10);

        // drag left 3, and up 1
        curr = appendAction(curr, DRAG_LEFT, 20, 25);
        curr = appendAction(curr, DRAG_UP, 15, 25);

        // pick it up again and clone to the right side
        curr = appendAction(curr, DOWN, 5, 0);
        curr = appendAction(curr, DRAG_RIGHT, 10, 25);
        curr = appendAction(curr, DRAG_UP, 15, 25);

        // pick it up again and put it back in the bottom right corner
        curr = appendAction(curr, RIGHT, 3, 0);
        curr = appendAction(curr, DRAG_RIGHT, 20, 25);
        curr = appendAction(curr, DRAG_DOWN, 20, 25);

        // exit decoration mode
        curr = appendAction(curr, B, 15, 10);

        // leave the room
        curr = appendAction(curr, NOTHING, 0, 0);
        curr->child = FaceLeft();
        curr = appendAction(curr, LEFT, 3 * 15, 300);

        // re-enter the room
        curr = appendAction(curr, NOTHING, 0, 0);
        curr->child = FaceRight();
        curr = appendAction(curr, RIGHT, 3 * 15, 300);

        // go into decoration mode
        curr = appendAction(curr, PAD_DOWN, 5, 80);

        // collect clones
        curr = appendAction(curr, NOTHING, 5, 10);
        curr = appendAction(curr, Y, 10, 30);
        curr = appendAction(curr, RIGHT, 10, 0);
        curr = appendAction(curr, UP, 5, 30);
        curr = appendAction(curr, Y, 10, 30);
    }

    return cloneItem;
}
