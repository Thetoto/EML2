#include <unistd.h>
#include "menu.h"
#include <SDL2/SDL_mixer.h>
#include "inputs.h"

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

static void render_nameL(struct game *game)
{
    SDL_Rect dstrect;
    dstrect.x = 80;
    dstrect.y = 400;
    dstrect.w = 640;
    dstrect.h = 320;

    SDL_RenderCopy(game->renderer, game->texture_lib[LOUIS], NULL, &dstrect);
}

static void render_titleL(struct game *game)
{
    SDL_Rect dstrect;
    dstrect.x = 80;
    dstrect.y = 0;
    dstrect.w = 640;
    dstrect.h = 320;

    SDL_RenderCopy(game->renderer, game->texture_lib[LOUIST], NULL, &dstrect);
}
static void render_nameT(struct game *game)
{
    SDL_Rect dstrect;
    dstrect.x = 80;
    dstrect.y = 400;
    dstrect.w = 640;
    dstrect.h = 320;

    SDL_RenderCopy(game->renderer, game->texture_lib[TOTO], NULL, &dstrect);
}

static void render_titleT(struct game *game)
{
    SDL_Rect dstrect;
    dstrect.x = 80;
    dstrect.y = 0;
    dstrect.w = 640;
    dstrect.h = 320;

    SDL_RenderCopy(game->renderer, game->texture_lib[TOTOT], NULL, &dstrect);
}

static void render_nameG(struct game *game)
{
    SDL_Rect dstrect;
    dstrect.x = 80;
    dstrect.y = 400;
    dstrect.w = 640;
    dstrect.h = 320;

    SDL_RenderCopy(game->renderer, game->texture_lib[G], NULL, &dstrect);
}

static void render_titleG(struct game *game)
{
    SDL_Rect dstrect;
    dstrect.x = 80;
    dstrect.y = 0;
    dstrect.w = 640;
    dstrect.h = 320;

    SDL_RenderCopy(game->renderer, game->texture_lib[GT], NULL, &dstrect);
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

static void render_CONTINUESTORY(struct game *game)
{
    SDL_Rect dstrect;
    dstrect.x = 300;
    dstrect.y = 580;
    dstrect.w = 200;
    dstrect.h = 50;

    SDL_RenderCopy(game->renderer, game->texture_lib[CONTINUE], NULL,
            &dstrect);
}

static void render_CONTINUESSTORY(struct game *game)
{
    SDL_Rect dstrect;
    dstrect.x = 300;
    dstrect.y = 580;
    dstrect.w = 200;
    dstrect.h = 50;

    SDL_RenderCopy(game->renderer, game->texture_lib[CONTINUES], NULL,
            &dstrect);
}
void render_story(struct game *game)
{
    SDL_Rect dstrect;
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 800;
    dstrect.h = 640;

    int x;
    int y;
    SDL_RenderCopy(game->renderer, game->texture_lib[R], NULL,
            &dstrect);
    while (1)
    {
        SDL_PumpEvents();
        Uint8 mouse_state = SDL_GetMouseState(&x, &y);
        SDL_RenderCopy(game->renderer, game->texture_lib[R], NULL,
            &dstrect);

        struct inputs in = get_inputs();
        if (in.jump || (x > 300 && x < 500 && y > 580 && y < 630))
        {
            render_CONTINUESSTORY(game);
            if (in.jump || (mouse_state & SDL_BUTTON_LMASK))
                return;
        }
        else
            render_CONTINUESTORY(game);
        SDL_Delay(50);
        SDL_RenderPresent(game->renderer);
    }

}

void render_defeat(struct game *game)
{
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    game->music = Mix_LoadMUS("romfs:/ressources/mp3/death2.mp3");
    Mix_PlayMusic(game->music, 1);

    int x;
    int y;
    Uint8 mouse_state;
    render_DEFEAT(game);
    SDL_RenderPresent(game->renderer);
    SDL_Delay(1000);

    while (1)
    {
        SDL_PumpEvents();
        struct inputs in = get_inputs();
        mouse_state = SDL_GetMouseState(&x, &y);
        render_DEFEAT(game);
        if (in.jump || (x > 300 && x < 500 && y > 440 && y < 490))
        {
            render_CONTINUES(game);
            if (in.jump || (mouse_state & SDL_BUTTON_LMASK))
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
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    game->music = Mix_LoadMUS("romfs:/ressources/mp3/victory.mp3");
    Mix_PlayMusic(game->music, 1);
    SDL_PumpEvents();
    int x;
    int y;
    Uint8 mouse_state;
    while (1)
    {
        SDL_PumpEvents();
        mouse_state = SDL_GetMouseState(&x, &y);
        render_BG(game);
        render_VICTORY(game);
        struct inputs in = get_inputs();
        if (in.jump || (x > 300 && x < 500 && y > 440 && y < 490))
        {
            render_CONTINUES(game);
            if (in.jump || (mouse_state & SDL_BUTTON_LMASK))
                return;
        }
        else
            render_CONTINUE(game);
        SDL_Delay(100);
        SDL_RenderPresent(game->renderer);
    }
}

void render_credits(struct game *game)
{
    render_BG(game);
    render_titleL(game);
    render_nameL(game);

    SDL_RenderPresent(game->renderer);
    SDL_Delay(2000);

    SDL_PumpEvents();
    render_BG(game);
    render_titleT(game);
    render_nameT(game);

    SDL_RenderPresent(game->renderer);
    SDL_Delay(2000);

    SDL_PumpEvents();
    render_BG(game);
    render_titleG(game);
    render_nameG(game);

    SDL_RenderPresent(game->renderer);
    SDL_Delay(2000);
}
