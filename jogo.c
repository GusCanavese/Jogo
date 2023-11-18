#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define TAMANHO_ALTURA_BOMBA = 30


double tempo=0, tempoPassado=0, tempoInicio=0;

//mapa
typedef struct{
   Rectangle barreira[10];
   int numbarre;
   Color cor;
   int proxmap;
   int mapant;
   int imagemteste,png;
}Mapa;



typedef struct{
    Mapa atmap[3];
    Texture2D imagem;
    int altura;
    int largura;
}jogogeral;

typedef struct {
   int posi_x, posi_y, tamanho, temporizador;
} Bomba;


typedef struct {
   double tam_x;
   double tam_y;
   double posi_x;
   double posi_y;
   int qtdBomas;
   int dropedBomb;
   Bomba bomba;
} Heroi;

void persona (Heroi*g, Heroi *g2){
   g  -> posi_x  = 30;
   g  -> tam_y  = 30;
   g  -> posi_x = 330;
   g  -> posi_y = 200;
   g  -> qtdBomas = 4;
   g  -> bomba.tamanho =50;
   g  -> bomba.temporizador =3;
   g  -> dropedBomb=0;
   g2 -> tam_x  = 30;
   g2 -> tam_y  = 30;
   g2 -> posi_x = 400;
   g2 -> posi_y = 200;
   
}

void criaBomba(Heroi *p){
    DrawRectangle(p->bomba.posi_x, p->bomba.posi_y, 30, 30, BLACK);
}

void Explosao(Heroi *p){
    tempo = GetTime();
    tempoPassado = tempo-tempoInicio;
    if (tempoPassado > p->bomba.temporizador){
        DrawRectangle(p->bomba.posi_x, p->bomba.posi_y, (p->bomba.tamanho*2)+30, 30, RED);   
        DrawRectangle(p->bomba.posi_x, p->bomba.posi_y, 30, (p->bomba.tamanho*2)+30, RED);
        DrawRectangle(p->bomba.posi_x, p->bomba.posi_y, (p->bomba.tamanho*2)-30, 30, RED);   
        DrawRectangle(p->bomba.posi_x, p->bomba.posi_y, 30, (p->bomba.tamanho*2)-30, RED);
        p->qtdBomas--;
    }
}

void UpdateGame(Heroi *p){
    if(IsKeyDown(KEY_SPACE) && p->qtdBomas>0){
       tempo=GetTime();
       p->dropedBomb++;
       p->qtdBomas--;
       p->bomba.posi_x=p->posi_x;
       p->bomba.posi_y=p->posi_y;
   }

   if(p->posi_x<0) p->posi_x=0;
   if(p->posi_y<0) p->posi_y=0;
   if(p->posi_x>800 - 30) p->posi_x=800 - 30;
   if(p->posi_y>600 - 30) p->posi_y=600 - 30;
}


void IniciaJogo (Heroi *p){
   ClearBackground(LIGHTGRAY);
   DrawRectangle(p->posi_x, p->posi_y, 30, 30, GREEN );
   if(p->dropedBomb>0){
       criaBomba(&(*p));
       Explosao(&(*p));
   }
}



void mapa0(jogogeral *u){
   u->atmap[0].numbarre=1;
   u->atmap[0].barreira[0]=(Rectangle){20, 40, 50, 90};
}

void desmap(jogogeral *u){
   for(int i=0; i<u->atmap[0].numbarre; i++){
       DrawRectangleRec(u->atmap[0].barreira[i], BLACK);
   }
}





int main(){
   int comco= -1;
//    int pt2= -1;
//    char jogador1[12];
//    char jogador2[12];
   Heroi g, g2;
   jogogeral geral;
   geral.altura=600;
   geral.largura=800;
   Rectangle r = (Rectangle){100, 100, 500, 20};
   Rectangle opcsingle = (Rectangle){geral.largura/3, geral.altura/3, geral.largura/3, 50};
   Rectangle opcmult = (Rectangle){geral.largura/3, geral.altura/3 + 70, geral.largura/3, 50};
   Vector2 mousePosition = {0};
   geral.imagem = LoadTexture("imagemteste.png");
   persona(&g, &g2);
   InitWindow (geral.largura, geral.altura, "Jogo");
   SetTargetFPS (60);
   mapa0(&geral);
   while(comco == -1){
       if(comco == -1){
           mousePosition = GetMousePosition();
           Color corRetopc1 = BLACK;
           Color corRetopc2 = BLACK;
           int letraText1 = 20;
           int letraText2 = 20;
           BeginDrawing();
           ClearBackground(DARKBLUE);
           if(CheckCollisionPointRec( mousePosition, opcsingle)){
               letraText1 += 15;
               if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                   corRetopc1 = WHITE;
                   comco = 1;
               }
           };
           if(CheckCollisionPointRec(mousePosition, opcmult)){
               letraText2 += 15;
               if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                   corRetopc2 = WHITE;
                   comco = 2;
               }
           };
           DrawText("BOMBERMAN", geral.largura/4+30, geral.altura/7, 50, WHITE);
           DrawRectangle(geral.largura/3, geral.altura/3, geral.largura/3, 50, corRetopc1);
           DrawText("SinglePlayer", geral.largura/3+30, geral.altura/3+10, letraText1, DARKBLUE);
           DrawRectangle(geral.largura/3, geral.altura/3+70, geral.largura/3, 50, corRetopc2);
           DrawText("MultiPlayer", geral.largura/3+30, geral.altura/3+80, letraText2, DARKBLUE);
           EndDrawing();
       }
   }
    
    while (!WindowShouldClose()){
        UpdateGame(&g);
        IniciaJogo(&g);

//começo movimentação
       if(IsKeyDown(KEY_RIGHT)){
           g.posi_x += 10;
           if(g.posi_x > 800-30 || CheckCollisionRecs(r, (Rectangle){g.posi_x, g.posi_y, g.tam_x, g.tam_y})) {
           g.posi_x -= 10;
           }
       }

       if( IsKeyDown (KEY_LEFT)){
           g.posi_x -=10;
           if(g.posi_x < 0 || CheckCollisionRecs(r, (Rectangle){g.posi_x, g.posi_y, g.tam_x, g.tam_y})){ 
               g.posi_x += 10;
           }      
       }

       if( IsKeyDown (KEY_UP)){
           g.posi_y -= 10;
           if(g.posi_y < 0 || CheckCollisionRecs(r, (Rectangle){g.posi_x, g.posi_y, g.tam_x, g.tam_y})) {
           g.posi_y += 10;
           }
       }

       if( IsKeyDown (KEY_DOWN)){
           g.posi_y += 10;
           if(g.posi_y > 600-30 || CheckCollisionRecs(r, (Rectangle){g.posi_x, g.posi_y, g.tam_x, g.tam_y})) {
           g.posi_y -= 10;
           }
       }

       if(IsKeyDown (KEY_D)){
           g2.posi_x += 10;
           if(g2.posi_x > 800-30 || CheckCollisionRecs(r, (Rectangle){g2.posi_x, g2.posi_y, g2.tam_x, g2.tam_y})) {
           g2.posi_x -= 10;
           }
       }

       if( IsKeyDown (KEY_A)){
           g2.posi_x -=10;
           if(g2.posi_x < 0 || CheckCollisionRecs(r, (Rectangle){g2.posi_x, g2.posi_y, g2.tam_x, g2.tam_y})){
               g2.posi_x += 10;
           }      
       }

       if( IsKeyDown (KEY_W)){
           g2.posi_y -= 10;
           if(g2.posi_y < 0 || CheckCollisionRecs(r, (Rectangle){g2.posi_x, g2.posi_y, g2.tam_x, g2.tam_y})) {
           g2.posi_y += 10;
           }
       }

       if( IsKeyDown (KEY_S)){
           g2.posi_y += 10;
           if(g2.posi_y > 600-30 || CheckCollisionRecs(r, (Rectangle){g2.posi_x, g2.posi_y, g2.tam_x, g2.tam_y})) {
           g2.posi_y -= 10;
           }
       }
//fim movimentação

   BeginDrawing () ;
   ClearBackground (WHITE);
   DrawRectangle (g.posi_x, g.posi_y, g.tam_x, g.tam_y, BLUE );
   DrawRectangle (g2.posi_x, g2.posi_y, g2.tam_x, g2.tam_y, BLACK );
   DrawRectangleRec(r, RED);
   desmap(&geral);
   DrawTexture(geral.imagem, 0 , 0, BLUE);
   EndDrawing ();
   }
   UnloadTexture(geral.imagem);
   CloseWindow () ;
}