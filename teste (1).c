#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800
#define HERO_BOMB_HEIGHT_WIDTH 30

double tempoAtual=0, tempoDecorrido=0, tempoInicial=0;

typedef struct{
   int bomb_x, bomb_y, raio, timer;
}Bomb;

typedef struct{
   int pos_x, pos_y, deadOrAlive, qtdBombas, dropedBomb;
   bool counting;
   Bomb bomba;
}Player;

void initPlayer(Player *p){
   p->pos_x=0;
   p->pos_y=0;
   p->deadOrAlive=1;
   p->qtdBombas=1;
   p->bomba.raio=50;
   p->bomba.timer=3;
   p->dropedBomb=0;
   p->counting=false;
}

void drawBomb(Player *p){
   DrawRectangle(p->bomba.bomb_x, p->bomba.bomb_y, 
   HERO_BOMB_HEIGHT_WIDTH, HERO_BOMB_HEIGHT_WIDTH, BLACK );
}

void drawExplosion(Player *p){
    tempoAtual=GetTime();
    tempoDecorrido=tempoAtual-tempoInicial;
    if(tempoDecorrido > p->bomba.timer){
        DrawRectangle(p->bomba.bomb_x-p->bomba.raio, p->bomba.bomb_y,
        p->bomba.raio*2+HERO_BOMB_HEIGHT_WIDTH, HERO_BOMB_HEIGHT_WIDTH, RED );
        DrawRectangle(p->bomba.bomb_x, p->bomba.bomb_y-p->bomba.raio,
        HERO_BOMB_HEIGHT_WIDTH, p->bomba.raio*2+HERO_BOMB_HEIGHT_WIDTH, RED);
        if(tempoDecorrido > p->bomba.timer+1){
            p->dropedBomb--;
            p->qtdBombas++;
        }
    }
}

void UpdateGame(Player *p){

   if(IsKeyDown(KEY_SPACE) && p->qtdBombas>0){
       tempoInicial=GetTime();
       p->dropedBomb++;
       p->qtdBombas--;
       p->bomba.bomb_x=p->pos_x;
       p->bomba.bomb_y=p->pos_y;
   }

   if(p->pos_x<0) p->pos_x=0;
   if(p->pos_y<0) p->pos_y=0;
   if(p->pos_x>SCREEN_WIDTH-HERO_BOMB_HEIGHT_WIDTH) p->pos_x=SCREEN_WIDTH-HERO_BOMB_HEIGHT_WIDTH;
   if(p->pos_y>SCREEN_HEIGHT-HERO_BOMB_HEIGHT_WIDTH) p->pos_y=SCREEN_HEIGHT-HERO_BOMB_HEIGHT_WIDTH;
}

void DrawGame (Player *p){
   BeginDrawing () ;
   ClearBackground(LIGHTGRAY);
   DrawRectangle(p->pos_x, p->pos_y, HERO_BOMB_HEIGHT_WIDTH, HERO_BOMB_HEIGHT_WIDTH, GREEN );
   if(p->dropedBomb>0){
       drawBomb(&(*p));
       drawExplosion(&(*p));
   }
   EndDrawing () ;
}

int main () {
   Player p;
   initPlayer(&p);
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, " FUNCIONA PELO AMOR DE DEUS! ");
   SetTargetFPS(60);
   while(!WindowShouldClose()){
      UpdateGame(&p);
      DrawGame(&p);
   }
   CloseWindow() ;
}