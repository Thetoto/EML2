#include "vector.h"


struct vec2 v_sum(struct vec2 a, struct vec2 b)
{
    struct vec2 res = {
        a.x + b.x,
        a.y + b.y
    };
    return res;
}

struct vec2 v_sub(struct vec2 a, struct vec2 b)
{
    struct vec2 res = {
        a.x - b.x,
        a.y - b.y
    };
    return res;
}

struct vec2 v_scale(struct vec2 v, double a)
{
    struct vec2 res = {
        v.x * a,
        v.y * a
    };
    return res;
}

double v_dist(struct vec2 v)
{
    double dist = pow(v.x, 2) + pow(v.y, 2);
    return sqrt(dist);
}

struct vec2 v_norm(struct vec2 v)
{
    double dist = v_dist(v);
    struct vec2 res = {
        v.x / dist,
        v.y / dist
    };
    return res;
}


double v_scalar(struct vec2 a, struct vec2 b)
{
    return a.x * b.x + a.y * b.y;
}

double v_cross(struct vec2 a, struct vec2 b)
{
    return a.x * b.y - b.x * a.y;
}

/*
struct struct vec2 v_cross(struct vec2 a, struct vec2 b)
{
    struct vec2 res = {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
    return res;
}
*/

void v_print(struct vec2 a)
{
    printf("x: %f\ny: %f\n\n", a.x, a.y);
}


int l_equal(struct line a, struct line b)
{
    if ((a.p1.x == b.p1.x)
        && (a.p1.y == b.p1.y)
        && (a.p2.x == b.p2.x)
        && (a.p2.y == b.p2.y))
        return 1;

    struct vec2 temp = a.p1;
    a.p1 = a.p2;
    a.p2 = temp;

    return (a.p1.x == b.p1.x)
        && (a.p1.y == b.p1.y)
        && (a.p2.x == b.p2.x)
        && (a.p2.y == b.p2.y);
}
