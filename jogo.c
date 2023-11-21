#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#define TAMANHO_ALTURA_BOMBA = 30


double tempo1=0, tempoPassado1=0, tempoInicio1=0;
double tempo2=0, tempoPassado2=0, tempoInicio2=0;

//mapa
typedef struct{
   Rectangle barreira[40];
   int numbarre;
   Color cor;
   int proxmap;
   int mapant;
   int imagemteste;
}Mapa;

typedef struct{
    Mapa atmap[3];
    Texture2D imagem;
    int altura;
    int largura;
}jogogeral;

typedef struct {
   int posi_x, posi_y, tamanho, temporizador;
}Bomba;


typedef struct {
   double tam_x;
   double tam_y;
   double posi_x;
   double posi_y;
   int qtdBombas;
   int dropedBomb;
   bool contador;
   Bomba bomba;
}Heroi;

Rectangle retangulo_heroi(Heroi* g) {
    Rectangle r= {g->posi_x, g->posi_y, g->tam_x, g->tam_y };
    return r;
}

void persona (Heroi*g, Heroi *g2){
   g  -> posi_x             = 30;
   g  -> tam_y              = 30;
   g  -> tam_x              = 30;
   g  -> posi_x             = 330;
   g  -> posi_y             = 210;
   g  -> qtdBombas          = 4;
   g  -> bomba.tamanho      = 30;
   g  -> bomba.temporizador = 3;
   g  -> dropedBomb         = 0;
   g  -> contador           = false;
   g2 -> tam_x              = 30;
   g2 -> tam_y              = 30;
   g2 -> posi_x             = 400;
   g2 -> posi_y             = 210;
   g2 -> qtdBombas         = 4;
   g2 -> bomba.tamanho     = 30;
   g2 -> bomba.temporizador= 3;
   g2 -> dropedBomb        = 0;
   g2 -> contador          = false;
}

void criaBomba(Heroi *p){
    DrawRectangle(p->bomba.posi_x, p->bomba.posi_y, 30, 30, BLACK);
}

void Explosao1(Heroi *p){
    tempo1 = GetTime();
    tempoPassado1 = tempo1-tempoInicio1;
    if (tempoPassado1 > p->bomba.temporizador){
        DrawRectangle(p->bomba.posi_x - 60, p->bomba.posi_y, (p->bomba.tamanho*2)+90, 30, RED);   
        DrawRectangle(p->bomba.posi_x, p->bomba.posi_y - 60, 30, (p->bomba.tamanho*2)+90, RED);
        if(tempoPassado1 > p->bomba.temporizador+1){
            p->dropedBomb--;
            p->qtdBombas++;
        }
    }
}

void Explosao2(Heroi *p){
    tempo2 = GetTime();
    tempoPassado2 = tempo2-tempoInicio2;
    if (tempoPassado2 > p->bomba.temporizador){
        DrawRectangle(p->bomba.posi_x - 60, p->bomba.posi_y, (p->bomba.tamanho*2)+90, 30, RED);   
        DrawRectangle(p->bomba.posi_x, p->bomba.posi_y - 60, 30, (p->bomba.tamanho*2)+90, RED);
        if(tempoPassado2 > p->bomba.temporizador+1){
            p->dropedBomb--;
            p->qtdBombas++;
        }
    }
}


void UpdateGame(Heroi *p, Heroi *g){
    if(IsKeyDown(KEY_SPACE) && p->qtdBombas>0){
        tempoInicio1=GetTime();
        p->dropedBomb++;
        p->qtdBombas--;
        p->bomba.posi_x=p->posi_x;
        p->bomba.posi_y=p->posi_y;
    }
    if(p->posi_x<0) p->posi_x=0;
    if(p->posi_y<0) p->posi_y=0;
    if(p->posi_x>800 - 30) p->posi_x=800 - 30;
    if(p->posi_y>600 - 30) p->posi_y=600 - 30;

    if(IsKeyDown(KEY_RIGHT_CONTROL) && g->qtdBombas>0){
        tempoInicio2=GetTime();
        g->dropedBomb++;
        g->qtdBombas--;
        g->bomba.posi_x=g->posi_x;
        g->bomba.posi_y=g->posi_y;
    }
    if(g->posi_x<0) g->posi_x=0;
    if(g->posi_y<0) g->posi_y=0;
    if(g->posi_x>800 - 30) g->posi_x=800 - 30;
    if(g->posi_y>600 - 30) g->posi_y=600 - 30;
}










void IniciaJogo1 (Heroi *p){
    ClearBackground(LIGHTGRAY);
    DrawRectangleRec(retangulo_heroi(p), PURPLE);
    if(p->dropedBomb>0){
        criaBomba(&(*p));
        Explosao1(&(*p));
    }
}


void IniciaJogo2 (Heroi *g){
    ClearBackground(LIGHTGRAY);
    DrawRectangleRec(retangulo_heroi(g), WHITE);
    if(g->dropedBomb>0){
        criaBomba(&(*g));
        Explosao2(&(*g));
    }
}



void mapa0(jogogeral *u){
   u->atmap[0].numbarre=36;
   for(int i=0; i<6; i++){
    for(int j=0; j<6; j++){
        u->atmap[0].barreira[i*6+j]=(Rectangle){(120*i)+50,(120*j)+50,30,30};
    }
   }
}

void desmap(jogogeral *u, Heroi g, Heroi g2){
    for(int i=0; i<4; i++){
        DrawRectangleRec(u->atmap[0].barreira[i], BLACK);
    }for(int j=4; j<u->atmap[0].numbarre; j++){
        for(int k=4; k<u->atmap[0].numbarre; k++)
        DrawRectangleRec(u->atmap[0].barreira[k], BLACK);
    }
}

/*void bordamapa(jogogeral *u){
    u->atmap[0].barreira[0]=(Rectangle){0, 0, 800, 10}; //cima
   u->atmap[0].barreira[1]=(Rectangle){0, 595, 800, 10}; //baixo
   u->atmap[0].barreira[2]=(Rectangle){0, 0, 10, 600}; //esq
   u->atmap[0].barreira[3]=(Rectangle){795, 0, 10, 600}; //dir
}

void desborda(jogogeral *u, Heroi g, Heroi g2){
    for(int i=0; i<u->atmap[0].numbarre; i++){
       DrawRectangleRec(u->atmap[0].barreira[i], BLACK);
   }
}*/

int colisaoBarreira(jogogeral *u, Rectangle g){
    printf("rect: %lf %lf %lf %lf\n", g.x, g.y, g.width, g.height);
    for(int i=0; i< u->atmap[0].numbarre; i++){
        Rectangle b = u->atmap[0].barreira[i];
            printf("barreira[%d]: %lf %lf %lf %lf\n", i, b.x, b.y, b.width, b.height);
            if(CheckCollisionRecs(u->atmap[0].barreira[i], g)) {
                printf("Colidiu com %d\n", i);
                return 1;
            }
            
       }
    return 0;
}



int main(){
    int comco= -1;
    Heroi g, g2;
    jogogeral geral;
    geral.altura=600;
    geral.largura=800;
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
                    comco = 1;
                }
            };
            if(CheckCollisionPointRec(mousePosition, opcmult)){
                letraText2 += 15;
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
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
        UpdateGame(&g, &g2);
        IniciaJogo1(&g);
        IniciaJogo2(&g2);

        //começo movimentação
        if(IsKeyDown(KEY_RIGHT)){
            g.posi_x += 10;
            if(colisaoBarreira(&geral, retangulo_heroi(&g))) {
                g.posi_x -= 10;
            }
        }

        if( IsKeyDown (KEY_LEFT)){
            g.posi_x -=10;
            if(colisaoBarreira(&geral, retangulo_heroi(&g))){ 
                g.posi_x += 10;
            }      
        }

        if( IsKeyDown (KEY_UP)){
            g.posi_y -= 10;
            if(colisaoBarreira(&geral, retangulo_heroi(&g))) {
                g.posi_y += 10;
            }
        }

        if( IsKeyDown (KEY_DOWN)){
            g.posi_y += 10;
            if(colisaoBarreira(&geral, retangulo_heroi(&g))) {
                g.posi_y -= 10;
            }
        }

        if(IsKeyDown (KEY_D)){
            g2.posi_x += 10;
            if(colisaoBarreira(&geral, retangulo_heroi(&g2))) {
                g2.posi_x -= 10;
            }
        }

        if( IsKeyDown (KEY_A)){
            g2.posi_x -=10;
            if(colisaoBarreira(&geral, retangulo_heroi(&g2))){
                g2.posi_x += 10;
            }      
        }

        if( IsKeyDown (KEY_W)){
            g2.posi_y -= 10;
            if(colisaoBarreira(&geral, retangulo_heroi(&g2))) {
                g2.posi_y += 10;
            }
        }

        if( IsKeyDown (KEY_S)){
            g2.posi_y += 10;
            if(colisaoBarreira(&geral, retangulo_heroi(&g2))) {
                g2.posi_y -= 10;
            }
        }

        BeginDrawing () ;
        ClearBackground (DARKGREEN);
        desmap(&geral, g, g2);
        DrawTexture(geral.imagem, 0 , 0, RED);
        EndDrawing();
    }
    UnloadTexture(geral.imagem);
    CloseWindow();
    }