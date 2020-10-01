#include "rendering.h"
#include <stdio.h>
static void warnx(char *str)
{
    printf("WARNING : %s\n", str);
}

static void load_menus(struct game *game)
{
    SDL_Texture *bg_text = IMG_LoadTexture(game->renderer,
            BG_PATH);
    if (!bg_text)
        warnx("cannot convert background to SDL_Texture");

    SDL_Texture *door_text = IMG_LoadTexture(game->renderer,
            DOOR_PATH);
    if (!door_text)
        warnx("cannot convert door to SDL_Texture");

    SDL_Texture *doorS_text = IMG_LoadTexture(game->renderer,
            DOORS_PATH);
    if (!doorS_text)
        warnx("cannot convert doorS to SDL_Texture");

    SDL_Texture *credits_text = IMG_LoadTexture(game->renderer,
            CREDITS_PATH);
    if (!credits_text)
        warnx("cannot convert credits to SDL_Texture");

    SDL_Texture *creditsS_text = IMG_LoadTexture(game->renderer,
            CREDITSS_PATH);
    if (!creditsS_text)
        warnx("cannot convert creditsS to SDL_Texture");

    SDL_Texture *eml_text = IMG_LoadTexture(game->renderer,
            EML_PATH);
    if (!eml_text)
        warnx("cannot convert eml to SDL_Texture");

    SDL_Texture *history_text = IMG_LoadTexture(game->renderer,
            HISTORY_PATH);
    if (!history_text)
        warnx("cannot convert history to SDL_Texture");

    SDL_Texture *historyS_text = IMG_LoadTexture(game->renderer,
            HISTORYS_PATH);
    if (!historyS_text)
        warnx("cannot convert historyS to SDL_Texture");

    SDL_Texture *quickgame_text = IMG_LoadTexture(game->renderer,
            QUICKGAME_PATH);
    if (!quickgame_text)
        warnx("cannot convert quickgame to SDL_Texture");

    SDL_Texture *quickgameS_text = IMG_LoadTexture(game->renderer,
            QUICKGAMES_PATH);
    if (!quickgameS_text)
        warnx("cannot convert quickgameS to SDL_Texture");

    SDL_Texture *back_text = IMG_LoadTexture(game->renderer,
            BACK_PATH);
    if (!back_text)
        warnx("cannot convert back to SDL_Texture");

    SDL_Texture *continue_text = IMG_LoadTexture(game->renderer,
            CONTINUE_PATH);
    if (!continue_text)
        warnx("cannot convertcontinue to SDL_Texture");

    SDL_Texture *continueS_text = IMG_LoadTexture(game->renderer,
            CONTINUES_PATH);
    if (!continueS_text)
        warnx("cannot convert continueS to SDL_Texture");

    SDL_Texture *victory_text = IMG_LoadTexture(game->renderer,
            VICTORY_PATH);
    if (!victory_text)
        warnx("cannot convertvictory to SDL_Texture");

    SDL_Texture *gameover_text = IMG_LoadTexture(game->renderer,
            DEFEAT_PATH);
    if (!gameover_text)
        warnx("cannot convert gameover to SDL_Texture");

    SDL_Texture *resume_text = IMG_LoadTexture(game->renderer,
            R_PATH);
    if (!resume_text)
        warnx("cannot convert resume to SDL_Texture");


    game->texture_lib[BACK] = back_text;
    game->texture_lib[DOOR] = door_text;
    game->texture_lib[DOORS] = doorS_text;
    game->texture_lib[BG] = bg_text;
    game->texture_lib[CREDITS] = credits_text;
    game->texture_lib[CREDITSS] = creditsS_text;
    game->texture_lib[EML] = eml_text;
    game->texture_lib[HISTORY] = history_text;
    game->texture_lib[HISTORYS] = historyS_text;
    game->texture_lib[QUICKGAME] = quickgame_text;
    game->texture_lib[QUICKGAMES] = quickgameS_text;
    game->texture_lib[CONTINUE] = continue_text;
    game->texture_lib[CONTINUES] = continueS_text;
    game->texture_lib[VICTORY] = victory_text;
    game->texture_lib[GAMEOVER] = gameover_text;
    game->texture_lib[R] = resume_text;
}

static void load_names(struct game *game)
{
    SDL_Texture *louis_text = IMG_LoadTexture(game->renderer,
            LOUIS_PATH);
    if (!louis_text)
        warnx("cannot louis to SDL_Texture");

    SDL_Texture *louist_text = IMG_LoadTexture(game->renderer,
            LOUIST_PATH);
    if (!louist_text)
        warnx("cannot louist to SDL_Texture");

    SDL_Texture *toto_text = IMG_LoadTexture(game->renderer,
            TOTO_PATH);
    if (!toto_text)
        warnx("cannot toto to SDL_Texture");

    SDL_Texture *totot_text = IMG_LoadTexture(game->renderer,
            TOTOT_PATH);
    if (!totot_text)
        warnx("cannot totot to SDL_Texture");

    SDL_Texture *g_text = IMG_LoadTexture(game->renderer,
            G_PATH);
    if (!g_text)
        warnx("cannot g to SDL_Texture");

    SDL_Texture *gt_text = IMG_LoadTexture(game->renderer,
            GT_PATH);
    if (!gt_text)
        warnx("cannot gt to SDL_Texture");

    game->texture_lib[LOUIS] = louis_text;
    game->texture_lib[LOUIST] = louist_text;
    game->texture_lib[TOTO] = toto_text;
    game->texture_lib[TOTOT] = totot_text;
    game->texture_lib[G] = g_text;
    game->texture_lib[GT] = gt_text;
}

void load_blocks(struct game *game)
{
    SDL_Texture *grass_text = IMG_LoadTexture(game->renderer,
            GRASS_PATH);
    if (!grass_text)
        warnx("cannot convert grass_surface to SDL_Texture");

    SDL_Texture *void_text = IMG_LoadTexture(game->renderer,
            VOID_PATH);
    if (!grass_text)
        warnx("cannot convert void_surface to SDL_Texture");

    SDL_Texture *lava1_text = IMG_LoadTexture(game->renderer,
            LAVA1_PATH);
    if (!lava1_text)
        warnx("cannot convert lava1 to SDL_Texture");

    SDL_Texture *lava2_text = IMG_LoadTexture(game->renderer,
            LAVA2_PATH);
    if (!lava2_text)
        warnx("cannot convert lava2 to SDL_Texture");

    SDL_Texture *lava3_text = IMG_LoadTexture(game->renderer,
            LAVA3_PATH);
    if (!lava3_text)
        warnx("cannot convert lava3 to SDL_Texture");

    SDL_Texture *princess_text = IMG_LoadTexture(game->renderer,
            PRINCESS_PATH);
    if (!princess_text)
        warnx("cannot convert Princess Shepard to SDL_Texture");

    SDL_Texture *brick_text = IMG_LoadTexture(game->renderer,
            BRICK_PATH);
    if (!brick_text)
        warnx("cannot convert brick to SDL_Texture");

    SDL_Texture *dirt_text = IMG_LoadTexture(game->renderer,
            DIRT_PATH);
    if (!dirt_text)
        warnx("cannot convert dirt to SDL_Texture");

    SDL_Texture *stone_text = IMG_LoadTexture(game->renderer,
            STONE_PATH);
    if (!stone_text)
        warnx("cannot convert stone to SDL_Texture");

    SDL_Texture *wood_text = IMG_LoadTexture(game->renderer,
            WOOD_PATH);
    if (!wood_text)
        warnx("cannot convert wood to SDL_Texture");

    game->texture_lib[VOID] = void_text;
    game->texture_lib[GRASS] = grass_text;
    game->texture_lib[LAVA1] = lava1_text;
    game->texture_lib[LAVA2] = lava2_text;
    game->texture_lib[LAVA3] = lava3_text;
    game->texture_lib[PRINCESS] = princess_text;
    game->texture_lib[BRICK] = brick_text;
    game->texture_lib[DIRT] = dirt_text;
    game->texture_lib[STONE] = stone_text;
    game->texture_lib[WOOD] = wood_text;

}

void load_ennemies(struct game *game)
{
    SDL_Texture *er0_text = IMG_LoadTexture(game->renderer,
            ER0_PATH);
    if (!er0_text)
        warnx("cannot convert ennemy right 0 to SDL_Texture");

    SDL_Texture *er1_text = IMG_LoadTexture(game->renderer,
            ER1_PATH);
    if (!er1_text)
        warnx("cannot convert ennemy right 1 to SDL_Texture");

    SDL_Texture *el0_text = IMG_LoadTexture(game->renderer,
            EL0_PATH);
    if (!el0_text)
        warnx("cannot convert ennemy left 0 to SDL_Texture");

    SDL_Texture *el1_text = IMG_LoadTexture(game->renderer,
            EL1_PATH);
    if (!el1_text)
        warnx("cannot convert ennemy left 1 to SDL_Texture");

    SDL_Texture *ef_text = IMG_LoadTexture(game->renderer,
            EF_PATH);
    if (!ef_text)
        warnx("cannot convert ennemy front to SDL_Texture");

    SDL_Texture *efj_text = IMG_LoadTexture(game->renderer,
            EFJ_PATH);
    if (!efj_text)
        warnx("cannot convert ennemy front jump to SDL_Texture");


    game->texture_lib[ER0] = er0_text;
    game->texture_lib[ER1] = er1_text;
    game->texture_lib[EL0] = el0_text;
    game->texture_lib[EL1] = el1_text;
    game->texture_lib[EF] = ef_text;
    game->texture_lib[EFJ] = efj_text;

}

static void load_players_jump(struct game *game)
{
    SDL_Texture *prj_text = IMG_LoadTexture(game->renderer,
            PRJUMP_PATH);
    if (!prj_text)
        warnx("cannot convert player right jump to SDL_Texture");

    SDL_Texture *plj_text = IMG_LoadTexture(game->renderer,
            PLJUMP_PATH);
    if (!plj_text)
        warnx("cannot convert player left jump to SDL_Texture");

    SDL_Texture *pfj_text = IMG_LoadTexture(game->renderer,
            PFJUMP_PATH);
    if (!pfj_text)
        warnx("cannot convert player front jump to SDL_Texture");

    game->texture_lib[PRJ] = prj_text;
    game->texture_lib[PLJ] = plj_text;
    game->texture_lib[PFJ] = pfj_text;
}

void load_players_attacks(struct game *game)
{
    SDL_Texture *ar0_text = IMG_LoadTexture(game->renderer,
            AR0_PATH);
    if (!ar0_text)
        warnx("cannot convert player attack right 0 to SDL_Texture");

    SDL_Texture *ar1_text = IMG_LoadTexture(game->renderer,
            AR1_PATH);
    if (!ar1_text)
        warnx("cannot convert player attack right 1 to SDL_Texture");

    SDL_Texture *al0_text = IMG_LoadTexture(game->renderer,
            AL0_PATH);
    if (!al0_text)
        warnx("cannot convert player attack left 0 to SDL_Texture");

    SDL_Texture *al1_text = IMG_LoadTexture(game->renderer,
            AL1_PATH);
    if (!al1_text)
        warnx("cannot convert player attack left 1 to SDL_Texture");

    game->texture_lib[AR0] = ar0_text;
    game->texture_lib[AR1] = ar1_text;
    game->texture_lib[AL0] = al0_text;
    game->texture_lib[AL1] = al1_text;

}

void load_players(struct game *game)
{
    SDL_Texture *pr0_text = IMG_LoadTexture(game->renderer,
            PR0_PATH);
    if (!pr0_text)
        warnx("cannot convert player right 0 to SDL_Texture");

    SDL_Texture *pr1_text = IMG_LoadTexture(game->renderer,
            PR1_PATH);
    if (!pr1_text)
        warnx("cannot convert player right 1 to SDL_Texture");

    SDL_Texture *pr2_text = IMG_LoadTexture(game->renderer,
            PR2_PATH);
    if (!pr2_text)
        warnx("cannot convert player right 2 to SDL_Texture");

    SDL_Texture *pl0_text = IMG_LoadTexture(game->renderer,
            PL0_PATH);
    if (!pl0_text)
        warnx("cannot convert player left 0 to SDL_Texture");

    SDL_Texture *pl1_text = IMG_LoadTexture(game->renderer,
            PL1_PATH);
    if (!pl1_text)
        warnx("cannot convert player left 1 to SDL_Texture");

    SDL_Texture *pl2_text = IMG_LoadTexture(game->renderer,
            PL2_PATH);
    if (!pl2_text)
        warnx("cannot convert player left 2 to SDL_Texture");

    SDL_Texture *pf_text = IMG_LoadTexture(game->renderer,
            PF_PATH);
    if (!pf_text)
        warnx("cannot convert player front to SDL_Texture");


    game->texture_lib[PL0] = pl0_text;
    game->texture_lib[PL1] = pl1_text;
    game->texture_lib[PL2] = pl2_text;
    game->texture_lib[PR0] = pr0_text;
    game->texture_lib[PR1] = pr1_text;
    game->texture_lib[PR2] = pr2_text;
    game->texture_lib[PF] = pf_text;
    load_players_jump(game);
    load_players_attacks(game);
    load_menus(game);
    load_ennemies(game);
    load_names(game);
}
