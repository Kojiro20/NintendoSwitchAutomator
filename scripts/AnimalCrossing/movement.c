#include <stdio.h>
#include <scripts/scripts.h>

#include "movement.h"

static struct Node* faceUp = NULL;
static struct Node* faceDown = NULL;
static struct Node* faceLeft = NULL;
static struct Node* faceRight = NULL;

struct Node* faceDir(Buttons_t direction) {
    struct Node* head = initializeNode(NOTHING, 0);
    struct Node* curr = head;

    // avoid moving while turning
    // there is a rotational pivot effect when you turn
    int delay = 2;
    for (int i = 0; i < 5; i++) {
        curr = appendAction(curr, direction, delay, 0);
    }

    return head;
}

struct Node* FaceUp() {
    if (faceUp == NULL) {
        faceUp = faceDir(UP);
    }

    return faceUp;
}

struct Node* FaceDown() {
    if (faceDown == NULL) {
        faceDown = faceDir(DOWN);
    }

    return faceDown;
}

struct Node* FaceLeft() {
    if (faceLeft == NULL) {
        faceLeft = faceDir(LEFT);
    }

    return faceLeft;
}

struct Node* FaceRight() {
    if (faceRight == NULL) {
        faceRight = faceDir(RIGHT);
    }

    return faceRight;
}
