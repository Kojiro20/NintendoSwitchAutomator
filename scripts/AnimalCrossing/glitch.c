#include <stdio.h>
#include <scripts/scripts.h>

#include "tools.h"
#include "movement.h"

struct Node* GlitchTableMoveRight(void) {
    struct Node* head = initializeNode(NOTHING, 0, 0);
    struct Node* curr = head;

    // press L to select bottom item (table)
    curr = appendAction(curr, L, 15, 10);

    // move the table over one grid space
    curr = appendAction(curr, DRAG_RIGHT, 10, 15);

    // fetch the glitched item-to-clone
    curr = appendAction(curr, LEFT, 11, 15);
    curr = appendAction(curr, UP, 5, 15);
    curr = appendAction(curr, DRAG_RIGHT, 10, 15);

    return head;
}

struct Node* PickUpAndMoveRight(void) {
    struct Node* head = initializeNode(NOTHING, 0, 0);
    struct Node* curr = head;

    // grab to re-anchor cursor to center of item
    curr = appendAction(curr, A, 10, 30);

    // pick up item
    curr = appendAction(curr, Y, 10, 15);

    // move to next
    curr = appendAction(curr, RIGHT, 6, 1);

    return head;
}

/*
 * Pre-requisites:
 *   - room setup, prepare glitch table with empty spot in top left
 *   - set up room with tables, glitch table, and the item to clone
 *
 *     .   .   .   .   .   .
 *    .┌--------------------┐
 *     │╔══╗                │
 *    .│╚══╝ <- glitch table│
 *     │                    │
 *    .│                    │
 *     │╔══╗╔══╗╔══╗╔══╗    │
 *    .│╚══╝╚══╝╚══╝╚══╝   X <-- item to clone
 *     └-------┐   ┌--------┘
 *      entry >--┘
 */
struct Node* Clone1x1Items(void) {

    // initialize sub routines
    struct Node* glitchTableMoveRight = GlitchTableMoveRight();
    struct Node* pickUpAndMoveRight = PickUpAndMoveRight();

    // create cloning start node
    struct Node* head = initializeNode(NOTHING, 0, 0);
    struct Node* curr = head;

    // close things
    curr = appendAction(curr, B, 5, 20);
    repeatAction(curr, 3);

    // go into decoration mode
    curr = appendAction(curr, PAD_DOWN, 5, 40);
    repeatAction(curr, 3);

    // move cursor to the bottom right (this is where the item-to-clone starts)
    curr = appendAction(curr, RIGHT, 40, 0);
    curr = appendAction(curr, DOWN, 40, 0);

    // drag the item to the top left (glitch table should be here already)
    curr = appendAction(curr, DRAG_LEFT, 75, 15);
    curr = appendAction(curr, DRAG_UP, 40, 15);

    // perform individual clone 7 times
    curr = appendAction(curr, NOTHING, 0, 0);
    curr->child = glitchTableMoveRight;
    repeatAction(curr, 7);

    // move the table down one grid space, then back to the left side
    curr = appendAction(curr, L, 15, 10);
    curr = appendAction(curr, DRAG_DOWN, 10, 15);
    curr = appendAction(curr, DRAG_LEFT, 60, 15);

    // retrieve the 8th cloned item
    curr = appendAction(curr, UP, 10, 0);
    curr = appendAction(curr, RIGHT, 50, 0);
    curr = appendAction(curr, DRAG_DOWN, 10, 15);
    curr = appendAction(curr, DRAG_LEFT, 60, 15);

    // extra L to offset selection
    curr = appendAction(curr, L, 15, 10);

    // perform individual clone 7 times
    curr = appendAction(curr, NOTHING, 0, 0);
    curr->child = glitchTableMoveRight;
    repeatAction(curr, 7);

    // move the table over and down one grid space
    curr = appendAction(curr, L, 15, 10);
    curr = appendAction(curr, DRAG_RIGHT, 10, 15);
    curr = appendAction(curr, DRAG_DOWN, 10, 15);

    // put the crown back in the bottom right
    curr = appendAction(curr, UP, 10, 0);
    curr = appendAction(curr, LEFT, 10, 2);
    curr = appendAction(curr, DRAG_DOWN, 40, 15);
    curr = appendAction(curr, DRAG_RIGHT, 20, 15);

    // move tables up to catch cloned items
    curr = appendAction(curr, LEFT, 15, 0);
    curr = appendAction(curr, DRAG_UP, 40, 15);
    curr = appendAction(curr, LEFT, 15, 0);
    curr = appendAction(curr, DOWN, 40, 0);
    curr = appendAction(curr, DRAG_UP, 40, 15);
    curr = appendAction(curr, LEFT, 15, 0);
    curr = appendAction(curr, DOWN, 40, 0);
    curr = appendAction(curr, DRAG_UP, 40, 15);
    curr = appendAction(curr, LEFT, 15, 0);
    curr = appendAction(curr, DOWN, 40, 0);
    curr = appendAction(curr, DRAG_UP, 40, 15);

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

    // move cursor to the top left
    curr = appendAction(curr, LEFT, 50, 0);
    curr = appendAction(curr, UP, 50, 0);

    // pick up items
    curr = appendAction(curr, NOTHING, 0, 0);
    curr->child = pickUpAndMoveRight;
    repeatAction(curr, 8);

    // move cursor to the left and down one row
    curr = appendAction(curr, LEFT, 70, 0);
    curr = appendAction(curr, DOWN, 5, 0);

    // pick up items
    curr = appendAction(curr, NOTHING, 0, 0);
    curr->child = pickUpAndMoveRight;
    repeatAction(curr, 8);

    // move cursor to the top left
    curr = appendAction(curr, LEFT, 70, 0);
    curr = appendAction(curr, UP, 20, 0);

    // move tables back down
    curr = appendAction(curr, DRAG_DOWN, 40, 15);
    curr = appendAction(curr, RIGHT, 15, 0);
    curr = appendAction(curr, UP, 40, 0);
    curr = appendAction(curr, DRAG_DOWN, 40, 15);
    curr = appendAction(curr, RIGHT, 15, 0);
    curr = appendAction(curr, UP, 40, 0);
    curr = appendAction(curr, DRAG_DOWN, 40, 15);
    curr = appendAction(curr, RIGHT, 15, 0);
    curr = appendAction(curr, UP, 40, 0);
    curr = appendAction(curr, DRAG_DOWN, 40, 15);

    // move glitch table back to top left
    curr = appendAction(curr, UP, 20, 0);
    curr = appendAction(curr, RIGHT, 20, 0);
    curr = appendAction(curr, L, 15, 25);
    curr = appendAction(curr, DRAG_UP, 30, 15);
    curr = appendAction(curr, DRAG_LEFT, 70, 15);

    return head;
}
