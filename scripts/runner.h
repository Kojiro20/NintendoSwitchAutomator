#ifndef _SCRIPTS_RUNNER_
#define _SCRIPTS_RUNNER_

#include <stdint.h>
#include "common.h"

/*
 * This provides an interface to the game scripts for the joystick.
 * The joystick should only need to know about this and the common
 * definitions.
 */

Command GetNextCommand(void);
void InitializeGameScript(void);

#endif
