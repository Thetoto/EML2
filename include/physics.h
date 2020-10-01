#pragma once

#include "eml2.h"
#include <math.h>

#define ACCELERATION 0.02f
#define BOUNCE 0.9f
#define EPSILON 0.000001f
#define MOVE_SPEED 0.2f
#define JUMP 0.4f
#define DRAG 0.97f
#define TIME_JUMP 10
#define TIMEOUT 5

int apply_gravity(struct map *map);
int move_all(struct map *map);

int is_intersect(struct line l1, struct line l2);
void compute_delims(struct map *map);

void move_left(struct character *player);
void move_right(struct character *player);
void move_jump(struct character *player);
void move_attack(struct character *player);
