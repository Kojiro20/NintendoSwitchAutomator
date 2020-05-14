#include <stdio.h>
#include <scripts/scripts.h>

#include "tools.h"
#include "movement.h"

struct Node* _GlitchTableMoveRight(void) {
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

struct Node* _PickUpAndMoveRight(void) {
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
 *   - prepare glitch table with empty spot in top left
 *   - set up basement with tables, glitch table, and the item to clone
 *
 *     .   .   .   .   .   .
 *    .┌--------------------┐
 *     │╔══╗                │
 *    .│╚══╝ <- glitch table│
 *     │                    │
 *    .│                    │
 *     │╔══╗╔══╗╔══╗╔══╗    │
 *    .│╚══╝╚══╝╚══╝╚══╝   x│ <-- item to clone
 *     └-------┐   ┌--------┘
 *      entry >--┘
 */
struct Node* Clone1x1Items(void) {

    // initialize sub routines
    struct Node* glitchTableMoveRight = _GlitchTableMoveRight();
    struct Node* pickUpAndMoveRight = _PickUpAndMoveRight();

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

    // exit decoration mode and re-enter to ensure selector state is reset
    // there is an issue where it sometimes will start selecting the table
    // but, when it first enters decoration mode it will select things on the table
    curr = appendAction(curr, B, 5, 20);
    repeatAction(curr, 3);
    curr = appendAction(curr, PAD_DOWN, 5, 40);
    repeatAction(curr, 3);

    // move glitch table back to top left
    curr = appendAction(curr, RIGHT, 40, 0);
    curr = appendAction(curr, L, 15, 25);
    curr = appendAction(curr, DRAG_UP, 30, 15);
    curr = appendAction(curr, DRAG_LEFT, 70, 15);

    return head;
}



struct Node* _SelectNext40Items(void) {
    
    // create a row selector node that selects 8 items
    struct Node* rowSelector = initializeNode(NOTHING, 0, 0);
    repeatAction(rowSelector, 8);
    rowSelector->child = initializeNode(NOTHING, 0, 0);
    struct Node* c = rowSelector->child;
    c = appendAction(c, A, 5, 10); // move to pockets?
    c = appendAction(c, A, 5, 7); // yes
    c = appendAction(c, RIGHT, 5, 7); // next

    // create a move-down node that repeates 5 times
    struct Node* moveDown = initializeNode(DOWN, 5, 5);
    repeatAction(moveDown, 5);
    moveDown->child = rowSelector;

    return moveDown;
}


struct Node* _GoFromHomeToNookMart(void) {
    struct Node* head = initializeNode(NOTHING, 0, 0);
    struct Node* curr = head;

    curr->child = FaceRight();
    curr = appendAction(curr, RIGHT, 4 * 12, 0);
    curr->child = FaceUp();
    curr = appendAction(curr, UP, 10, 0);

    return head;
}

struct Node* _GoFromNookMartToHome(void) {
    struct Node* head = initializeNode(NOTHING, 0, 0);
    struct Node* curr = head;

    curr->child = FaceLeft();
    curr = appendAction(curr, LEFT, 4 * 12, 0);
    curr->child = FaceUp();
    curr = appendAction(curr, UP, 10, 0);

    return head;
}

struct Node* _SellInventoryToDropBox(void) {
    struct Node* head = initializeNode(NOTHING, 10, 0);
    struct Node* curr = head;

    // create a row selector node that selects 8 items
    struct Node* rowSelector = initializeNode(NOTHING, 0, 0);
    repeatAction(rowSelector, 10);
    rowSelector->child = initializeNode(NOTHING, 0, 0);
    struct Node* c = rowSelector->child;
    c = appendAction(c, A, 5, 2); // select
    c = appendAction(c, RIGHT, 5, 2); // next
    appendAction(rowSelector, DOWN, 5, 5);

    // create a move-down node that repeates 5 times
    struct Node* moveDown = initializeNode(NOTHING, 5, 5);
    repeatAction(moveDown, 4);
    moveDown->child = rowSelector;

    // standing in front to of the dropbox
    curr = appendAction(curr, A, 5, 5);
    repeatAction(curr, 3);
    curr = appendAction(curr, A, 5, 150); // wow it's the dropbox
    curr = appendAction(curr, A, 5, 50); // yes sell
    curr = appendAction(curr, A, 5, 100); // still want to sell

    // go to top of menu
    curr = appendAction(curr, PAD_UP, 5, 10);
    repeatAction(curr, 5);

    // select items
    curr = appendAction(curr, NOTHING, 5, 5);
    curr->child = moveDown;

    // confirm
    curr = appendAction(curr, PLUS, 5, 15);
    curr = appendAction(curr, A, 5, 100);

    return head;
}

/*
 * Pre-requisites:
 *   - place house next to the nook mart
 *   - build a fence to keep NPCs out
 *   - empty pockets
 *   - enter house and don't move
 *   - open home inventory, find the number of the row of items to sell
 *     that row and the following 5 will be sold n times
 *   - select the top row of the category you will sell from
 *   - be careful looping this
 * 
 *                  ┌--- as close as possible
 *                  v
 *    .   .   .   .   .   .   .   .   .
 *     ┌-----------┐  ┌---------------┐
 *    .│   Home    │  │   Nook Mart   │
 * ╔═══│           │══│               │
 * ║  .└---┐   ┌---┘  └░░--┐     ┌----┘
 * ║         ^          ^            ║ <- NPC fence
 * ║ entry --┘          └-- drop box ║
 * ╚═════════════════════════════════╝
 */
struct Node* Sell40Items(int startRow, int times) {
    struct Node* head = initializeNode(NOTHING, 0, 0);
    struct Node* curr = head;

    // ensure home inventory is open
    curr = appendAction(curr, B, 15, 5);
    repeatAction(curr, 3);
    curr = appendAction(curr, PAD_RIGHT, 15, 15);
    repeatAction(curr, 3);

    // go to start row
    curr = appendAction(curr, PAD_DOWN, 5, 15);
    repeatAction(curr, startRow);

    // select 40 items
    curr = appendAction(curr, NOTHING, 0, 0);
    curr->child = _SelectNext40Items();

    // close home inventory
    curr = appendAction(curr, B, 10, 25);

    // leave house
    curr = appendAction(curr, DOWN, 4 * 15, 300);

    // go to nook mart
    curr = appendAction(curr, NOTHING, 0, 0);
    curr->child = _GoFromHomeToNookMart();

    // sell items in drop box
    curr = appendAction(curr, NOTHING, 0, 0);
    curr->child = _SellInventoryToDropBox();

    // go home
    curr = appendAction(curr, NOTHING, 0, 0);
    curr->child = _GoFromNookMartToHome();

    // enter home
    curr = appendAction(curr, A, 5, 400);

    // stop, be careful letting this loop
    struct Node* meta = initializeNode(NOTHING, 0, 0);
    meta->child = head;
    repeatAction(meta, times);
    appendAction(meta, NOTHING, 0, 0);
    stop(meta->next);

    return meta;
}
