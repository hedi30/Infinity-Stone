

#include "main.h"

#define ARROW_SPEED 12
#define DISPLAY_H 720
#define DISPLAY_W 1280
#define TILE_SIZE 16


#include <pthread.h>
#include <unistd.h>


Keys keys_archer;
Archer archer;

Item bow,arrow,stone_fragement;



int playLevel1(void)
{
    
 
    Item door;
    
    SDL_Texture *righ_texture,*left_texture, *up_texture,*down_texture,*bull_right_texture,*bull_left_texture,*arrow_right_texture,*arrow_left_texture,*arrow_up_texture,*arrow_down_texture;
    SDL_Texture *monster_demon_texture, *monster_chort_texture,*monster_tentacle_texture,*monster_rokita_texture ;
    SDL_Texture *black_texture;
    SDL_Texture *stone_fragment_texture, *map_texture,*door_open_texture,*door_closed_texture;
  
    SDL_Texture* victory_texture;
    SDL_Texture* bow_texture;
    
    
    Enemie monster_rokita1,
     monster_rokita2,
     monster_rokita3,
     monster_rokita4,
     monster_rokita5,
     monster_rokita6,
     
  
     monster_demon1,
     monster_demon2,
     monster_demon3,
     monster_demon4,
     monster_demon5,
     monster_demon6,


    monster_tentacle1,
    monster_tentacle2;

   

    SDL_Window *window;
    SDL_Event ev;
    
    // map rect
    
    SDL_Rect * map_rect = NULL;
    
  // arrow rect
    
    SDL_Rect * arrow_rect = NULL ;
    
    // archer rect
    SDL_Rect * archer_rect = NULL;
    
    // tentacle rect
    
    SDL_Rect * monster_tentacle1_rect = NULL;
    SDL_Rect * monster_tentacle2_rect = NULL;
    // monster demon rect
    SDL_Rect * monster_demon1_rect = NULL;
    SDL_Rect * monster_demon2_rect = NULL;
    SDL_Rect * monster_demon3_rect = NULL;
    SDL_Rect * monster_demon4_rect = NULL;
    SDL_Rect * monster_demon5_rect = NULL;
    SDL_Rect * monster_demon6_rect = NULL;
    SDL_Rect * monster_demon7_rect = NULL;

    
    // monster rockita rect
    SDL_Rect * monster_rokita1_rect = NULL;
    SDL_Rect * monster_rokita2_rect = NULL;
    SDL_Rect * monster_rokita3_rect = NULL;
    SDL_Rect * monster_rokita4_rect = NULL;
    SDL_Rect * monster_rokita5_rect = NULL;
    SDL_Rect * monster_rokita6_rect = NULL;
    
    // stone fragement rect
    SDL_Rect * fragement_stone_rect = NULL;
    
    // door rect
    
    SDL_Rect * door_rect = NULL;
    
    // ttf rect
    SDL_Rect *Message_rect = NULL;
    
    // victory rect
    
    SDL_Rect *victory_rect = NULL;
    
    
    // bow
    
    SDL_Rect *bow_rect = NULL;

    
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0) {
        fputs(SDL_GetError(), stderr);
        return 1;
    }
    if (TTF_Init() == -1)
    {
       fputs("couldn't load ttf",stdout);
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
    {
        fputs(SDL_GetError(), stderr);
        return 1;
    }
    
    Mix_Music *bgm = Mix_LoadMUS("Adventure-320bit.mp3");
    Mix_Chunk *sound_effect = Mix_LoadWAV("arrow_sound_effect.mp3");
    Mix_Chunk *death_effect = Mix_LoadWAV("death_effect.mp3");
    Mix_Chunk *victory_effect = Mix_LoadWAV("victory.mp3");
    Mix_Chunk *collect_sound_effect = Mix_LoadWAV("collect_sound_effect.mp3");
    if (!(window = SDL_CreateWindow("Infinity stone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAY_W, DISPLAY_H, SDL_WINDOW_SHOWN))) {
        fputs(SDL_GetError(), stderr);
        return 1;
    }

    if (!(ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        fputs(SDL_GetError(), stderr);
        return 1;
    }


    //black
    victory_texture = IMG_LoadTexture(ren, "victory.jpg");
    black_texture = IMG_LoadTexture(ren, "black.jpg");
    
    map_texture = IMG_LoadTexture(ren, "map.bmp");
    
    // door
    door_open_texture = IMG_LoadTexture(ren, "door_open.png");
    door_closed_texture = IMG_LoadTexture(ren, "door_closed.png");
    
    
    // archer_texture
    righ_texture = IMG_LoadTexture(ren, "archer_right.png");
    left_texture = IMG_LoadTexture(ren, "archer_left.png");
    up_texture = IMG_LoadTexture(ren,"archer_up.png");
    down_texture = IMG_LoadTexture(ren,"archer_down.png");
    
    // arrow_texture
    arrow_right_texture = IMG_LoadTexture(ren, "arrow_right.png");
    arrow_left_texture = IMG_LoadTexture(ren, "arrow_left.png");
    arrow_up_texture = IMG_LoadTexture(ren, "arrow_up.png");
    arrow_down_texture = IMG_LoadTexture(ren, "arrow_down.png");
    
    
    
    // monsters texture
    bull_right_texture = IMG_LoadTexture(ren, "bull_right.png");
    bull_left_texture = IMG_LoadTexture(ren, "bull_left.png");
    
    monster_demon_texture = IMG_LoadTexture(ren, "monster_demon.png");
    monster_chort_texture = IMG_LoadTexture(ren,"monster_chort.png");
    monster_tentacle_texture = IMG_LoadTexture(ren,"monster_tentackle.png");
    monster_rokita_texture = IMG_LoadTexture(ren,"monster_rokita.png");
    
    
    //stone fragement
    
    stone_fragment_texture = IMG_LoadTexture(ren, "Stone_Fragment.png");
    
    
    // bone
    
    bow_texture = IMG_LoadTexture(ren, "bow.png");
    
    
    
    //MARK: - SDL ttf
//    TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
//
//
//    SDL_Color White = {255, 255, 255};
//
//    surfaceMessage =
//        TTF_RenderText_Solid(Sans, "Level 1", White);
//
//
//    Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
   
    
    // MARK: - player init
    archer.texture = righ_texture;
    archer.x = 56;
    archer.y = 256;
    archer.isShooting = false;
    archer.hp = 4;
   
    //arrow
    arrow.texture = arrow_right_texture;
    arrow.x = 100;
    arrow.y = 100;
    
    
    //monster demon 1
    monster_demon1.texture = monster_demon_texture;
    monster_demon1.x = 275;
    monster_demon1.y = 342;
    monster_demon1.hp = 1;
    
    
    // monster_demon 2
    monster_demon2.texture = monster_demon_texture;
    monster_demon2.x = 320;
    monster_demon2.y = 226;
    monster_demon2.hp = 1;
  
    // monster_demon 3
    
    monster_demon3.texture = monster_demon_texture;
    monster_demon3.x = 320 + 45;
    monster_demon3.y = 342;
    monster_demon3.hp = 1;
    
    //monster_demon 4
    monster_demon4.texture = monster_demon_texture;
    monster_demon4.x = monster_demon3.x + 45;
    monster_demon4.y = 226;
    monster_demon4.hp = 1;
    
    // monster_demon 5
    
    monster_demon5.texture = monster_demon_texture;
    monster_demon5.x = monster_demon4.x + 45;
    monster_demon5.y = 342;
    monster_demon5.hp = 1;
    
    //monster_demon 6
    
    monster_demon6.texture = monster_demon_texture;
    monster_demon6.x = monster_demon5.x + 45;
    monster_demon6.y = 226;
    monster_demon6.hp = 1;
    
    
    
    //monster tentacle
    monster_tentacle1.x = 560;
    monster_tentacle1.y = 382;
    monster_tentacle1.texture = monster_tentacle_texture;
    monster_tentacle1.hp = 1;
    
    // monster tentacle
    
    monster_tentacle2.x = 254;
    monster_tentacle2.y = 136;
    monster_tentacle2.texture = monster_tentacle_texture;
    monster_tentacle2.hp = 1;
    
    //monster rokita1
    
    monster_rokita1.texture = monster_rokita_texture;
    monster_rokita1.x = 752;
    monster_rokita1.y = 526;
    
    monster_rokita1.hp = 1;
    
    //monster rokita2

    monster_rokita2.texture = monster_rokita_texture;
    monster_rokita2.x = monster_rokita1.x + 45;
    monster_rokita2.y = 420;
    monster_rokita2.hp = 1;
    //monster rokita3

    monster_rokita3.texture = monster_rokita_texture;
    monster_rokita3.x = monster_rokita2.x + 45;
    monster_rokita3.y = 526;
    monster_rokita3.hp = 1;
    
    //monster rokita4
    
    monster_rokita4.texture = monster_rokita_texture;
    monster_rokita4.x = monster_rokita3.x + 45;
    monster_rokita4.y = 420;
    monster_rokita4.hp = 1;
    
    
    //monster rokita5

    monster_rokita5.texture = monster_rokita_texture;
    monster_rokita5.x = monster_rokita4.x + 45;
    monster_rokita5.y = 526;
    monster_rokita5.hp = 1;
    
    
    //monster rokita6

    monster_rokita6.texture = monster_rokita_texture;
    monster_rokita6.x = monster_rokita5.x + 45;
    monster_rokita6.y = 420;
    monster_rokita6.hp = 1;
    
    // stone fragement
    
    stone_fragement.texture = stone_fragment_texture;
    stone_fragement.x = 1226;
    stone_fragement.y = 640;
    stone_fragement.hp = 1;
    
    // door
    
    door.x = 48;
    door.y = 304;
    door.texture = door_closed_texture;
    door.hp = 1;
    
    // bow
    
    bow.x = 23;
    bow.y = 24 ;
    bow.texture = bow_texture;
    bow.hp = 1;
    
    
    bool quit = false;
    while(!quit)
    {
        
        if(!Mix_PlayingMusic())
        {
            
            Mix_VolumeMusic(40);
        
            Mix_PlayMusic(bgm, -1);
        }
        
        while (SDL_PollEvent(&ev)) {
            
            switch (ev.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                    
                case SDL_KEYDOWN:
                    
                    do_key_down(&ev.key);
                   
                    break;
                    
                case SDL_KEYUP:
                    do_key_up(&ev.key);
                    break;
                    
                default:
                    break;
            }
            
            
        }
        change_archer_position(up_texture, down_texture, arrow_down_texture, arrow_up_texture, arrow_left_texture, left_texture, righ_texture, arrow_right_texture,1);
        
        
        // MARK: - movements
        
        if (monster_demon1.hp == 1)
        {
            
            
            if (monster_demon1.y == 342)
            {
                
                monster_demon1.dy = -1;
            }
            
            else if (monster_demon1.y == 226)
            {
                
                
                monster_demon1.dy = 1;
            }
            
        }
        
        
        monster_demon1.y += monster_demon1.dy;
        
        if (monster_demon2.hp == 1)
        {
            
            if (monster_demon2.y == 342)
            {
                
                monster_demon2.dy = -1;
            }
            
            else if (monster_demon2.y == 226) {
                
                
                monster_demon2.dy = 1;
            }
            
        }
        
        
        monster_demon2.y += monster_demon2.dy;
        
        if (monster_demon3.hp == 1)
        {
            
            
            if (monster_demon3.y == 342)
            {
                
                monster_demon3.dy = -1;
            }
            
            else if (monster_demon3.y == 226) {
                
                
                monster_demon3.dy = 1;
            }
            
        }
        
        
        monster_demon3.y += monster_demon3.dy;
        
        
        
        if (monster_demon4.hp == 1)
        {
            
            
            if (monster_demon4.y == 342)
            {
                
                monster_demon4.dy = -1;
            }
            
            else if (monster_demon4.y == 226) {
                
                
                monster_demon4.dy = 1;
            }
            
        }
        
        
        monster_demon4.y += monster_demon4.dy;
        
        
        if (monster_demon5.hp == 1)
        {
            
            
            if (monster_demon5.y == 342)
            {
                
                monster_demon5.dy = -1;
            }
            
            else if (monster_demon5.y == 226) {
                
                
                monster_demon5.dy = 1;
            }
            
        }
        
        
        monster_demon5.y += monster_demon5.dy;
        
        
        
        if (monster_demon6.hp == 1)
        {
            
            
            if (monster_demon6.y == 342)
            {
                
                monster_demon6.dy = -1;
            }
            
            else if (monster_demon6.y == 226) {
                
                
                monster_demon6.dy = 1;
            }
            
        }
        
        
        monster_demon6.y += monster_demon6.dy;
        
        
        
        
        if (monster_tentacle1.hp)
        {
            if (monster_tentacle1.x == 722)
            {
                monster_tentacle1.dx = -3;
            }
            else if (monster_tentacle1.x == 560)
            {
                monster_tentacle1.dx = 3;
            }
            
            
            
        }
        
        monster_tentacle1.x += monster_tentacle1.dx;
        
        if (monster_tentacle2.hp)
        {
            if (monster_tentacle2.x == 254)
            {
                monster_tentacle2.dx = -5;
            }
            else if (monster_tentacle2.x == 14)
            {
                monster_tentacle2.dx = 5;
            }
            
            
            
        }
        
        monster_tentacle2.x += monster_tentacle2.dx;
        
        
        
        if (monster_rokita1.hp == 1)
        {
            
            
            if (monster_rokita1.y == 526)
            {
                
                monster_rokita1.dy = -1;
            }
            
            else if (monster_rokita1.y == 420) {
                
                
                monster_rokita1.dy = 1;
            }
            
        }
        monster_rokita1.y += monster_rokita1.dy;
        
        
        if (monster_rokita2.hp == 1)
        {
            
            
            if (monster_rokita2.y == 526)
            {
                
                monster_rokita2.dy = -1;
            }
            
            else if (monster_rokita2.y == 420) {
                
                
                monster_rokita2.dy = 1;
            }
            
        }
        monster_rokita2.y += monster_rokita2.dy;
        
        if (monster_rokita3.hp == 1)
        {
            
            
            if (monster_rokita3.y == 526)
            {
                
                monster_rokita3.dy = -1;
            }
            
            else if (monster_rokita3.y == 420) {
                
                
                monster_rokita3.dy = 1;
            }
            
        }
        monster_rokita3.y += monster_rokita3.dy;
        
        if (monster_rokita4.hp == 1)
        {
            
            
            if (monster_rokita4.y == 526)
            {
                
                monster_rokita4.dy = -1;
            }
            
            else if (monster_rokita4.y == 420) {
                
                
                monster_rokita4.dy = 1;
            }
            
        }
        monster_rokita4.y += monster_rokita4.dy;
        
        
        if (monster_rokita5.hp == 1)
        {
            
            
            if (monster_rokita5.y == 526)
            {
                
                monster_rokita5.dy = -1;
            }
            
            else if (monster_rokita5.y == 420) {
                
                
                monster_rokita5.dy = 1;
            }
            
        }
        monster_rokita5.y += monster_rokita5.dy;
        
        
        
        if (monster_rokita6.hp == 1)
        {
            
            
            if (monster_rokita6.y == 526)
            {
                
                monster_rokita6.dy = -1;
            }
            
            else if (monster_rokita6.y == 420) {
                
                
                monster_rokita6.dy = 1;
            }
            
        }
        monster_rokita6.y += monster_rokita6.dy;
        
        // MARK: - shooting
        archer.isShooting = keys_archer.shoot;
        
        
        if (archer.hp > 0 &&  archer.isShooting && arrow.hp == 0 && archer.canShoot && archer.arrows > 0)
        {
            Mix_PlayChannel(2, sound_effect, 0);
        }
        
        if (archer.hp > 0 && archer.isShooting && arrow.hp == 0 && archer.canShoot && archer.arrows > 0)
        {
            archer.arrows --;
            if (arrow.texture == arrow_up_texture)
            {
                arrow.x = archer.x;
                arrow.y = archer.y + 16;
                arrow.dx = 0;
                arrow.dy = - ARROW_SPEED;
                arrow.hp = 1;
            }
            
            else if (arrow.texture == arrow_down_texture)
            {
                arrow.x = archer.x;
                arrow.y = archer.y + 16;
                arrow.dx = 0;
                arrow.dy =  ARROW_SPEED;
                arrow.hp = 1;
            }
            
            else if (arrow.texture == arrow_left_texture)
            {
                arrow.x = archer.x;
                arrow.y = archer.y + 16;
                arrow.dx = - ARROW_SPEED;
                arrow.dy = 0;
                arrow.hp = 1;
            }
            else {
                
                arrow.x = archer.x;
                arrow.y = archer.y + 16;
                arrow.dx =  ARROW_SPEED;
                arrow.dy = 0;
                arrow.hp = 1;
            }
            
            
            
        }
        
        arrow.x += arrow.dx;
        arrow.y += arrow.dy;
        
        // MARK: - Collision
        if (arrow.texture == arrow_right_texture)
        {
            if (arrow.x >= 256 && arrow.y >= 28 && arrow.y <= 226)
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
            if (arrow.x >= 722 && arrow.y >= 226 && arrow.y <= 406)
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
            if (arrow.x >= 1238 && arrow.y >= 415 && arrow.y <= 700)
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
        }
        
        if (arrow.texture == arrow_up_texture)
        {
            if (arrow.x <= 254 && arrow.y <= 28)
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
            if (arrow.x >= 254 && arrow.y <= 226)
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
            if (arrow.x >= 740 && arrow.y <= 424 )
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
        }
        
        if (arrow.texture == arrow_left_texture)
        {
            if (arrow.x <= 158 && arrow.y >= 304)
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
            else if (arrow.x <= 560 && arrow.y >= 370 && arrow.y <= 550  )
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
            else if (arrow.x <= 1004  && arrow.y >= 550 && arrow.y <= 700 )
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
            
            else if (arrow.x <= 14)
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
        }
        
        if (arrow.texture == arrow_down_texture)
        {
            if (arrow.x <= 158 && arrow.y >= 286)
            {
               arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
            else if (arrow.y >= 670)
            {
                 arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
            else if (arrow.x >= 548 && arrow.y >= 526  && arrow.x <= 1004)
                
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
            else if (arrow.x > 158 && arrow.y >= 352  && arrow.x <= 554)
            {
               arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
        }
        
        
        
          
        
        
        
        if (SDL_HasIntersection(arrow_rect, monster_demon1_rect))
        {
            monster_demon1.hp = 0;
            arrow.hp = 0;
            freeRect(&monster_demon1_rect);
            freeRect(&arrow_rect);

        }
        if (SDL_HasIntersection(arrow_rect, monster_demon2_rect))
        {
            monster_demon2.hp = 0;
            arrow.hp = 0;
            freeRect(&monster_demon2_rect);
            freeRect(&arrow_rect);

        }
        if (SDL_HasIntersection(arrow_rect, monster_demon3_rect))
        {
            monster_demon3.hp = 0;
            arrow.hp = 0;
            freeRect(&monster_demon3_rect);
            freeRect(&arrow_rect);

        }
        if (SDL_HasIntersection(arrow_rect, monster_demon4_rect))
        {
            monster_demon4.hp = 0;
            freeRect(&monster_demon4_rect);


            arrow.hp = 0;
            freeRect(&arrow_rect);

        }
        if (SDL_HasIntersection(arrow_rect, monster_demon5_rect))
        {
            monster_demon5.hp = 0;
            freeRect(&monster_demon5_rect);
            arrow.hp = 0;
            freeRect(&arrow_rect);

        }
        if (SDL_HasIntersection(arrow_rect, monster_demon6_rect))
        {
            monster_demon6.hp = 0;
            freeRect(&monster_demon6_rect);


            arrow.hp = 0;
            freeRect(&arrow_rect);

        }
        if (SDL_HasIntersection(arrow_rect, monster_tentacle1_rect))
        {
            monster_tentacle1.hp = 0;
            freeRect(&monster_tentacle1_rect);
           
            
            arrow.hp = 0;
            freeRect(&arrow_rect);
            
        }
        
        if (SDL_HasIntersection(arrow_rect, monster_tentacle2_rect))
        {
            monster_tentacle2.hp = 0;
            freeRect(&monster_tentacle2_rect);
            
            arrow.hp = 0;
            freeRect(&arrow_rect);
            
        }
        
        
        
        if (
            SDL_HasIntersection(archer_rect, monster_rokita1_rect) ||
            SDL_HasIntersection(archer_rect, monster_rokita2_rect) ||
            SDL_HasIntersection(archer_rect, monster_rokita3_rect) ||
            SDL_HasIntersection(archer_rect, monster_rokita4_rect) ||
            SDL_HasIntersection(archer_rect, monster_rokita5_rect) ||
            SDL_HasIntersection(archer_rect, monster_rokita6_rect) ||
            SDL_HasIntersection(archer_rect, monster_demon1_rect) ||
            SDL_HasIntersection(archer_rect, monster_demon2_rect) ||
            SDL_HasIntersection(archer_rect, monster_demon3_rect) ||
            SDL_HasIntersection(archer_rect, monster_demon4_rect) ||
            SDL_HasIntersection(archer_rect, monster_demon5_rect) ||
            SDL_HasIntersection(archer_rect, monster_demon6_rect) ||
            SDL_HasIntersection(archer_rect, monster_tentacle1_rect) ||
            SDL_HasIntersection(archer_rect, monster_tentacle2_rect)
            
            
        )
        {
                archer.hp = 0;
                freeRect(&archer_rect);
               
                arrow.hp = 0;
                freeRect(&arrow_rect);
                Mix_PlayChannel(2, death_effect, 0);
                return 0;
            
            
        }
        
        
        if (SDL_HasIntersection(arrow_rect, monster_rokita1_rect))
        {
           
            monster_rokita1.hp = 0;
            freeRect(&monster_rokita1_rect);

            arrow.hp = 0;
            freeRect(&arrow_rect);
        }
        if (SDL_HasIntersection(arrow_rect, monster_rokita2_rect))
        {

            
            monster_rokita2.hp = 0;
            freeRect(&monster_rokita2_rect);
            arrow.hp = 0;
            freeRect(&arrow_rect);
            printf("%p\n",arrow_rect);
            
        }
        if (SDL_HasIntersection(arrow_rect, monster_rokita3_rect))
        {
            monster_rokita3.hp = 0;
            freeRect(&monster_rokita3_rect);
          
            arrow.hp = 0;
            freeRect(&arrow_rect);
            
        }
        if (SDL_HasIntersection(arrow_rect, monster_rokita4_rect))
        {
            monster_rokita4.hp = 0;
            freeRect(&monster_rokita4_rect);
            
            arrow.hp = 0;
            freeRect(&arrow_rect);
           
        }
        
        if (SDL_HasIntersection(arrow_rect, monster_rokita5_rect))
        {
            monster_rokita5.hp = 0;
            freeRect(&monster_rokita5_rect);
            
            arrow.hp = 0;
            freeRect(&arrow_rect);
        }
        if (SDL_HasIntersection(arrow_rect, monster_rokita6_rect))
        {
            monster_rokita6.hp = 0;
            freeRect(&monster_rokita6_rect);
           
            
            arrow.hp = 0;
            freeRect(&arrow_rect);
           
        }
        
        if (SDL_HasIntersection(archer_rect, fragement_stone_rect))
        {
            
            stone_fragement.hp = 0;
            freeRect(&fragement_stone_rect);
            door.texture = door_open_texture;
            fragement_collected = true;
            archer.arrows += 3;
            
            Mix_PlayChannel(2, collect_sound_effect, 0);
            
            
        }
        
        if (fragement_collected == true)
        {
            if (SDL_HasIntersection(archer_rect,door_rect))
            {
                lvl_ended = true;
                archer.hp = 0;
                freeRect(&archer_rect);
                Mix_PlayChannel(2, victory_effect, 0);
            
//                surfaceMessage =
//                    TTF_RenderText_Solid(Sans, "Victory", White);
//
//
//                Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
                
            }
        }
        
        if (SDL_HasIntersection(bow_rect, archer_rect))
        {
            bow.hp = 0;
            
            freeRect(&bow_rect);
            archer.arrows = 5;
            archer.canShoot = true;
            
        }
        
       
      
        
        printf("x:%d, y:%d\n",archer.x,archer.y);
        
        // MARK: - drawing textures
        
        freeRect(&map_rect);
        map_rect = draw_texture(&ren,  map_texture, 0, 0);
        
        freeRect(&door_rect);
        door_rect = draw_texture(&ren, door.texture, door.x, door.y);
        
        
        if (bow.hp)
        {
            freeRect(&bow_rect);
            bow_rect =  draw_texture(&ren, bow.texture, bow.x, bow.y);
        }
        
        
        
        
        if (archer.hp)
        {
            freeRect(&archer_rect);
            archer_rect = draw_texture(&ren, archer.texture, archer.x, archer.y);
            
        }
       
        
        
        if (monster_demon1.hp)
        {
            freeRect(&monster_demon1_rect);
            monster_demon1_rect = draw_texture(&ren, monster_demon1.texture, monster_demon1.x, monster_demon1.y);
        }
        
        if (monster_demon2.hp)
        {
            freeRect(&monster_demon2_rect);
           monster_demon2_rect = draw_texture(&ren, monster_demon2.texture, monster_demon2.x, monster_demon2.y);
        }
        
        if (monster_demon3.hp)
        {
            
            freeRect(&monster_demon3_rect);
           monster_demon3_rect =  draw_texture(&ren, monster_demon3.texture, monster_demon3.x, monster_demon3.y);
        }
        
        if (monster_demon4.hp)
        {
            freeRect(&monster_demon4_rect);
            monster_demon4_rect = draw_texture(&ren, monster_demon4.texture, monster_demon4.x, monster_demon4.y);
            
        }
        
        if (monster_demon5.hp)
        {
            
            freeRect(&monster_demon5_rect);
            monster_demon5_rect =   draw_texture(&ren, monster_demon5.texture, monster_demon5.x, monster_demon5.y);
        }
        
        
        if (monster_demon6.hp)
        {
            freeRect(&monster_demon6_rect);
            monster_demon6_rect =  draw_texture(&ren, monster_demon6.texture, monster_demon6.x, monster_demon6.y);
        }
        
        
        
        if (monster_tentacle1.hp)
        {
            freeRect(&monster_tentacle1_rect);
            monster_tentacle1_rect = draw_texture(&ren, monster_tentacle1.texture, monster_tentacle1.x, monster_tentacle1.y);
        }
        
        if (monster_tentacle2.hp)
        {
            freeRect(&monster_tentacle2_rect);
            monster_tentacle2_rect = draw_texture(&ren, monster_tentacle2.texture, monster_tentacle2.x, monster_tentacle2.y);
        }
        
      
        if (arrow.hp && archer.hp)
            
        {   freeRect(&arrow_rect);
            arrow_rect = draw_texture(&ren, arrow.texture, arrow.x, arrow.y);
        }
        
        
        if (monster_rokita1.hp)
        {
            
            freeRect(&monster_rokita1_rect);
            monster_rokita1_rect = draw_texture(&ren, monster_rokita1.texture, monster_rokita1.x, monster_rokita1.y);
            
        }
        
        if (monster_rokita2.hp)
        {
            
            freeRect(&monster_rokita2_rect);
            monster_rokita2_rect = draw_texture(&ren, monster_rokita2.texture, monster_rokita2.x, monster_rokita2.y);
            
        }
        
        if (monster_rokita3.hp)
        {
            
            freeRect(&monster_rokita3_rect);

            monster_rokita3_rect = draw_texture(&ren, monster_rokita3.texture, monster_rokita3.x, monster_rokita3.y);
            
        }
        
        if (monster_rokita4.hp)
        {
            
            freeRect(&monster_rokita4_rect);

            monster_rokita4_rect = draw_texture(&ren, monster_rokita4.texture, monster_rokita4.x, monster_rokita4.y);
            
        }
        
        if (monster_rokita5.hp)
        {
            
            freeRect(&monster_rokita5_rect);

            monster_rokita5_rect = draw_texture(&ren, monster_rokita5.texture, monster_rokita5.x, monster_rokita5.y);
            
        }
        
        if (monster_rokita6.hp)
        {
            freeRect(&monster_rokita6_rect);

            monster_rokita6_rect = draw_texture(&ren, monster_rokita6.texture, monster_rokita6.x, monster_rokita6.y);
            
        }
        
        if (stone_fragement.hp)
        {
            
            freeRect(&fragement_stone_rect);

            fragement_stone_rect = draw_texture(&ren, stone_fragement.texture, stone_fragement.x, stone_fragement.y);
        }
        
       
        
        
        if (lvl_ended)
            
        {
            
            
            freeRect(&victory_rect);
           victory_rect = draw_texture(&ren, victory_texture, 0, 0);
            
            freeRect(&bow_rect);
            
            freeRect(&archer_rect);
            
            
            freeRect(&arrow_rect);
            
            freeRect(&monster_demon1_rect);
            

            freeRect(&monster_demon2_rect);
            

            freeRect(&monster_demon3_rect);
           

            freeRect(&monster_demon4_rect);
            

            freeRect(&monster_demon5_rect);
            

            freeRect(&monster_demon6_rect);
          

            freeRect(&monster_demon7_rect);
           

            freeRect(&monster_tentacle1_rect);
            freeRect(&monster_tentacle2_rect);

            freeRect(&monster_rokita1_rect);
            

            freeRect(&monster_rokita2_rect);
           

            freeRect(&monster_rokita3_rect);
            

            freeRect(&monster_rokita4_rect);
            

            freeRect(&monster_rokita5_rect);
           

            freeRect(&monster_rokita6_rect);
            

            freeRect(&fragement_stone_rect);
            
            freeRect(&door_rect);
           

            freeRect(&Message_rect);

           

            freeRect(&victory_rect);
           
            freeRect(&map_rect);
            
            freeRect(&bow_rect);
           
            
                
            Mix_FreeChunk(sound_effect);
            Mix_FreeChunk(victory_effect);
            Mix_FreeChunk(death_effect);
            Mix_FreeChunk(collect_sound_effect);
            Mix_Quit();

            Mix_FreeMusic(bgm);
            
            SDL_DestroyRenderer(ren);
            SDL_DestroyWindow(window);
            SDL_Quit();
            
            
            return 1;
           
        }
            
        
        SDL_RenderPresent(ren);
        
        

    }
   
    // MARK: - free and quit
    
    
    return 0;
}

void run_game(void) {
    int current_level = 1;
    bool level_result = false;

    while (current_level <= 3) {
        switch (current_level) {
            case 1:
                level_result = playLevel1();
                break;
            case 2:
                level_result = playLevel2();
                break;
            case 3:
                level_result = playLevel3();
                break;
            default:
                break;
        }

        if (level_result) {
            current_level++; // Move to the next level
        } else {
            // Restart the current level
        }
    }
}

int main(int argc, char **argv) {
  
    system("pwd");
    playLevel2();
//run_game();
    
    
    
    
 
    return 0;
}




SDL_Rect *draw_texture(SDL_Renderer **renderer, SDL_Texture *texture, int x, int y)
{

    SDL_Rect *rect = malloc(sizeof(rect));

    rect->x = x;
    rect->y = y;
    rect->w = 0;
    rect->h = 0;
    
    SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);

    SDL_RenderCopy(*renderer, texture, NULL, rect);
    return rect;
}


 void change_archer_position(SDL_Texture * up_texture , SDL_Texture *down_texture , SDL_Texture * arrow_down_texture , SDL_Texture * arrow_up_texture,
                             SDL_Texture * arrow_left_texture , SDL_Texture * left_texture  , SDL_Texture * righ_texture , SDL_Texture * arrow_right_texture,
                             int lvl
                             )
{
     
     if (lvl == 1)
     {
         // MARK: - archer bounds
           if (archer.x < 288)
           {
               if (archer.y >= TILE_SIZE + 16)
               {
                   if (keys_archer.up)
                       
                   {
                       
                       archer.texture = up_texture;
                       
                       if (arrow.hp == 0)
                       {
                           arrow.texture = arrow_up_texture;
                       }
                       
                       archer.y -= PLAYER_SPEED;
                   }
               }
           }
           
           
           
           else if (archer.x >= 750)
           {
               if (archer.y >= 430 )
               {
                   if (keys_archer.up)
                   {
                       
                       archer.texture = up_texture;
                       
                       if (arrow.hp == 0)
                       {
                           arrow.texture = arrow_up_texture;
                       }
                       
                       
                       archer.y -= PLAYER_SPEED;
                   }
               }
           }
           
           else if (archer.x >= 288)
           {
               if (archer.y >= 230 )
               {
                   if (keys_archer.up)
                   {
                       if (arrow.hp == 0)
                       {
                           arrow.texture = arrow_up_texture;
                       }
                       
                      
                       archer.texture = up_texture;

                       archer.y -= PLAYER_SPEED;
                   }
               }
           }
          
          
           // move down
           
           if ( archer.x >= 1005)
           {
               if (archer.y <= 650)
               {
                   if (keys_archer.down)
                   {
                       if (arrow.hp == 0)
                       {
                           arrow.texture = arrow_down_texture;
                       }
                       
                       archer.texture = down_texture;

                       archer.y += PLAYER_SPEED;
                   }
               }
              
           }
           else if (archer.x < 160)
           {
               if (archer.y <= 280)
               {
                   if (keys_archer.down)
                   {
                       if (arrow.hp == 0)
                       {
                           arrow.texture = arrow_down_texture;
                       }
                       archer.texture = down_texture;

                       archer.y += PLAYER_SPEED;
                   }
               }
           }
           
           else if (archer.x > 552)
           {
               if (archer.y <= 520)
               {
                   if (keys_archer.down)
                   {
                       if (arrow.hp == 0)
                       {
                           arrow.texture = arrow_down_texture;
                       }
                       archer.texture = down_texture;

                       archer.y += PLAYER_SPEED;
                   }
               }
           }
           
           else if (archer.x > 155)
           {
               if (archer.y <= 350)
               {
                   if (keys_archer.down)
                   {
                       if (arrow.hp == 0)
                       {
                           arrow.texture = arrow_down_texture;
                       }
                       archer.texture = down_texture;

                       archer.y += PLAYER_SPEED;
                   }
               }
           }
           
          
           
           //left
           if (archer.x < 560)
           {
               
          if ((archer.x > 160 && archer.y >= 292))
           {
               if (keys_archer.left)
               {
                   if (arrow.hp == 0)
                   {
                       arrow.texture = arrow_left_texture;
                   }
                   archer.texture = left_texture;

                   archer.x -= PLAYER_SPEED;
               }
           }
           
           if ((archer.y <= 288 && archer.x > TILE_SIZE))
           {
               if (keys_archer.left)
               {
                   archer.texture = left_texture;
                   if (arrow.hp == 0)
                   {
                       arrow.texture = arrow_left_texture;
                   }

                   archer.x -= PLAYER_SPEED;
               }
           }
               
           }
              
           
          
           
           else if (archer.x >= 1000)
           {
               if (archer.y <= 520)
               {
                   if (keys_archer.left)
                   {
                       archer.texture = left_texture;
                       if (arrow.hp == 0)
                       {
                           arrow.texture = arrow_left_texture;
                       }
                       archer.x -= PLAYER_SPEED;
                   }
               }
               else if (archer.x >= 1010 && archer.y >= 520)
               {
                   if (keys_archer.left)
                   {
                       archer.texture = left_texture;
                       if (arrow.hp == 0)
                           
                       {
                           arrow.texture = arrow_left_texture;
                       }
                       archer.x -= PLAYER_SPEED;
                   }
               }
           }
           
           
           else if (archer.x >= 560)
          {
              if (archer.y <= 344)
              {
                  if (keys_archer.left)
                  {
                      archer.texture = left_texture;
                      if (arrow.hp == 0)
                      {
                          arrow.texture = arrow_left_texture;
                      }
                      archer.x -= PLAYER_SPEED;
                  }
              }
              else if (archer.x > 560 && archer.y >= 344)
              {
                  if (keys_archer.left)
                  {
                      archer.texture = left_texture;
                      if (arrow.hp == 0)
                      {
                          arrow.texture = arrow_left_texture;
                      }
                      archer.x -= PLAYER_SPEED;
                  }
              }
             
          }
           
           

           
          
           
          if ((archer.x <= 250 && archer.y <= 214) || (archer.y >= 220 && archer.x <= 720) || (archer.y >= 424 && archer.x <= 1232 ))
          {
              if (keys_archer.right)
              {
                  archer.texture = righ_texture;
                  if (arrow.hp == 0)
                  {
                      arrow.texture = arrow_right_texture;
                  }
                  archer.x += PLAYER_SPEED;
              }
          }
     }
     
     
     // lvl 2
     
     else if (lvl == 2)
     {
         if (archer.x > 806 && archer.y > 22)
         {
             if (keys_archer.up)

             {

                 archer.texture = up_texture;

                 if (arrow.hp == 0)
                 {
                     arrow.texture = arrow_up_texture;
                 }

                 archer.y -= PLAYER_SPEED;
             }
         }
       
      
         
        else if (archer.y < 368)
         {
             if (( archer.x < 434 && archer.y > 22) || (archer.x > 434 && archer.y >= 100)  || ( archer.x > 810 && archer.y > 22))
             {
                 if (keys_archer.up)
                     
                 {
                     
                     archer.texture = up_texture;
                     
                     if (arrow.hp == 0)
                     {
                         arrow.texture = arrow_up_texture;
                     }
                     
                     archer.y -= PLAYER_SPEED;
                 }
             }
         }
         
         else if ((archer.y > 386 && archer.x > 441 && archer.y >= 526) || (archer.y >= 386 && archer.x >= 20 && archer.x < 452))
         {
             if (keys_archer.up)

             {
                    archer.texture = up_texture;

                 if (arrow.hp == 0)
                 {
                     arrow.texture = arrow_up_texture;
                 }

                 archer.y -= PLAYER_SPEED;
             }
         }
         
         
       
        
         
         if (archer.x >= 464 && archer.x <= 788 && archer.y <= 190 )
        {
            if (keys_archer.down)
            {
                if (arrow.hp == 0)
                {
                    arrow.texture = arrow_down_texture;
                }
                
                archer.texture = down_texture;

                archer.y += PLAYER_SPEED;
            }
        }
         
        
        else if (archer.x >= 452 && archer.x <= 800 && archer.y < 616 && archer.y > 500)
        {
            
            if (keys_archer.down)
            {
                if (arrow.hp == 0)
                {
                    arrow.texture = arrow_down_texture;
                }
                
                archer.texture = down_texture;

                archer.y += PLAYER_SPEED;
            }
        }
         
         
         
       
       else  if (archer.y < 340 && archer.x < 452)
         {
             if (keys_archer.down)
             {
                 if (arrow.hp == 0)
                 {
                     arrow.texture = arrow_down_texture;
                 }
                 
                 archer.texture = down_texture;

                 archer.y += PLAYER_SPEED;
             }
         }
         
       
         
         else if (archer.y >= 370 && archer.y < 670 && archer.x < 452)
         {
             if (keys_archer.down)
             {
                 if (arrow.hp == 0)
                 {
                     arrow.texture = arrow_down_texture;
                 }
                 
                 archer.texture = down_texture;

                 archer.y += PLAYER_SPEED;
             }
         }
         
        
         
         
         else if (archer.x > 806 && archer.y >= 20 && archer.y < 670  )
             
         {
             if (keys_archer.down)
             {
                 if (arrow.hp == 0)
                 {
                     arrow.texture = arrow_down_texture;
                 }
                 
                 archer.texture = down_texture;

                 archer.y += PLAYER_SPEED;
             }
         }
         
        
         
         
         if (archer.x < 434 && archer.x > 20)
         {
            
             if (keys_archer.left)
             {
                 if (arrow.hp == 0)
                 {
                     arrow.texture = arrow_left_texture;
                 }
                 archer.texture = left_texture;
                 archer.x -= PLAYER_SPEED;
             }
             
         }
         
         else if (archer.x >= 434  )
         {
             
             
            if (!(archer.x == 818 && archer.y > 202 && archer.y <= 520) && !(archer.x == 818 && archer.y >= 20  && archer.y <= 86) && !(archer.x == 818 && archer.y >= 622 && archer. y <= 674) && !(archer.x == 476 && archer.y >= 88 && archer.y <= 202 ))
            {
                if (keys_archer.left)
                {
                    if (arrow.hp == 0)
                    {
                        arrow.texture = arrow_left_texture;
                    }
                    archer.texture = left_texture;

                    archer.x -= PLAYER_SPEED;
                }
            }
            

             
         }
         
         
       
         
        
         
            
          if ((archer.x < 800 && !(archer.x >= 434 && archer.y >= 380 && archer.y <= 520) && !(archer.x >= 440 && archer.y >= 622 && archer.y <= 674 )
              
              
              && !(archer.y > 19 && archer.y <= 344 )
              )
              || (archer.x >= 476 && archer.x < 800)
              )
          {
              
            
              if (keys_archer.right)
              {
                  archer.texture = righ_texture;
                  if (arrow.hp == 0)
                  {
                      arrow.texture = arrow_right_texture;
                  }
                  archer.x += PLAYER_SPEED;
              }
          }
         
         
       else  if (archer.y <= 344 && archer.y >= 15 && archer.x < 434)
            
        {
              if (archer.x <= 434)
              {
                  
                  if (keys_archer.right)
                  {
                      archer.texture = righ_texture;
                      if (arrow.hp == 0)
                      {
                          arrow.texture = arrow_right_texture;
                      }
                      archer.x += PLAYER_SPEED;
                  }
              }
            
              
            
            
           
            
            
            
        }
         
          else if (archer.x >= 800 && archer.x <= 1238)
           {
               if (keys_archer.right)
               {
                   archer.texture = righ_texture;
                   if (arrow.hp == 0)
                   {
                       arrow.texture = arrow_right_texture;
                   }
                   archer.x += PLAYER_SPEED;
               }
           }
         
        
         
        
         
         


         
         
         
        
         
     }
   
}


void do_key_down(SDL_KeyboardEvent *event)
{
    
   
    
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_F1)
        {
            keys_archer.start = true;
            
        }
       
        if (event->keysym.scancode == SDL_SCANCODE_W)
        {
            keys_archer.up = 1;
            
        }

        if (event->keysym.scancode == SDL_SCANCODE_S)
        {
            keys_archer.down = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_A)
        {
            keys_archer.left = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_D)
        {
            keys_archer.right = 1;
        }
        
        if(event->keysym.scancode == SDL_SCANCODE_SPACE)
        {
            
            keys_archer.shoot = true;
        }

      

        
    }
}
void do_key_up(SDL_KeyboardEvent *event )
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_W)
        {
            keys_archer.up = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_S)
        {
            keys_archer.down = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_A)
        {
            keys_archer.left = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_D)
        {
            keys_archer.right = 0;
        }
        
        if (event->keysym.scancode == SDL_SCANCODE_SPACE)
        {
            keys_archer.shoot = false;
        }

     

    }
}


void freeRect (SDL_Rect ** p) {
    
    
 free(*p);
*p = NULL;
   
}


int playLevel2(void)
{
    
    SDL_Window *window;
    SDL_Event ev;
    
    SDL_Texture * righ_texture , *left_texture,*up_texture, *down_texture , *arrow_up_texture, *arrow_down_texture,*arrow_right_texture,*arrow_left_texture;
    
    SDL_Texture *map_texture ;
    
   SDL_Rect *map_rect = NULL;
    SDL_Rect *archer_rect = NULL;
   
    
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0) {
        fputs(SDL_GetError(), stderr);
        return 1;
    }
    if (TTF_Init() == -1)
    {
        fputs("couldn't load ttf",stdout);
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
    {
        fputs(SDL_GetError(), stderr);
        return 1;
    }
    
    Mix_Music *bgm = Mix_LoadMUS("Adventure-320bit.mp3");
    Mix_Chunk *sound_effect = Mix_LoadWAV("arrow_sound_effect.mp3");
    Mix_Chunk *death_effect = Mix_LoadWAV("death_sound.mp3");
    Mix_Chunk *victory_effect = Mix_LoadWAV("victory.mp3");
    Mix_Chunk *collect_sound_effect = Mix_LoadWAV("collect_sound_effect.mp3");
    if (!(window = SDL_CreateWindow("Infinity stone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAY_W, DISPLAY_H, SDL_WINDOW_SHOWN))) {
        fputs(SDL_GetError(), stderr);
        return 1;
    }
    
    if (!(ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        fputs(SDL_GetError(), stderr);
        return 1;
    }
    
    // archer_texture
    righ_texture = IMG_LoadTexture(ren, "archer_right.png");
    left_texture = IMG_LoadTexture(ren, "archer_left.png");
    up_texture = IMG_LoadTexture(ren,"archer_up.png");
    down_texture = IMG_LoadTexture(ren,"archer_down.png");
    
    // arrow_texture
    arrow_right_texture = IMG_LoadTexture(ren, "arrow_right.png");
    arrow_left_texture = IMG_LoadTexture(ren, "arrow_left.png");
    
   
    arrow_up_texture = IMG_LoadTexture(ren, "arrow_up.png");
    arrow_down_texture = IMG_LoadTexture(ren, "arrow_down.png");
    
    map_texture = IMG_LoadTexture(ren, "map_lvl2.png");
    
    SDL_Rect * arrow_rect = NULL;
    
    // MARK: - player init
    archer.texture = righ_texture;
    archer.x = 56;
    archer.y = 400;
    archer.isShooting = false;
    archer.hp = 4;
    
    
    //MARK: - arrow init
    
    arrow.texture = arrow_right_texture;
    arrow.hp = 0;
   
    
    
    
    bool quit = false;
    while(!quit)
    {
        
        if(!Mix_PlayingMusic())
        {
            
            Mix_VolumeMusic(40);
            
            Mix_PlayMusic(bgm, -1);
        }
        
        while (SDL_PollEvent(&ev)) {
            
            switch (ev.type)
            {
                    
               
                    
                case SDL_QUIT:
                    quit = true;
                    break;
                    
                case SDL_KEYDOWN:
                    
                    do_key_down(&ev.key);
                    
                    break;
                    
                case SDL_KEYUP:
                    do_key_up(&ev.key);
                    break;
                    
                default:
                    break;
            }
            
            
        }
        
        
        printf("x:%d, y:%d\n",archer.x,archer.y);
        
        
        change_archer_position(up_texture, down_texture, arrow_down_texture, arrow_up_texture, arrow_left_texture, left_texture, righ_texture, arrow_right_texture , 2);
        
        //MARK: - archer shooting lvl 2
        
        
        archer.isShooting = keys_archer.shoot;
        archer.canShoot = 1;
        archer.arrows = 4;
       
        
        
        if (archer.hp > 0 &&  archer.isShooting && arrow.hp == 0 && archer.canShoot && archer.arrows > 0)
        {
            Mix_PlayChannel(2, sound_effect, 0);
        }
        
        if (archer.hp > 0 && archer.isShooting && arrow.hp == 0 && archer.canShoot && archer.arrows > 0)
        {
           
            if (arrow.texture == arrow_up_texture)
            {
                arrow.x = archer.x;
                arrow.y = archer.y + 16;
                arrow.dx = 0;
                arrow.dy = - ARROW_SPEED;
                arrow.hp = 1;
            }
            
            else if (arrow.texture == arrow_down_texture)
            {
                arrow.x = archer.x;
                arrow.y = archer.y + 16;
                arrow.dx = 0;
                arrow.dy =  ARROW_SPEED;
                arrow.hp = 1;
            }
            
            else if (arrow.texture == arrow_left_texture)
            {
                arrow.x = archer.x;
                arrow.y = archer.y + 16;
                arrow.dx = - ARROW_SPEED;
                arrow.dy = 0;
                arrow.hp = 1;
            }
            else {
                
                arrow.x = archer.x;
                arrow.y = archer.y + 16;
                arrow.dx =  ARROW_SPEED;
                arrow.dy = 0;
                arrow.hp = 1;
            }
            
            
            
        }
        
        arrow.x += arrow.dx;
        arrow.y += arrow.dy;
        
        
        //MARK: - collision level2
        
        if (arrow.texture == arrow_right_texture)
        {
           
            if (arrow.x < 818)
            {
                if (arrow.y <= 360 && arrow.y >= 20 && arrow.x >= 434  )
               {
                   arrow.hp = 0;
                   freeRect(&arrow_rect);
               }
               
               else if (arrow.x >= 440 && arrow.y >= 382 && arrow.y <= 520 )
                   
               {
                   arrow.hp = 0;
                   freeRect(&arrow_rect);
               }
               
               else if (arrow.x >= 440 && arrow.y >= 628 && arrow.y <= 900)
               {
                   arrow.hp = 0;
                   freeRect(&arrow_rect);
               }
            }
            
            else if (arrow.x >= 818)
            {
                
                if (arrow.x >= 1238)
                {
                    arrow.hp = 0;
                    freeRect(&arrow_rect);
                }
            }
          
            
          
            
           
        }
        
        if (arrow.texture == arrow_up_texture)
        {
            
           
             if (archer.y <= 382 && arrow.y <= 15)
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
            else if (arrow.x >= 20 && arrow.x <= 434 && arrow.y <= 382 && archer.y >= 382)
             {
                arrow.hp = 0;
                freeRect(&arrow_rect);
             }
            
           else if (arrow.x >= 458 && arrow.x <= 812 && arrow.y <= 94 && archer.y < 200  )
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
           else  if (arrow.x >= 458 && arrow.x <= 812 && arrow.y <= 520 && archer.y > 520)
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
            else if (arrow.x >= 812 && arrow.y <= 15)
                
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
           
            
            
        }
        
        if (arrow.texture == arrow_left_texture)
        {
            
            if (arrow.x <= 15)
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
            
            else if (archer.x >= 812 && arrow.x < 818 && arrow.y >= 214 && arrow.y <= 525)
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
          
            
            else if (arrow.y >= 628 && arrow.y <= 900 && arrow.x < 818)
                
            {
                arrow.hp = 0;
                freeRect(&arrow_rect);
            }
                
        }
        
        if (arrow.texture == arrow_down_texture)
        {
           if (arrow.y >= 700)
           {
               arrow.hp = 0;
               freeRect(&arrow_rect);
           }
            
        }
        
        
        
        
        
        
        
        
        SDL_RenderClear(ren);
        
        //MARK: - drawing lvl2
        
       
        
        
        
        map_rect = draw_texture(&ren, map_texture, 0, 0);
        archer_rect = draw_texture(&ren, archer.texture, archer.x, archer.y);
        
        if (arrow.hp && archer.hp)
            
        {
            freeRect(&arrow_rect);
            arrow_rect = draw_texture(&ren, arrow.texture, arrow.x, arrow.y);
        }
        
        
        SDL_RenderPresent(ren);
        
       
    }
    
    
   
    
    
    Mix_FreeChunk(sound_effect);
    Mix_FreeChunk(victory_effect);
    Mix_FreeChunk(death_effect);
    Mix_FreeChunk(collect_sound_effect);
    Mix_Quit();

    Mix_FreeMusic(bgm);
    
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    
    return 0;
}


int StartMenu(void)
{
    
    SDL_Window *window;
    SDL_Event ev;
    
    
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_TIMER | SDL_INIT_AUDIO) != 0) {
        fputs(SDL_GetError(), stderr);
        return 1;
    }
    if (TTF_Init() == -1)
    {
        fputs("couldn't load ttf",stdout);
        return 1;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
    {
        fputs(SDL_GetError(), stderr);
        return 1;
    }
    
    Mix_Music *bgm = Mix_LoadMUS("Adventure-320bit.mp3");
    Mix_Chunk *sound_effect = Mix_LoadWAV("arrow_sound_effect.mp3");
    Mix_Chunk *death_effect = Mix_LoadWAV("death_sound.mp3");
    Mix_Chunk *victory_effect = Mix_LoadWAV("victory.mp3");
    Mix_Chunk *collect_sound_effect = Mix_LoadWAV("collect_sound_effect.mp3");
    if (!(window = SDL_CreateWindow("Infinity stone", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DISPLAY_W, DISPLAY_H, SDL_WINDOW_SHOWN))) {
        fputs(SDL_GetError(), stderr);
        return 1;
    }
    
    if (!(ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        fputs(SDL_GetError(), stderr);
        return 1;
    }
    
    
    bool quit = false;
    while(!quit)
    {
        
        if(!Mix_PlayingMusic())
        {
            
            Mix_VolumeMusic(40);
            
            Mix_PlayMusic(bgm, -1);
        }
        
        while (SDL_PollEvent(&ev)) {
            
            switch (ev.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                    
                case SDL_KEYDOWN:
                    
                    do_key_down(&ev.key);
                    
                    break;
                    
                case SDL_KEYUP:
                    do_key_up(&ev.key);
                    break;
                    
              
                    break;
                    
                default:
                    break;
            }
            
            
        }
       
        TTF_Font *font = TTF_OpenFont("Sans.ttf", 24);
            if (!font) {
                printf("Error loading font: %s\n", TTF_GetError());
                return 1;
            }
        SDL_Color textColor = {255, 255, 255}; // White text color
        SDL_Surface *StartSurface = TTF_RenderText_Solid(font, "Start game F1", textColor);
        SDL_Texture *StartTexture = SDL_CreateTextureFromSurface(ren, StartSurface);
        
        
        SDL_Surface *quitSurface = TTF_RenderText_Solid(font, "Quit F2", textColor);
        SDL_Texture *quitTexture = SDL_CreateTextureFromSurface(ren, quitSurface);
        
        SDL_RenderClear(ren);
        SDL_Rect* startRect =  draw_texture(&ren, StartTexture, 1280/2 - 95, 720/2);
        
        SDL_Rect *  QuitRect = draw_texture(&ren, quitTexture, 1280/2 - 95 , 720/2 + 50);
        
        
        if (keys_archer.start)
        {
            return 1;
        }
        
       
       
        SDL_RenderPresent(ren);
        
       
    }
    
    
   
    
    
    Mix_FreeChunk(sound_effect);
    Mix_FreeChunk(victory_effect);
    Mix_FreeChunk(death_effect);
    Mix_FreeChunk(collect_sound_effect);
    Mix_Quit();

    Mix_FreeMusic(bgm);
    
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    
    return 0;
}


int playLevel3(void)
{
    return  0;
}
