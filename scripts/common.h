#ifndef _SCRIPTS_COMMON_
#define _SCRIPTS_COMMON_

#include <stdint.h>

/*
 * Common definitions (needed between scripts and the joystick)
 */

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    R_UP,
    R_DOWN,
    R_LEFT,
    R_RIGHT,
    R_UP_LEFT,
    R_UP_RIGHT,
    R_DOWN_LEFT,
    R_DOWN_RIGHT,
    X,
    Y,
    A,
    B,
    L,
    R,
    ZL,
    ZR,
    MINUS,
    PLUS,
    THROW,
    NOTHING,
    TRIGGERS,
    PAD_LEFT,
    PAD_UP,
    PAD_RIGHT,
    PAD_DOWN,
    DRAG_LEFT,
    DRAG_RIGHT,
    DRAG_UP,
    DRAG_DOWN
} Buttons_t;

typedef struct {
    Buttons_t button;
    uint16_t duration;
} Command;

#endif