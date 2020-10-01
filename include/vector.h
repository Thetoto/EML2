#pragma once

#include <math.h>
#include <stdio.h>

struct vec2
{
    float x;
    float y;
};

struct line
{
    struct vec2 p1;
    struct vec2 p2;
};

struct vec2 v_sum(struct vec2 a, struct vec2 b);
struct vec2 v_sub(struct vec2 a, struct vec2 b);
struct vec2 v_scale(struct vec2 v, double a);
double v_scalar(struct vec2 a, struct vec2 b);

double v_dist(struct vec2 v);
struct vec2 v_norm(struct vec2 v);

double v_cross(struct vec2 a, struct vec2 b);
void v_print(struct vec2 a);

int l_equal(struct line a, struct line b);
