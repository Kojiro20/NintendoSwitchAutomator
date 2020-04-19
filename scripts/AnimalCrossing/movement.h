#ifndef _SCRIPTS_AC_MOVEMENT_
#define _SCRIPTS_AC_MOVEMENT_

#include <scripts/scripts.h>

struct Node* FaceUp(void);
struct Node* FaceDown(void);
struct Node* FaceLeft(void);
struct Node* FaceRight(void);
struct Node* RunInCircle(void);
struct Node* MoveDistInDir(int spaces, int offset, Buttons_t direction);

#endif