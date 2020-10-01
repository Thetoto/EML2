#include <SDL2/SDL.h>
#include "inputs.h"
#include "physics.h"
#include <stdint.h>
#include <switch.h>

struct inputs get_inputs(void)
{
    struct inputs in =
    {
        0, 0, 0, 0, 0, 0
    };
    SDL_PumpEvents();
    uint32_t kDown;
    uint32_t kHeld;
    uint32_t kUp;
		hidScanInput();

		kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);
		kUp = hidKeysUp(CONTROLLER_P1_AUTO);

//    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (kHeld & KEY_RIGHT)
        in.right = 1;
    if (kHeld & KEY_LEFT)
        in.left = 1;
    if (kHeld & KEY_A)
        in.jump = 1;
    if (kHeld & KEY_PLUS)
        in.quit = 1;
    if (kHeld & KEY_B)
        in.attack = 1;
    if (kHeld & KEY_Y)
        in.cheat = -1;
    return in;
}

short check_block(struct character *pnj, int delta)
{
    int x = pnj->position.x / 1;
    int y = pnj->position.y / 1;
    if (pnj->map->grid[y+1][x + delta] == GRASS
            || pnj->map->grid[y+1][x + delta] == DIRT
            || pnj->map->grid[y+1][x + delta] == WOOD
            || pnj->map->grid[y+1][x + delta] == STONE
            || pnj->map->grid[y+1][x + delta] == BRICK)
        return 1;
    if (pnj->map->grid[y+2][x + delta] == GRASS
            || pnj->map->grid[y+2][x + delta] == DIRT
            || pnj->map->grid[y+2][x + delta] == WOOD
            || pnj->map->grid[y+2][x + delta] == STONE
            || pnj->map->grid[y+2][x + delta] == BRICK)
        return 1;
    if (pnj->map->grid[y+3][x + delta] != GRASS
            && pnj->map->grid[y+3][x + delta] != DIRT
            && pnj->map->grid[y+3][x + delta] != WOOD
            && pnj->map->grid[y+3][x + delta] != STONE
            && pnj->map->grid[y+3][x + delta] != BRICK)
        return 1;
    return 0;
}

void best_ia(struct game *game)
{
    for (size_t i = 1; i < game->map->n_players; i++)
{
        struct character *pnj = game->map->players[i];
        if (pnj->orientation == 1 && check_block(pnj, 2))
        {
            pnj->orientation = -1;
        }
        if (pnj->orientation == -1 && check_block(pnj, -1))
        {
            pnj->orientation = 1;
        }
        if (pnj->orientation == -1)
            move_left(pnj);
        else
            move_right(pnj);
    }
}

int update(struct game *game, struct inputs in)
{
    if (in.left)
        move_left(game->map->players[0]);
    if (in.right)
        move_right(game->map->players[0]);
    if (in.jump)
        move_jump(game->map->players[0]);
    if (in.attack && game->map->players[0]->is_attacking == 0)
        game->map->players[0]->is_attacking = 1;
    best_ia(game);
    if (in.quit)
    {
        game->is_playing = 0;
    }
    apply_gravity(game->map);
    int res = move_all(game->map);
    if (res == 1)
        return -2;
    for (size_t i = 0; i < 1; i++)
    {
        struct character *player = game->map->players[i];
        int dir = player->velocity.x > 0.01 ? 1 : player->velocity.x < -0.01 ? -1 : 0;
        if (dir == -1)
            player->orientation = -1;
        if (dir == 1)
            player->orientation = 1;
    }
    if (game->map->players[0]->position.x < 0)
    {
        game->lvl--;
        game->lvl = (game->lvl + 6) % 6;
        return 1;
    }
    if (game->map->players[0]->position.x > 49)
    {
        game->lvl++;
        game->lvl = (game->lvl + 6) % 6;
        return 2;
    }
    if (res == -1)
        return -1;
    return 0;
}
