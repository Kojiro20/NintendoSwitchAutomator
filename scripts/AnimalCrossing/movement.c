#include <stdio.h>
#include <scripts/scripts.h>

#include "movement.h"

static struct Node* faceUp = NULL;
static struct Node* faceUpLeft = NULL;
static struct Node* faceUpRight = NULL;
static struct Node* faceDown = NULL;
static struct Node* faceDownLeft = NULL;
static struct Node* faceDownpRight = NULL;
static struct Node* faceLeft = NULL;
static struct Node* faceRight = NULL;
static struct Node* runInCircle = NULL;

struct Node* faceDir(Buttons_t direction) {
    struct Node* head = initializeNode(NOTHING, 0, 0);
    struct Node* curr = head;

    // avoid moving while turning
    // there is a rotational pivot effect when you turn
    curr = appendAction(curr, direction, 1, 1);
    repeatAction(curr, 7);
    curr = appendAction(curr, NOTHING, 0, 0);

    return head;
}

struct Node* FaceUp(void) {
    if (faceUp == NULL) {
        faceUp = faceDir(UP);
    }

    return faceUp;
}

struct Node* FaceUpLeft(void) {
    if (faceUpLeft == NULL) {
        faceUpLeft = faceDir(UP_LEFT);
    }

    return faceUpLeft;
}

struct Node* FaceUpRight(void) {
    if (faceUpRight == NULL) {
        faceUpRight = faceDir(UP_RIGHT);
    }

    return faceUpRight;
}

struct Node* FaceDown(void) {
    if (faceDown == NULL) {
        faceDown = faceDir(DOWN);
    }

    return faceDown;
}

struct Node* FaceDownLeft(void) {
    if (faceDownLeft == NULL) {
        faceDownLeft = faceDir(DOWN_LEFT);
    }

    return faceDownLeft;
}

struct Node* FaceDownRight(void) {
    if (faceDownpRight == NULL) {
        faceDownpRight = faceDir(DOWN_RIGHT);
    }

    return faceDownpRight;
}

struct Node* FaceLeft(void) {
    if (faceLeft == NULL) {
        faceLeft = faceDir(LEFT);
    }

    return faceLeft;
}

struct Node* FaceRight(void) {
    if (faceRight == NULL) {
        faceRight = faceDir(RIGHT);
    }

    return faceRight;
}

/*
 * Note, this is not cached due to inputs
 */
struct Node* MoveDistInDir(int dist, int offset, Buttons_t direction) {
    struct Node* head = initializeNode(NOTHING, 0, 0);
    struct Node* curr = head;

    switch (direction)
    {
        case DOWN:
            head->child = FaceDown();
            break;
        case LEFT:
            head->child = FaceLeft();
            break;
        case RIGHT:
            head->child = FaceRight();
            break;
        default: // UP
            head->child = FaceUp();
    }

    int gridSpaceDelay = dist * 13 + offset;
    curr = appendAction(curr, direction, gridSpaceDelay, gridSpaceDelay);
    return head;
}

struct Node* RunInCircle(void) {
    if (runInCircle == NULL) {
        runInCircle = initializeNode(NOTHING, 0, 0);
        struct Node* curr = runInCircle;

        int dist = 50;

        curr->child = FaceLeft();
        curr = appendAction(curr, LEFT, dist, 0);
        curr->child = FaceDown();
        curr = appendAction(curr, DOWN, dist, 0);
        curr->child = FaceRight();
        curr = appendAction(curr, RIGHT, dist, 0);
        curr->child = FaceUp();
        curr = appendAction(curr, UP, dist, 0);
    }

    return runInCircle;
}
