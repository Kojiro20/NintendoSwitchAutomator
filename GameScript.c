#include "GameScript.h"
#include <stdio.h>

// store commands as a linked list
struct Node {
    Command command;
    struct Node *next;
};

static struct Node* head = NULL;
static struct Node* curr = NULL;
static struct Node* tail = NULL;

/*
 * This is where you should write game scripts
 * other methods shouldn't need to be updated.
 */
void LoadUserCommands(void) {
    
    // cancel any active dialog
    act(B, 5, 5);
    act(B, 5, 5);
    act(B, 5, 5);

    // put tool away
    act(PAD_DOWN, 10, 20);
}

/*
 * You shouldn't need to touch anything below this point
 */
void InitializeGameScript(void) {

    // create starting point
    struct Node* head = (struct Node*)malloc(sizeof(struct Node));
    head->command = (Command) { NOTHING, 5 };

    // initialize current/tail pointers
    curr = head;
    tail = head;
    
    // add additional commands
    LoadUserCommands();

    // make the list cyclical
    tail->next = head;
}

Command GetNextCommand(void) {
    Command res = curr->command;
    curr = curr->next;
    return res;
}

void act(Buttons_t button, uint16_t duration, uint16_t delay) {
    struct Node* next = (struct Node*)malloc(sizeof(struct Node));
    struct Node* wait = (struct Node*)malloc(sizeof(struct Node));

    next->command = (Command) { (Buttons_t) button, duration };
    wait->command = (Command) { NOTHING, delay };

    tail->next = next;
    next->next = wait;
    tail = wait;
}
