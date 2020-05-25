#include <stdio.h>
#include <scripts/scripts.h>

static struct Node* wishStars = NULL;
struct Node* WishStars(void) {
    if (wishStars == NULL) {
        wishStars = initializeNode(NOTHING, 0, 0);
        struct Node* curr = wishStars;

        // Look up
        curr = appendAction(curr, R_UP, 10, 10);
        // Wish
        curr = appendAction(curr, A, 5, 10);
    }

    return wishStars;
}
