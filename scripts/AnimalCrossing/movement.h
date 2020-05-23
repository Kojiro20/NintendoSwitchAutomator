#ifndef _AC_MOVEMENT_
#define _AC_MOVEMENT_

#include <scripts/scripts.h>

struct Node* FaceUp(void);
struct Node* FaceUpLeft(void);
struct Node* FaceUpRight(void);
struct Node* FaceDown(void);
struct Node* FaceDownLeft(void);
struct Node* FaceDownRight(void);
struct Node* FaceLeft(void);
struct Node* FaceRight(void);
struct Node* RunInCircle(void);
struct Node* MoveDistInDir(int spaces, int offset, Buttons_t direction);

#endif