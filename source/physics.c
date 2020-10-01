#include "physics.h"


static float max(float a, float b)
{
    if (a > b)
        return a;
    return b;
}

static float min(float a, float b)
{
    if (a < b)
        return a;
    return b;
}


int is_between(float a, float borne1, float borne2)
{
    return borne1 < a && a < borne2;
}

int apply_gravity(struct map *map)
{
    struct character **players = map->players;
    size_t n = map->n_players;
    struct vec2 gravity =
    {
        0, ACCELERATION
    };

    for (size_t i = 0; i < n; i++)
        players[i]->velocity = v_sum(players[i]->velocity, gravity);

    return 0;
}



//opti: l'écrire en une ligne
static int on_line(struct vec2 p, struct vec2 q, struct vec2 r)
{
    return q.x <= max(p.x, r.x)
        && q.x >= min(p.x, r.x)
        && q.y <= max(p.y, r.y)
        && q.y >= min(p.y, r.y);
}


static int dir_points(struct vec2 a, struct vec2 b, struct vec2 c)
{
    float det = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);

    if (fabs(det) < EPSILON)
        return 0;
    return (det < 0) + 1;
}


int is_equal(float a, float b)
{
    return a - EPSILON < b && a + EPSILON > b;
}


int is_intersect(struct line l1, struct line l2)
{
    int dir1 = dir_points(l1.p1, l1.p2, l2.p1);
    int dir2 = dir_points(l1.p1, l1.p2, l2.p2);
    int dir3 = dir_points(l2.p1, l2.p2, l1.p1);
    int dir4 = dir_points(l2.p1, l2.p2, l1.p2);

    if ((!is_equal(dir1, dir2) && !is_equal(dir3, dir4))
        || (!dir1 && on_line(l1.p1, l2.p1, l1.p2))
        || (!dir2 && on_line(l1.p1, l2.p2, l1.p2))
        || (!dir3 && on_line(l2.p1, l1.p1, l2.p2))
        || (!dir4 && on_line(l2.p1, l1.p2, l2.p2)))
        return 1;
    return 0;
}



static int check_col(struct character *player, struct line line)
{
    struct vec2 newpos = player->position;
    struct vec2 v = player->velocity;
    if (v.x > 0)
        newpos.x += player->size.x;
    if (v.y > 0)
        newpos.y += player->size.y;
    struct line dPlayer =
        {
            newpos, v_sum(newpos, player->velocity)
        };
    return is_intersect(dPlayer, line);
}


struct vec2 find_intersection(struct character *player, struct line l)
{
    struct vec2 hitPlayer = player->position;
    if (player->velocity.x > 0)
        hitPlayer.x += player->size.x;
    if (player->velocity.y > 0)
        hitPlayer.y += player->size.y;

    struct vec2 res =
    {
        0, 0
    };

    struct line dPlayer =
    {
        hitPlayer, v_sum(hitPlayer, player->velocity)
    };
    if (l.p1.x == l.p2.x) //vertical
    {
        res.x = l.p1.x;
        res.y = dPlayer.p1.y / player->position.x * l.p1.x;
    }
    else if (l.p1.y == l.p2.y)
    {
        res.y = l.p1.y;
        res.x = dPlayer.p1.x / player->position.y * l.p1.y;
    }
    return res;
}

static void move(struct character *player)
{
    player->position = v_sum(player->position, player->velocity);
    player->velocity.x *= DRAG;
}


static void move_bounce(struct character *player, struct line l)
{
    if (l.p1.x == l.p2.x) //collide avec un truc vertical
    {
        player->velocity.x *= -BOUNCE;
    }
    else
        player->velocity.y *= -(BOUNCE / 15);
    player->velocity = v_scale(player->velocity, BOUNCE);
    move(player);
    player->has_jumped = 0;
}


void move_left(struct character *player)
{
    if (player->went_left && player->is_player)
        return;
    player->velocity.x = -MOVE_SPEED;
    player->went_left = TIMEOUT;
}

void move_right(struct character *player)
{
    if (player->went_right && player->is_player)
        return;
    player->velocity.x = MOVE_SPEED;
    player->went_right = TIMEOUT;
}

void move_jump(struct character *player)
{
    if (player->has_jumped || player->went_jump)
        return;
    player->velocity.y = -JUMP;
    player->has_jumped = 1;
    player->went_jump = TIMEOUT * 2;
}



int p_is_in(struct vec2 point, struct vec2 origin, struct vec2 size)
{
    return is_between(point.x, origin.x, origin.x + size.x)
        && is_between(point.y, origin.y, origin.y + size.y);
}

int is_in(struct character *player, struct character *ennemy)
{
    for (int i = 0; i < 4; i++)
    {
        struct vec2 border =
        {
            player->position.x + player->size.x * (i / 2),
            player->position.y + player->size.y * (i % 2)
        };
        if (p_is_in(border, ennemy->position, ennemy->size))
            return 1;
    }
    return 0;
}

int is_in_coord(struct character *player, int i, int j)
{
    struct vec2 origin =
    {
        i, j
    };
    struct vec2 size =
    {
        1, 1
    };

    for (int i = 0; i < 4; i++)
    {
        struct vec2 border =
        {
            player->position.x + player->size.x * (i / 2),
            player->position.y + player->size.y * (i % 2)
        };
        if (p_is_in(border, origin, size))
            return 1;
    }
    return 0;
}



void p_remove_at_i(struct character **players, int n, int i)
{
    while (i < n)
    {
        players[i] = players[i + 1];
        i++;
    }
}


void move_attack(struct character *player)
{
    struct vec2 attack =
    {
        player->position.x + player->orientation,
        player->position.y + 1
    };

    struct map *map = player->map;

    for (size_t i = 1; i < map->n_players; i++)
    {
        if (p_is_in(attack, map->players[i]->position, map->players[i]->size))
//            || p_is_in(attack2, map->players[i]->position, map->players[i]->size))
        {
            p_remove_at_i(map->players, map->n_players, i);
            map->n_players--;
        }
    }
}

int is_dead(struct map *map)
{
    struct character *player = map->players[0];

    if (player->position.y > HEIGHT + 8) //fall death
        return 1;
    for (size_t i = 1; i < map->n_players; i++) //ennemies death
    {
        if (is_in(player, map->players[i]))
            return 1;
    }

    for (int i = 0; i < WIDTH; i++) //lava death
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            if (map->grid[j][i] == LAVA1)
            {
                if (is_in_coord(player, i, j) || is_in_coord(player, i, j - 1))
                    return 1;
            }
        }
    }
    return 0;
}


int ground_under(struct map *map, struct vec2 point)
{
    int x = point.x;
    int y = point.y - 0.1f;
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        return map->grid[y][x] != VOID;
    return 0;
}

int on_ground(struct map *map)
{
    struct character *player = map->players[0];
    struct vec2 feet1 =
        {
            player->position.x,
            player->position.y + player->size.y + 1
        };
    struct vec2 feet2 =
    {
        player->position.x + player->size.x,
        player->position.y + player->size.y + 1
    };
    return ground_under(map, feet1) || ground_under(map, feet2);
}

int won(struct map *map)
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            if (map->grid[j][i] == PRINCESS)
                return is_in_coord(map->players[0], i, j) || is_in_coord(map->players[0], i, j - 1);
        }
    }
    return 0;
}



int move_all(struct map *map)
{
    struct character **players = map->players;
    size_t n = map->n_players;
    for (size_t i = 0; i < n; i++)
    {
        short collided = 0;
        size_t ndel = map->n_delims;
        for (size_t j = 0; j < ndel; j++)
        {
            struct line delim = map->delims[j];
            if (check_col(players[i], delim) == 0)
                continue;
            move_bounce(players[i], delim);
            collided = 1;
            break;
        }
        if (!collided)
            move(players[i]);
    }

    if (players[0]->is_attacking)
        move_attack(players[0]);
    
    players[0]->is_ground = on_ground(map);
    if (players[0]->went_left)
        players[0]->went_left--;

    if (players[0]->went_right)
        players[0]->went_right--;

    if (players[0]->went_jump)
        players[0]->went_jump--;

    if (players[0]->is_ground && players[0]->went_jump < TIME_JUMP / 2)
        players[0]->has_jumped = 0;

    if (is_dead(map))
        return -1;
    if (won(map))
        return 1;

    return 0;
}







struct line l_create(float a, float b, float c, float d)
{
    struct vec2 v1 =
    {
        b, a
    };
    struct vec2 v2 =
    {
        d, c
    };

    struct line res =
    {
        v1, v2
    };
    return res;
}


struct line *remove_at_i(struct line *list, size_t i, size_t n)
{
    while (i < n - 1)
    {
        list[i] = list[i + 1];
        i++;
    }
    return realloc(list, sizeof(struct line) * (n - 1));
}

void remove_redundancies(struct map *map)
{
    int nd = map->n_delims;
    for (int i = 0; i < nd; i++)
    {
        for (int j = i + 1; j < nd; j++)
        {
            if (l_equal(map->delims[i], map->delims[j])
                && l_equal(map->delims[i], map->delims[j]))
            {
                map->delims = remove_at_i(map->delims, j, map->n_delims);
                map->n_delims--;
                map->delims = remove_at_i(map->delims, i, map->n_delims);
                map->n_delims--;
                j -= 2;
                i--;
                nd -= 2;
                if (j < 0)
                    j = 0;
                if (i < 0)
                    i = 0;
            }
        }
    }
}


void compute_delims(struct map *map)
{
    size_t nblocks = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (map->grid[i][j] == GRASS
                || map->grid[i][j] == BRICK
                || map->grid[i][j] == DIRT
                || map->grid[i][j] == WOOD
                || map->grid[i][j] == STONE)
            {
                nblocks += 4;
                map->delims = realloc(map->delims, sizeof(struct line) * nblocks);
                map->delims[nblocks - 4] = l_create(i, j, i + 1, j);
                map->delims[nblocks - 3] = l_create(i, j, i, j + 1);
                map->delims[nblocks - 2] = l_create(i + 1, j + 1, i + 1, j);
                map->delims[nblocks - 1] = l_create(i + 1, j + 1, i, j + 1);
            }
        }
    }

    map->n_delims = nblocks;
    remove_redundancies(map);
}
