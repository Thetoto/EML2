#pragma once

#include "eml2.h"

struct inputs
{
    short attack;
    short left;
    short right;
    short jump;
    short quit;
    short cheat;
};


struct inputs get_inputs(void);
int update(struct game *game, struct inputs in);
