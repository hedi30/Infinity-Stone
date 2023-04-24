//
//  main.h
//  Infinity Stone
//
//  Created by hedi on 6/2/2023.
//

#ifndef main_h
#define main_h
#define PLAYER_SPEED 6
#define SCREEN_HEIGHT 720
#define SCREEN_WIDH 1280
#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
SDL_Renderer *ren;
typedef struct Archer {
    int x;
    int y;
    int dx;
    int dy;
    int hp;
    bool isShooting;
    bool canShoot;
    int arrows;
    SDL_Texture *texture;
}Archer;

typedef struct Enemie
{
    int x;
    int y;
    int dx;
    int dy;
    int hp;
    SDL_Texture * texture;
    
}Enemie;



typedef struct Item
{
    int x;
    int y;
    int dx;
    int dy;
    int hp;
    SDL_Texture * texture;
}Item;



typedef struct {
    int up;
    int down;
    int right;
    int left;
    bool shoot;
    bool start;
    bool quit;
}Keys;

bool fragement_collected;
bool lvl_ended = false;

void freeRect (SDL_Rect ** p);
int playLevel2(void);
int playLevel3(void);
int playLevel1(void);
int StartMenu(void);
void change_archer_position(SDL_Texture * up_texture , SDL_Texture *down_texture , SDL_Texture * arrow_down_texture , SDL_Texture * arrow_up_texture,
                            SDL_Texture * arrow_left_texture , SDL_Texture * left_texture  , SDL_Texture * righ_texture , SDL_Texture * arrow_right_texture ,
                            int lvl
                            );



SDL_Rect *draw_texture(SDL_Renderer **renderer, SDL_Texture *texture, int x, int y);
void do_key_down(SDL_KeyboardEvent *event);
void do_key_up(SDL_KeyboardEvent *event );
#endif /* main_h */
