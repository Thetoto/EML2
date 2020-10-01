#pragma once

#define WIN_WIDTH 800
#define WIDTH 50
#define WIN_HEIGHT 640
#define HEIGHT 40
#define BLOCK_SIZE 16

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stddef.h>

#include "vector.h"

enum block
{
    VOID = 0,
    GRASS = 1,
    LAVA1 = 2,
    LAVA2 = 3,
    LAVA3 = 4,
    PRINCESS = 5,
    BRICK = 6,
    DIRT = 7,
    STONE = 8,
    WOOD = 9,
    PL0 = 10,
    PL1 = 11,
    PL2 = 12,
    PR0 = 13,
    PR1 = 14,
    PR2 = 15,
    PF = 16,
    PLJ = 17,
    PRJ = 18,
    PFJ = 19,
    AL0 = 20,
    AL1 = 21,
    AR0 = 22,
    AR1 = 23,
    ER0 = 24,
    ER1 = 25,
    EL0 = 26,
    EL1 = 27,
    EF = 28,
    EFJ = 29,
    BG = 30,
    CREDITS = 31,
    CREDITSS = 32,
    EML = 33,
    HISTORY = 34,
    HISTORYS = 35,
    QUICKGAME = 36,
    QUICKGAMES = 37,
    DOOR = 38,
    DOORS = 39,
    CONTINUE = 40,
    CONTINUES = 41,
    VICTORY = 42,
    GAMEOVER = 43,
    BACK = 44,
    LOUIS = 45,
    LOUIST = 46,
    TOTO = 47,
    TOTOT = 48,
    G = 49,
    GT = 50,
    R = 51
};

struct map
{
    struct character **players;
    size_t n_players;

    struct line *delims;
    size_t n_delims;

    enum block **grid; //grid[height][width] merci Louis
};

struct character
{
    short is_player;
    struct map *map;

    int went_left;
    int went_right;
    int went_jump;

    short is_ground;
    short orientation;
    short is_attacking;
    short has_jumped;

    struct vec2 size;

    struct vec2 position;
    struct vec2 velocity;
};

struct game
{
    short is_playing;
    struct map *map;
    int lvl;
    int timer;
    int timer_lava;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture **texture_lib;
    Mix_Music *music;
};
