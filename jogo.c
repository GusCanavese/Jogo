#include <stdio.h>
#include <string.h>
#include "raylib.h"


//coordenadas do quadrado
typedef struct{
    double tam_x;
    double tam_y;
    double posi_x;
    double posi_y;
} Quadrado;



//tamanho da janela e do quadrado
typedef struct{
    int largura;
    int altura;
    Quadrado quadrado;
} Jogo;


void InitGame(Jogo *g, Jogo *d){
    // tamanho janela 
    g->largura = 800;
    g->altura = 600;

    // Inicializar o tamanho e a posição do quadrado VERMELHO
    g->quadrado.tam_x = 30;
    g->quadrado.tam_y = 30;
    g->quadrado.posi_x = 400;
    g->quadrado.posi_y = 200;

    // Inicializar o tamanho e a posição do quadrado AZUL
    d->quadrado.tam_x = 30;
    d->quadrado.tam_y = 30;
    d->quadrado.posi_x = 500;
    d->quadrado.posi_y = 200;

}

int main()
{
    int gameStart = 1;
    char name[9];
    Jogo g, d, jogo = {800, 600};
    Rectangle r = (Rectangle){100, 100, 500, 20}; // criacao do retangulo aqui (tem que mandar desenhar ele la em baixo) (DA PRA FAZER AS COLISOES ASSIM)

    InitGame(&g, &d); //INICIANDO OS PERSONAGENS
    InitWindow(g.largura, g.altura, "Jogo");
    SetTargetFPS(60);

    while(gameStart == 1){
        if (gameStart == 1){
        BeginDrawing();
        ClearBackground(GRAY);
        DrawText("Bomberman", jogo.largura/2 - MeasureText("Bomberman", 40)/2, 50, 40, BLUE);
        DrawText("nICK:", jogo.largura/2 - MeasureText("Digite seu nome:", 20)/2, jogo.altura/2 - 50, 20, WHITE);
        DrawText(name, jogo.largura/2 - MeasureText(name, 40)/2, jogo.altura/2, 40, WHITE);

        if (gameStart == 1){
            DrawText("Press ENTER!", jogo.largura/2 - MeasureText("Press ENTER!", 20)/2, jogo.altura/2 + 50, 20, WHITE);
        }

        if (IsKeyPressed(KEY_BACKSPACE)){
        int length = strlen(name);

            if (length > 0){
                name[length - 1] = '\0';
            }
        } else {
            int key = GetKeyPressed();

            if (key != -1 && strlen(name) < 255){
                int length = strlen(name);
                name[length] = (char)key;
                name[length + 1] = '\0';
            }
                if (IsKeyPressed(KEY_ENTER)){
                    gameStart = 0;
                }
        }
    }
    EndDrawing();
}







    while (!WindowShouldClose())
    {
        //===============================================
        //MOVIMENTACAO QUADRADO AZUL
        //===============================================
        if (IsKeyDown(KEY_D))
        {
            d.quadrado.posi_x += 5;
            if (d.quadrado.posi_x > 800 - 30 || CheckCollisionRecs(r, (Rectangle){d.quadrado.posi_x, d.quadrado.posi_y, d.quadrado.tam_x, d.quadrado.tam_y}))
            {
                d.quadrado.posi_x -= 5;
            }
        }

        if (IsKeyDown(KEY_A))
        {
            d.quadrado.posi_x -= 5;
            if (d.quadrado.posi_x < 0 || CheckCollisionRecs(r, (Rectangle){d.quadrado.posi_x, d.quadrado.posi_y, d.quadrado.tam_x, d.quadrado.tam_y}))
            {
                d.quadrado.posi_x += 5;
            }
        }

        if (IsKeyDown(KEY_W))
        {
            d.quadrado.posi_y -= 5;
            if (d.quadrado.posi_y < 0 || CheckCollisionRecs(r, (Rectangle){d.quadrado.posi_x, d.quadrado.posi_y, d.quadrado.tam_x, d.quadrado.tam_y}))
            {
                d.quadrado.posi_y += 5;
            }
        }

        if (IsKeyDown(KEY_S))
        {
            d.quadrado.posi_y += 5;
            if (d.quadrado.posi_y > 400 - 30 || CheckCollisionRecs(r, (Rectangle){d.quadrado.posi_x, d.quadrado.posi_y, d.quadrado.tam_x, d.quadrado.tam_y}))
            {
                d.quadrado.posi_y -= 5;
            }
        }


        //===============================================
        //MOVIMENTACAO QUADRADO VERMELHO
        //===============================================
        if (IsKeyDown(KEY_RIGHT))
        {
            g.quadrado.posi_x += 5;
            if (g.quadrado.posi_x > 800 - 30 || CheckCollisionRecs(r, (Rectangle){g.quadrado.posi_x, g.quadrado.posi_y, g.quadrado.tam_x, g.quadrado.tam_y}))
            {
                g.quadrado.posi_x -= 5;
            }
        }

        if (IsKeyDown(KEY_LEFT))
        {
            g.quadrado.posi_x -= 5;
            if (g.quadrado.posi_x < 0 || CheckCollisionRecs(r, (Rectangle){g.quadrado.posi_x, g.quadrado.posi_y, g.quadrado.tam_x, g.quadrado.tam_y}))
            {
                g.quadrado.posi_x += 5;
            }
        }

        if (IsKeyDown(KEY_UP))
        {
            g.quadrado.posi_y -= 5;
            if (g.quadrado.posi_y < 0 || CheckCollisionRecs(r, (Rectangle){g.quadrado.posi_x, g.quadrado.posi_y, g.quadrado.tam_x, g.quadrado.tam_y}))
            {
                g.quadrado.posi_y += 5;
            }
        }

        if (IsKeyDown(KEY_DOWN))
        {
            g.quadrado.posi_y += 5;
            if (g.quadrado.posi_y > 400 - 30 || CheckCollisionRecs(r, (Rectangle){g.quadrado.posi_x, g.quadrado.posi_y, g.quadrado.tam_x, g.quadrado.tam_y}))
            {
                g.quadrado.posi_y -= 5;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(d.quadrado.posi_x, d.quadrado.posi_y, d.quadrado.tam_x, d.quadrado.tam_y, BLUE);
        DrawRectangle(g.quadrado.posi_x, g.quadrado.posi_y, g.quadrado.tam_x, g.quadrado.tam_y, RED);
        DrawRectangleRec(r, WHITE);
        EndDrawing();
    }
    CloseWindow();
}