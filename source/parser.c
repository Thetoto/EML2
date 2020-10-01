#include <stdio.h>
#include <stdlib.h>
#include "eml2.h"

void map_delete(struct map *map)
{
    for (int i = 0; i < HEIGHT; i++)
        free(map->grid[i]);
    // FREE PLAYERS
    for (size_t i = 0; i < map->n_players; i++)
        free(map->players[i]);

    free(map->grid);
}

static void add_player(int i, int j, struct map *map, short is_player)
{
    struct vec2 pos =
    {
        i, j
    };
    struct vec2 velo =
    {
        0, 0
    };
    struct vec2 size =
    {
        1, 2
    };

    int cur = map->n_players;
    if (is_player)
    {
        cur = 0;
    }
    else
        map->n_players++;

    map->players[cur] = malloc(sizeof(struct character));
    struct character *player = map->players[cur];
    player->is_player = is_player;
    player->map = map;

    player->went_left = 0;
    player->went_right = 0;

    player->went_jump = 0;
    player->is_ground = 1;

    player->orientation = 1;
    player->is_attacking = 0;
    player->has_jumped = 0;

    player->size = size;

    player->position = pos;
    player->velocity = velo;
}

void map_parse(char *path, struct map *map, short is_new)
{
    if (is_new)
        map->players = malloc(sizeof(struct character*) * 20);
    else
    {
        for (size_t i = 1; i < map->n_players; i++)
            free(map->players[i]);
    }
    map->n_players = 1;
    char cur;
    FILE *f = fopen(path, "r");
    if (!f)
        exit(1);
    enum block **grid = map->grid;
    if (is_new)
        grid = malloc(sizeof(enum block*) * HEIGHT);

    for (int j = 0; j < HEIGHT; j++)
    {
        if (is_new)
            grid[j] = malloc(sizeof(enum block) * WIDTH);
        for (int i = 0; i < WIDTH + 1; i++)
        {
            fread(&cur, 1, 1, f);
            if (cur == '\n' || cur == EOF)
                break;
            switch (cur)
            {
                case '.':
                    grid[j][i] = VOID;
                    break;
                case 'w':
                    grid[j][i] = WOOD;
                    break;
                case 'l':
                    grid[j][i] = LAVA1;
                    break;
                case 'f':
                    grid[j][i] = PRINCESS;
                    break;
                case 'p':
                    grid[j][i] = VOID;
                    //if (is_new)
                        add_player(i, j, map, 1);
                    break;
                case 'e':
                    grid[j][i] = VOID;
                    add_player(i, j, map, 0);
                    break;
                case 'b':
                    grid[j][i] = BRICK;
                    break;
                case 'd':
                    grid[j][i] = DIRT;
                    break;
                case 'g':
                    grid[j][i] = GRASS;
                    break;
                case 's':
                    grid[j][i] = STONE;
                    break;

                default:
                    grid[j][i] = VOID;
                    break;
            }
        }
        if (cur == EOF)
            break;
    }
    fclose(f);
    map->grid = grid;
}


