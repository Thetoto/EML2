#pragma once

#include "eml2.h"

#define GAME_NAME "Elves Must Live 2"
#define LAVA1_PATH "romfs:/ressources/blocks/lava2.png"
#define LAVA2_PATH "romfs:/ressources/blocks/lava3.png"
#define LAVA3_PATH "romfs:/ressources/blocks/lava4.png"
#define GRASS_PATH "romfs:/ressources/blocks/grass.png"
#define VOID_PATH "romfs:/ressources/blocks/void.png"
#define PRINCESS_PATH "romfs:/ressources/blocks/princess.png"
#define BRICK_PATH "romfs:/ressources/blocks/brick.png"
#define DIRT_PATH "romfs:/ressources/blocks/dirt.png"
#define STONE_PATH "romfs:/ressources/blocks/stone.png"
#define WOOD_PATH "romfs:/ressources/blocks/woodplanck.png"

#define PL0_PATH "romfs:/ressources/Player/left0.png"
#define PL1_PATH "romfs:/ressources/Player/left1.png"
#define PL2_PATH "romfs:/ressources/Player/left2.png"
#define PLJUMP_PATH "romfs:/ressources/Player/leftjump.png"

#define PR0_PATH "romfs:/ressources/Player/right0.png"
#define PR1_PATH "romfs:/ressources/Player/right1.png"
#define PR2_PATH "romfs:/ressources/Player/right2.png"
#define PRJUMP_PATH "romfs:/ressources/Player/rightjump.png"

#define PF_PATH "romfs:/ressources/Player/front.png"
#define PFJUMP_PATH "romfs:/ressources/Player/frontjump.png"

#define AR0_PATH "romfs:/ressources/Player/attackright0.png"
#define AR1_PATH "romfs:/ressources/Player/attackright1.png"
#define AL0_PATH "romfs:/ressources/Player/attackleft0.png"
#define AL1_PATH "romfs:/ressources/Player/attackleft1.png"

#define EL0_PATH "romfs:/ressources/Ennemies/left0.png"
#define EL1_PATH "romfs:/ressources/Ennemies/left1.png"
#define ER0_PATH "romfs:/ressources/Ennemies/right0.png"
#define ER1_PATH "romfs:/ressources/Ennemies/right1.png"
#define EF_PATH "romfs:/ressources/Ennemies/front.png"
#define EFJ_PATH "romfs:/ressources/Ennemies/frontJ.png"

#define DOOR_PATH "romfs:/ressources/Menus/quit.png"
#define DOORS_PATH "romfs:/ressources/Menus/quitS.png"
#define BG_PATH "romfs:/ressources/Menus/background.png"
#define CREDITS_PATH "romfs:/ressources/Menus/credits.png"
#define CREDITSS_PATH "romfs:/ressources/Menus/creditsS.png"
#define EML_PATH "romfs:/ressources/Menus/eml.png"
#define HISTORY_PATH "romfs:/ressources/Menus/history.png"
#define HISTORYS_PATH "romfs:/ressources/Menus/historyS.png"
#define QUICKGAME_PATH "romfs:/ressources/Menus/quickgame.png"
#define QUICKGAMES_PATH "romfs:/ressources/Menus/quickgameS.png"
#define CONTINUE_PATH "romfs:/ressources/Victory/continue.png"
#define CONTINUES_PATH "romfs:/ressources/Victory/continueS.png"
#define VICTORY_PATH "romfs:/ressources/Victory/victory.png"
#define DEFEAT_PATH "romfs:/ressources/Defeat/gameover.png"
#define BACK_PATH "romfs:/ressources/Menus/back_game.png"

#define LOUIS_PATH "romfs:/ressources/Menus/Louis.png"
#define LOUIST_PATH "romfs:/ressources/Menus/LouisT.png"
#define TOTO_PATH "romfs:/ressources/Menus/Toto.png"
#define TOTOT_PATH "romfs:/ressources/Menus/TotoT.png"
#define G_PATH "romfs:/ressources/Menus/G.png"
#define GT_PATH "romfs:/ressources/Menus/GT.png"

#define R_PATH "romfs:/ressources/Story/resume.png"

#define TIMER_MAX 20
#define TIMER_MAX2 10

#define TIMER_MAX_ATTACK 30
#define TIMER_MAX_ATTACK2 15

#define TIMER_MAX_LAVA 240
#define TIMER_MAX_LAVA3 80


//load.c
void load_blocks(struct game *game);
void load_players(struct game *game);

//rendering.c
void init_sdl(struct game *game);
void destroy_sdl(struct game *game);
void load_textures(struct game *game);
void render_frame(struct game *game);
