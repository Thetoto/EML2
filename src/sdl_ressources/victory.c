#include "menu.h"

static void render_VICTORY(struct game *game)
{
    SDL_Rect dstrect;
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 800;
    dstrect.h = 320;

    SDL_RenderCopy(game->renderer, game->texture_lib[VICTORY], NULL, &dstrect);
}

static void render_DEFEAT(struct game *game)
{
    SDL_Rect dstrect;
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 800;
    dstrect.h = 320;

    SDL_RenderCopy(game->renderer, game->texture_lib[GAMEOVER], NULL, &dstrect);
}

static void render_CONTINUE(struct game *game)
{
    SDL_Rect dstrect;
    dstrect.x = 300;
    dstrect.y = 440;
    dstrect.w = 200;
    dstrect.h = 50;

    SDL_RenderCopy(game->renderer, game->texture_lib[CONTINUE], NULL, &dstrect);
}

static void render_CONTINUES(struct game *game)
{
    SDL_Rect dstrect;
    dstrect.x = 300;
    dstrect.y = 440;
    dstrect.w = 200;
    dstrect.h = 50;

    SDL_RenderCopy(game->renderer, game->texture_lib[CONTINUES], NULL,
            &dstrect);
}
#include <stdio.h>
void render_defeat(struct game *game)
{
    int x;
    int y;
    Uint8 mouse_state;
    render_DEFEAT(game);
    SDL_RenderPresent(game->renderer);
    SDL_Delay(1000);

    while (1)
    {
        SDL_PumpEvents();
        mouse_state = SDL_GetMouseState(&x, &y);
        render_DEFEAT(game);
        if (x > 300 && x < 500 && y > 440 && y < 490)
        {
            render_CONTINUES(game);
            if (mouse_state & SDL_BUTTON_LMASK)
                return;
        }
        else
            render_CONTINUE(game);
        SDL_Delay(50);
        SDL_RenderPresent(game->renderer);
    }
}

void render_victory(struct game *game)
{
    int x;
    int y;
    Uint8 mouse_state;
    while (1)
    {
        SDL_PumpEvents();
        mouse_state = SDL_GetMouseState(&x, &y);
        render_BG(game);
        render_VICTORY(game);
        if (x > 300 && x < 500 && y > 440 && y < 490)
        {
            render_CONTINUES(game);
            if (mouse_state & SDL_BUTTON_LMASK)
                return;
        }
        else
            render_CONTINUE(game);
        SDL_Delay(50);
        SDL_RenderPresent(game->renderer);
    }
}
