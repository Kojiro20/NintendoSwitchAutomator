#include <stdio.h>
#include <scripts/scripts.h>

static int pickupTime = 30;
static int moveOffset = -2;

static struct Node* hitRock = NULL;

/**
 * Starting position:
 * 
 *   R
 * OX
 *  O
 * 
 * R = rock
 * X = you (facing any direction)
 * O = hole/obstruction
 */
struct Node* HitRock(void) {
    if (hitRock == NULL) {
        hitRock = initializeNode(NOTHING, 0, 0);
        struct Node* curr = hitRock;

        // Do this a few times, sometimes doesn't fully face correct direction
        curr->child = FaceUpRight();
        curr->next = initializeNode(NOTHING, 50, 0);
        curr->child = FaceUpRight();

        for (int i = 0; i < 8; i++) {
            curr = appendAction(curr, A, 5, 40);
        }

        // pickup around rock
        curr->child = MoveDistInDir(1, moveOffset, RIGHT);
        curr = appendAction(curr, Y, 5, pickupTime);
        curr->child = MoveDistInDir(1, moveOffset, RIGHT);
        curr = appendAction(curr, Y, 5, pickupTime);
        curr->child = MoveDistInDir(1, moveOffset, UP);
        curr = appendAction(curr, Y, 5, pickupTime);
        curr->child = MoveDistInDir(1, moveOffset, UP);
        curr = appendAction(curr, Y, 5, pickupTime);
        curr->child = MoveDistInDir(1, moveOffset, LEFT);
        curr = appendAction(curr, Y, 5, pickupTime);
        curr->child = MoveDistInDir(1, moveOffset, LEFT);
        curr = appendAction(curr, Y, 5, pickupTime);
        curr->child = MoveDistInDir(1, moveOffset, DOWN);
        curr = appendAction(curr, Y, 5, pickupTime);
        curr->child = MoveDistInDir(1, moveOffset, DOWN);
        curr = appendAction(curr, Y, 5, pickupTime);

        stop(curr);
    }

    return hitRock;
}