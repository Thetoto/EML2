#include <SDL.h>
#include <SDL_image.h>
#include <err.h>
#include "rendering.h"

void init_sdl(struct game *game)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        errx(2,"could not init SDL: %s", SDL_GetError());//get explicit err msg

    //init window
    SDL_Window *win = SDL_CreateWindow(GAME_NAME,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WIN_WIDTH, WIN_HEIGHT, 0);

    if (!win)
    {
        warnx("could not init SDL window: %s", SDL_GetError());
        SDL_Quit();
        exit(3);
    }

    //init renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1,
            SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        warnx("could not init SDL renderer: %s", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(4);
    }

    game->renderer = renderer;
    game->window = win;
}

void destroy_sdl(struct game *game)
{
    SDL_DestroyTexture(game->texture_lib[VOID]);
    SDL_DestroyTexture(game->texture_lib[GRASS]);

    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}

void load_textures(struct game *game)
{
    SDL_Surface *grass_surface = IMG_Load(GRASS_PATH);
    if (!grass_surface)
        errx("cannot load %s", GRASS_PATH);

    SDL_Surface *void_surface = IMG_Load(VOID_PATH);
    if (!void_surface)
        errx("cannot load %s", VOID_PATH);

    SDL_Texture *grass_text = SDL_CreateTextureFromSurface(game->renderer,
            grass_surface);
    if (!grass_text)
        errx("cannot convert grass_surface to SDL_Texture");
    SDL_FreeSurface(grass_surface);

    SDL_Texture *void_text = SDL_CreateTextureFromSurface(game->renderer,
            void_surface);
    if (!grass_text)
        errx("cannot convert void_surface to SDL_Texture");
    SDL_FreeSurface(void_surface);

    game->texture_lib[VOID] = void_text;
    game->texture_lib[GRASS] = grass_text;
}

void render_frame(struct game *game)
{

    int imax = WIN_WIDTH / BLOCK_SIZE;
    int jmax = WIN_HEIGHT / BLOCK_SIZE;

    for (int j = 0; j < jmax; j++)
    {
        for (int i = 0; i < imax; i++)
        {
            SDL_rect srcrect;
            SDL_rect dstrect;
            srcrect.x = 0;
            srcrect.y = 0;
            srcrect.w = BLOCK_SIZE;
            srcrect.h = BLOCK_SIZE;

            dstrect.x = i * BLOCK_SIZE;
            dstrect.y = j * BLOCK_SIZE;
            dstrect.w = WIN_WIDTH;
            dstrect.h = WIN_HEIGHT;

            SDL_RenderCopy(game->renderer,
                    game->texture_lib[game->map->grid[j][i]],
                    &srcrect,
                    &dstrect);
        }
    }
}