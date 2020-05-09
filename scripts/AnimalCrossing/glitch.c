#include <stdio.h>
#include <scripts/scripts.h>

#include "tools.h"
#include "movement.h"

static struct Node* cloneItem = NULL;
static struct Node* sellInventory = NULL;
static struct Node* sellInventory20x = NULL;
static struct Node* leaveRoomAndSellInventory = NULL;
static struct Node* sellInventoryToDropBox = NULL;
static struct Node* selectTvsFromHomeInventory = NULL;
static struct Node* goFromHomeToNookMart = NULL;
static struct Node* goFromNookMartToHome = NULL;

struct Node* LeaveRoomAndSellInventory(void) {
    if (leaveRoomAndSellInventory == NULL)
    {
        leaveRoomAndSellInventory = initializeNode(NOTHING, 0, 0);
        struct Node *curr = leaveRoomAndSellInventory;

        // close decoration mode
        curr = appendAction(curr, B, 5, 20);
        repeatAction(curr, 3);

        // leave room
        curr = appendAction(curr, NOTHING, 1, 0);
        curr->child = FaceLeft();
        curr = appendAction(curr, LEFT, 3 * 15, 300);

        // leave house
        curr = appendAction(curr, LEFT, 3 * 16, 0);
        curr = appendAction(curr, DOWN, 4 * 15, 300);

        // go to rat house
        curr->child = GoFromHomeToNookMart();

        // sale box
        curr = appendAction(curr, A, 5, 20);
        curr = appendAction(curr, B, 5, 20);
        repeatAction(curr, 10); // get out of the dialog

        // go home
        curr = appendAction(curr, NOTHING, 0, 0);
        curr->child = GoFromNookMartToHome();
        curr = appendAction(curr, A, 5, 300);

        // go back to room
        curr = appendAction(curr, UP, 2 * 15, 0);
        curr = appendAction(curr, RIGHT, 5 * 16, 300);
    }

    return leaveRoomAndSellInventory;
}

struct Node* SelectTvsFromHomeInventory(void) {
    if (selectTvsFromHomeInventory == NULL)
    {
        // create a row selector node that selects 8 items
        struct Node* rowSelector = initializeNode(NOTHING, 0, 0);
        repeatAction(rowSelector, 8);
        rowSelector->child = initializeNode(NOTHING, 0, 0);
        struct Node* c = rowSelector->child;
        c = appendAction(c, A, 5, 10); // move to pockets?
        c = appendAction(c, A, 5, 5); // yes
        c = appendAction(c, RIGHT, 5, 5); // next

        // create a move-down node that repeates 5 times
        struct Node* moveDown = initializeNode(DOWN, 5, 5);
        repeatAction(moveDown, 5);
        moveDown->child = rowSelector;


        /*
         * Pre-reqs:
         *  make sure misc inventory slot is selected
         *  make sure TVs start on the second row of inventory
         *  start script from immediately inside front door
         *  start with empty inventory
         */


        selectTvsFromHomeInventory = initializeNode(NOTHING, 10, 0);
        struct Node *curr = selectTvsFromHomeInventory;

        // starting in home, open home inventory
        curr = appendAction(curr, PAD_RIGHT, 15, 25);
        curr = appendAction(curr, PAD_RIGHT, 15, 25);

        // go to top of misc inventory
        curr = appendAction(curr, PAD_UP, 5, 5);
        repeatAction(curr, 6);

        // select 40 items
        curr = appendAction(curr, DOWN, 5, 10);
        curr->child = moveDown;

        // exit selector
        curr = appendAction(curr, B, 5, 25);
    }

    return selectTvsFromHomeInventory;
}

struct Node* SellInventoryToDropBox(void) {
    if (sellInventoryToDropBox == NULL)
    {
        sellInventoryToDropBox = initializeNode(NOTHING, 10, 0);
        struct Node *curr = sellInventoryToDropBox;

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
    }

    return sellInventoryToDropBox;
}

struct Node* SellInventory(void) {
    if (sellInventory == NULL)
    {
        sellInventory = initializeNode(NOTHING, 0, 0);
        struct Node *curr = sellInventory;

        // grab 40 tvs from inventory
        curr = appendAction(curr, NOTHING, 1, 0);
        curr->child = SelectTvsFromHomeInventory();

        // leave house
        curr = appendAction(curr, DOWN, 4 * 15, 300);

        // go to rat house
        curr->child = GoFromHomeToNookMart();

        // sale box
        curr = appendAction(curr, NOTHING, 5, 0);
        curr->child = SellInventoryToDropBox();
        
        // go home
        curr = appendAction(curr, NOTHING, 0, 0);
        curr->child = GoFromNookMartToHome();
        curr = appendAction(curr, A, 5, 400);
    }

    return sellInventory;
}

struct Node* SellInventory20x(void) {
    if (sellInventory20x == NULL)
    {
        sellInventory20x = initializeNode(NOTHING, 0, 0);
        struct Node *curr = sellInventory20x;

        curr->child = SellInventory();
        repeatAction(curr, 20);
    }

    return sellInventory20x;
}

struct Node* GoFromHomeToNookMart(void) {
    if (goFromHomeToNookMart == NULL)
    {
        goFromHomeToNookMart = initializeNode(NOTHING, 0, 0);
        struct Node *curr = goFromHomeToNookMart;

        curr->child = FaceDown();
        curr = appendAction(curr, DOWN, 7 * 15, 0);
        curr->child = FaceRight();
        curr = appendAction(curr, RIGHT, 2 * 15, 0);
        curr->child = FaceDown();
        curr = appendAction(curr, DOWN, 6 * 15, 0);
        curr->child = FaceRight();
        curr = appendAction(curr, RIGHT, 12 * 15, 0);
        curr->child = FaceDown();
        curr = appendAction(curr, DOWN, 3 * 15, 0);
        curr->child = FaceRight();
        curr = appendAction(curr, RIGHT, 2 * 15, 0);
        curr->child = FaceUp();
        curr = appendAction(curr, UP, 2 * 15, 0);
    }

    return goFromHomeToNookMart;
}

struct Node* GoFromNookMartToHome(void) {
    if (goFromNookMartToHome == NULL)
    {
        goFromNookMartToHome = initializeNode(NOTHING, 0, 0);
        struct Node *curr = goFromNookMartToHome;

        curr->child = FaceDown();
        curr = appendAction(curr, DOWN, 2 * 15, 0);
        curr->child = FaceLeft();
        curr = appendAction(curr, LEFT, 2 * 15, 0);
        curr->child = FaceUp();
        curr = appendAction(curr, UP, 3 * 15, 0);
        curr->child = FaceLeft();
        curr = appendAction(curr, LEFT, 12 * 15, 0);
        curr->child = FaceUp();
        curr = appendAction(curr, UP, 6 * 15, 0);
        curr->child = FaceLeft();
        curr = appendAction(curr, LEFT, 2 * 15, 0);
        curr->child = FaceUp();
        curr = appendAction(curr, UP, 7 * 15, 0);
    }

    return goFromNookMartToHome;
}

struct Node* CloneItem(void)
{
    if (cloneItem == NULL)
    {
        cloneItem = initializeNode(NOTHING, 0, 0);
        struct Node *curr = cloneItem;

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
