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
    sprintf(str, "maps/lvl%d.eml", lvl);
    if (lvl == 0)
        map_parse(str, game->map, 1);
    else
        map_parse(str, game->map, 0);
    compute_delims(game->map);
}

void init_game(struct game *game)
{
    game->is_playing = 1;
    game->lvl = 0;
    game->map = malloc(sizeof(struct map));
    init_map(game, game->lvl);
    game->texture_lib = calloc(30, sizeof(SDL_Texture*));
    game->timer = 0;
    // Init SDL2 stuff
    init_sdl(game);
    load_textures(game);
}

void destroy_game(struct game *game)
{
    // Free stuff
    map_delete(game->map);
    destroy_sdl(game);
    free(game->map);
    free(game->texture_lib);
}

int main(void)
{

    struct game game;
    init_game(&game);

    while (game.is_playing)
    {
        // Get keyboard inputs
        struct inputs in = get_inputs();

        // Call physics funcs
        int res = update(&game, in);
        if (res > 0)
        {
            float save_y = game.map->players[0]->position.y;
            init_map(&game, game.lvl);
            game.map->players[0]->position.y = save_y;
            if (res == 1)
                game.map->players[0]->position.x = 49;
            if (res == 2)
                game.map->players[0]->position.x = 1;
        }
        if (res == -1)
            break;

        // Render new frame
        //render_frame(&game);
        main_menu(&game);
    }
    destroy_game(&game);
}
