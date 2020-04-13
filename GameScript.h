#ifndef _GAME_PLAY_H_
#define _GAME_PLAY_H_

#include <stdint.h>

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    X,
    Y,
    A,
    B,
    L,
    R,
    ZL,
    ZR,
    THROW,
    NOTHING,
    TRIGGERS,
    PAD_LEFT,
    PAD_UP,
    PAD_RIGHT,
    PAD_DOWN,
} Buttons_t;

typedef struct {
    Buttons_t button;
    uint16_t duration;
} Command;

Command GetNextCommand(void);

void InitializeGameScript(void);

#endif