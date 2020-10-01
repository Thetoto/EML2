#include <stdlib.h>
#include <stdio.h>

#include "eml2.h"
#include "rendering.h"
#include "vector.h"
#include "parser.h"
#include "inputs.h"
#include "physics.h"
#include "menu.h"

void init_map(struct game *game, int lvl)
{
    char str[100] = { 0 };
    sprintf(str, "romfs:/ressources/maps/lvl%d.eml", lvl);
    if (lvl == 0)
        map_parse(str, game->map, 1);
    else
        map_parse(str, game->map, 0);
    game->map->delims = NULL;
    compute_delims(game->map);
}

void init_game(struct game *game)
{
    game->is_playing = 1;
    game->lvl = 0;
    game->map = malloc(sizeof(struct map));
    init_map(game, game->lvl);
    game->timer = 0;
    game->timer_lava = 0;
}

void destroy_game(struct game *game)
{
    // Free stuff
    free(game->map->delims);
    map_delete(game->map);
    free(game->map);
}

void launch_game(struct game *game)
{
    short death = 0;
    init_game(game);
    while (game->is_playing)
    {
        // Get keyboard inputs
        struct inputs in =
        {
            0, 0, 0, 0, 0, 0
        };
        if (death == 0)
            in = get_inputs();

        // Call physics funcs
        int res = update(game, in);
        if (res > 0)
        {
            float save_y = game->map->players[0]->position.y;
            init_map(game, game->lvl);
            game->map->players[0]->position.y = save_y - 1;
            if (res == 1)
                game->map->players[0]->position.x = 48;
            if (res == 2)
                game->map->players[0]->position.x = 2;
        }
        if (in.cheat && game->map->players[0]->is_attacking)
        {
            init_map(game, ++game->lvl);
            game->map->players[0]->orientation = 0;
            game->map->players[0]->is_ground = 0;
            game->map->players[0]->has_jumped = 0;
            game->map->players[0]->is_attacking = 0;
        }
        if (res == -2)
        {
            render_victory(game);
            break;
        }
        if (res == -1)
        {
            if (death == 1)
            {
                render_defeat(game);
                break;
            }
            Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
            game->music = Mix_LoadMUS("romfs:/ressources/mp3/death.mp3");
            Mix_PlayMusic(game->music, 1);
            death = 1;
            struct vec2 pos = game->map->players[0]->position;
            struct vec2 velo = {0, 0};
            init_map(game, 99);
            game->map->players[0]->position = pos;
            game->map->players[0]->velocity = velo;
            game->map->players[0]->orientation = 0;
            game->map->players[0]->is_ground = 0;
            game->map->players[0]->has_jumped = 0;
            move_jump(game->map->players[0]);
        }

        // Render new frame
        render_frame(game);
    }
    destroy_game(game);

}

void launch_main_menu(struct game *game)
{
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    game->music = Mix_LoadMUS("romfs:/ressources/mp3/intro.mp3");
    Mix_PlayMusic(game->music, -1);
    while (1)
    {
        int res = main_menu(game);
        if (res == 1)
        {
            launch_game(game);
            //Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
            //game->music = Mix_LoadMUS("romfs:/ressources/mp3/intro.mp3");
            //Mix_PlayMusic(game->music, -1);
        }
        else if (res == -1)
        {
            break;
        }
    }
}



void main_old(void)
{

}

#include <switch.h>
#include <stdint.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char* argv[]) {
    void *nullptr = (char*) 0;
    //Do not use anything from <switch.h>
    //gfxInitDefault();
    //consoleInit(nullptr);

    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    romfsInit();
    //Switch screen size: 720p. Must set to full screen.
    SDL_Window* window = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window)
        SDL_Quit();
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
        SDL_Quit();
    SDL_Surface* screen = SDL_GetWindowSurface(window);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, screen);

    struct game game;
    game.renderer = renderer;
    game.window = window;

    SDL_RenderSetScale(renderer, 1.6f, 1.11f);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    Mix_Init(MIX_INIT_MP3);

    game.texture_lib = calloc(60, sizeof(SDL_Texture*));
    load_textures(&game);

    while (appletMainLoop()) {
        //main_old();
        launch_main_menu(&game);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    destroy_sdl(&game);
    free(game.texture_lib);
    //No libnx function calls.
    //gfxExit();

    Mix_FreeMusic(game.music);
    SDL_Quit();
    return 0;
}
