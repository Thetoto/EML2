#include "rendering.h"
#include "SDL2/SDL_mixer.h"

static void warnx(char *str)
{
    printf("WARNING : %s\n", str);
}

static void errx(char *str)
{
    printf("ERROR : %s\n", str);
}

void init_sdl(struct game *game)
{
    return;
}

void destroy_sdl(struct game *game)
{
    SDL_DestroyTexture(game->texture_lib[VOID]);
    SDL_DestroyTexture(game->texture_lib[GRASS]);
    SDL_DestroyTexture(game->texture_lib[LAVA1]);
    SDL_DestroyTexture(game->texture_lib[LAVA2]);
    SDL_DestroyTexture(game->texture_lib[LAVA3]);
    SDL_DestroyTexture(game->texture_lib[BRICK]);
    SDL_DestroyTexture(game->texture_lib[DIRT]);
    SDL_DestroyTexture(game->texture_lib[STONE]);
    SDL_DestroyTexture(game->texture_lib[WOOD]);


    SDL_DestroyTexture(game->texture_lib[PR0]);
    SDL_DestroyTexture(game->texture_lib[PR1]);
    SDL_DestroyTexture(game->texture_lib[PR2]);
    SDL_DestroyTexture(game->texture_lib[PL0]);
    SDL_DestroyTexture(game->texture_lib[PL1]);
    SDL_DestroyTexture(game->texture_lib[PL2]);
    SDL_DestroyTexture(game->texture_lib[PF]);
    SDL_DestroyTexture(game->texture_lib[PFJ]);
    SDL_DestroyTexture(game->texture_lib[PRJ]);
    SDL_DestroyTexture(game->texture_lib[PLJ]);
    SDL_DestroyTexture(game->texture_lib[AR0]);
    SDL_DestroyTexture(game->texture_lib[AR1]);
    SDL_DestroyTexture(game->texture_lib[AL0]);
    SDL_DestroyTexture(game->texture_lib[AL1]);

    SDL_DestroyTexture(game->texture_lib[EL1]);
    SDL_DestroyTexture(game->texture_lib[EL0]);
    SDL_DestroyTexture(game->texture_lib[ER1]);
    SDL_DestroyTexture(game->texture_lib[ER0]);
    SDL_DestroyTexture(game->texture_lib[EF]);
    SDL_DestroyTexture(game->texture_lib[EFJ]);

    SDL_DestroyTexture(game->texture_lib[DOOR]);
    SDL_DestroyTexture(game->texture_lib[DOORS]);
    SDL_DestroyTexture(game->texture_lib[BG]);
    SDL_DestroyTexture(game->texture_lib[CREDITS]);
    SDL_DestroyTexture(game->texture_lib[CREDITSS]);
    SDL_DestroyTexture(game->texture_lib[EML]);
    SDL_DestroyTexture(game->texture_lib[HISTORY]);
    SDL_DestroyTexture(game->texture_lib[HISTORYS]);
    SDL_DestroyTexture(game->texture_lib[QUICKGAME]);
    SDL_DestroyTexture(game->texture_lib[QUICKGAMES]);
    SDL_DestroyTexture(game->texture_lib[CONTINUE]);
    SDL_DestroyTexture(game->texture_lib[CONTINUES]);
    SDL_DestroyTexture(game->texture_lib[VICTORY]);
    SDL_DestroyTexture(game->texture_lib[GAMEOVER]);
    SDL_DestroyTexture(game->texture_lib[BACK]);

    SDL_DestroyTexture(game->texture_lib[LOUIS]);
    SDL_DestroyTexture(game->texture_lib[LOUIST]);
    SDL_DestroyTexture(game->texture_lib[TOTO]);
    SDL_DestroyTexture(game->texture_lib[TOTOT]);
    SDL_DestroyTexture(game->texture_lib[G]);
    SDL_DestroyTexture(game->texture_lib[GT]);

    SDL_DestroyTexture(game->texture_lib[R]);
}

void load_textures(struct game *game)
{
    load_blocks(game);
    load_players(game);
}

static int get_timer(struct game *game)
{
    int res = game->timer;
    game->timer += 1;
    if (game->timer > TIMER_MAX)
        game->timer = 0;
    return res;
}

static int get_attack_timer(struct character *player)
{
    int res = player->is_attacking;
    player->is_attacking += 1;
    if (player->is_attacking > TIMER_MAX_ATTACK)
        player->is_attacking = 0;
    return res;
}

static SDL_Texture *attacking(struct game *game, struct character *player)
{
    int  timer = get_attack_timer(player);
    int index = timer / TIMER_MAX_ATTACK2;
    int dir = player->orientation;
    if (dir == 0)
        return game->texture_lib[AL0];

    if (dir == -1)
    {
        if (index == 0)
            return game->texture_lib[AL0];
        return game->texture_lib[AL1];
    }

    if (index == 0)
        return game->texture_lib[AR0];
    return game->texture_lib[AR1];

}

static SDL_Texture *select_player_sprite(struct game *game,
        struct character *player)
{
    if (player->is_attacking)
        return attacking(game, player);

    int timer = get_timer(game);
    int index = timer / TIMER_MAX2;
    int dir = player->orientation;
    if (dir == 0)
    {
        return game->texture_lib[PF];// a modif
    }
    if (dir == -1)
    {
        if (!player->is_ground)
            return game->texture_lib[PLJ];
        if ((player->velocity.x > -0.05 && player->velocity.x < 0.05)
                ||index == 0)
            return game->texture_lib[PL0];
        return game->texture_lib[PL2];
    }

    if (!player->is_ground)
        return game->texture_lib[PRJ];
    if ((player->velocity.x > -0.05 && player->velocity.x < 0.05)
                ||index == 0)
        return game->texture_lib[PR0];
    return game->texture_lib[PR2];
}

static SDL_Texture *select_NPC_sprite(struct game *game,
        struct character *player)
{
    int timer = get_timer(game);
    int index = timer / TIMER_MAX2;
    int dir = player->orientation;
    if (dir == 0)
    {
        return game->texture_lib[EF];// a modif
    }

    if (!player->is_ground)
        return game->texture_lib[EFJ];

    if (dir == -1)
    {

        if ((player->velocity.x > -0.05 && player->velocity.x < 0.05)
                ||index == 0)
            return game->texture_lib[EL0];
        return game->texture_lib[EL1];
    }


    if ((player->velocity.x > -0.05 && player->velocity.x < 0.05)
                ||index == 0)
        return game->texture_lib[ER0];
    return game->texture_lib[ER1];
}


void render_players(struct game *game)
{
    for (size_t i = 0; i < game->map->n_players; i++)
    {
        SDL_Rect dstrect;
        dstrect.x = game->map->players[i]->position.x * BLOCK_SIZE;
        dstrect.y = game->map->players[i]->position.y * BLOCK_SIZE;
        dstrect.w = BLOCK_SIZE;
        dstrect.h = 2 * BLOCK_SIZE;

        struct character *player = game->map->players[i];
        SDL_Texture *text;
        if (player->is_player)
            text = select_player_sprite(game, player);
        else
            text= select_NPC_sprite(game, player);

        //attacking left
        if (player->is_attacking && player->orientation == -1)
            dstrect.x -= BLOCK_SIZE;
        if (player->is_attacking)
        {
            dstrect.w *= 2;
        }

        SDL_RenderCopy(game->renderer, text, NULL, &dstrect);
    }
}

static void get_lava_timer(struct game *game)
{
    game->timer_lava += 1;
    if (!(game->timer_lava < TIMER_MAX_LAVA))
        game->timer_lava = 0;
}

static SDL_Texture *select_block_texture(struct game *game, enum block block)
{
    if (block == LAVA1)
    {
        if (game->timer_lava < TIMER_MAX_LAVA3)
            return game->texture_lib[LAVA1];
        else if (game->timer_lava < TIMER_MAX_LAVA3 * 2)
            return game->texture_lib[LAVA2];
        return game->texture_lib[LAVA3];
    }
    return game->texture_lib[block];
}

static void render_map(struct game *game)
{
    SDL_RenderCopy(game->renderer, game->texture_lib[BACK], NULL, NULL);
    int imax = WIN_WIDTH / BLOCK_SIZE;
    int jmax = WIN_HEIGHT / BLOCK_SIZE;
    get_lava_timer(game);
    for (int j = 0; j < jmax; j++)
    {
        for (int i = 0; i < imax; i++)
        {
            SDL_Rect dstrect;

            dstrect.x = i * BLOCK_SIZE;
            dstrect.y = j * BLOCK_SIZE;
            dstrect.w = BLOCK_SIZE;
            dstrect.h = BLOCK_SIZE;

            if (game->map->grid[j][i] == PRINCESS)
                dstrect.h *= 2;
            SDL_RenderCopy(game->renderer, select_block_texture(game,
                        game->map->grid[j][i]), NULL, &dstrect);
        }
    }

}
void render_frame(struct game *game)
{
    render_map(game);
    render_players(game);
    SDL_RenderPresent(game->renderer);
}
