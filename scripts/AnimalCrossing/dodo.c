#include <stdio.h>
#include <scripts/scripts.h>

// NOTE: Before starting these scripts, you need to be right in front of dodo.
// It also must be the first time talking to dodo after entering the airport.
// (His speech is different when you talk to him the 2nd time)

static struct Node* welcome = NULL;
struct Node* _Welcome(void) {
    if (welcome == NULL) {
        welcome = initializeNode(NOTHING, 0, 0);
        struct Node* curr = welcome;
        // TODO: figure out why this extra first command needed
        curr = appendAction(curr, Y, 0, 0);

        // Start talking to Orville
        // Welcome to the airport
        curr = appendAction(curr, A, 5, 50);
        curr = appendAction(curr, B, 60, 0);

        // How can I help you out today?
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 5, 25);

        // Show options
        curr = appendAction(curr, A, 5, 25);
    }

    return welcome;
}

static struct Node* connectOnline = NULL;
struct Node* _ConnectOnline(void) {
    if (connectOnline == NULL) {
        connectOnline = initializeNode(NOTHING, 0, 0);
        struct Node* curr = connectOnline;

        // You wanna do local play or online play
        curr = appendAction(curr, A, 5, 25);
        curr = appendAction(curr, B, 50, 0);

        // Show options
        curr = appendAction(curr, A, 5, 25);

        // Online play
        curr = appendAction(curr, DOWN, 10, 0);

        // Let me just connect to you the internet
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 75, 0);

        // Show options
        curr = appendAction(curr, A, 5, 25);

        // Roger!
        curr = appendAction(curr, A, 5, 550);

        // How do you want to travel / Who do you want to invite
        curr = appendAction(curr, A, 5, 25);
    }

    return connectOnline;
}

static struct Node* travel = NULL;
struct Node* Travel(void) {
    if (travel == NULL) {
        travel = initializeNode(NOTHING, 0, 0);
        struct Node* curr = travel;

        curr->child = _Welcome();

        // I wanna fly
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 5, 25);

        // Roger!
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 5, 25);

        // Where did you want to go?
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 40, 0);

        // Show options
        curr = appendAction(curr, A, 5, 25);

        curr->child = _ConnectOnline();

        stop(curr);
    }

    return travel;
}

static struct Node* openGate = NULL;
struct Node* OpenGate(void) {
    if (openGate == NULL) {
        openGate = initializeNode(NOTHING, 0, 0);
        struct Node* curr = openGate;
        
        curr->child = _Welcome();

        // I want visitors
        curr = appendAction(curr, DOWN, 10, 0);

        curr->child = _ConnectOnline();
        
        stop(curr);
    }

    return openGate;
}

static struct Node* mysteryIsland = NULL;
struct Node* MysteryIsland(void) {
    if (mysteryIsland == NULL) {
        mysteryIsland = initializeNode(NOTHING, 0, 0);
        struct Node* curr = mysteryIsland;

        curr->child = _Welcome();

        // I wanna fly
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 5, 25);

        // Roger!
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 5, 25);

        // Looks like you have a NMT
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 30, 0);

        // Where did you want to go?
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 40, 0);

        // Show options
        curr = appendAction(curr, A, 5, 25);

        // Use NMT
        curr = appendAction(curr, DOWN, 10, 0);

        // So you wanna use your NMT? Roger!
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 25, 0);

        // You all packed?
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 70, 0);

        // Show options
        curr = appendAction(curr, A, 5, 25);

        // Time for takeoff
        curr = appendAction(curr, A, 5, 25);

        // Wait
        curr = appendAction(curr, A, 5, 900);

        // What would dodos do
        curr = appendAction(curr, A, 5, 600);

        // Wilbur: Alright, we are two down and docked
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 50, 0);

        // Wilbur: Meanwhile, I'll be in a holding pattern here 
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 50, 0);

        // Wilbur: Go catch some bees and chop some trees!
        curr = appendAction(curr, A, 5, 5);
        curr = appendAction(curr, B, 25, 0);

        curr = appendAction(curr, A, 5, 5);

        stop(curr);
    }

    return mysteryIsland;
}