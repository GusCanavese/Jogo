#include <stdio.h>
#include <string.h>
#include <raylib.h>

//coordenadas do quadrado
typedef struct{
    double tam_x;
    double tam_y;
    double posi_x;
    double posi_y;
} Quadrado;

typedef struct{
    int altura;
    int largura;
}Botao;

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
    int gameStart = -1;
    char nameJogador1[9];
    char nameJogador2[9];
    Jogo g, d, jogo = {800, 600};
    Rectangle r = (Rectangle){100, 100, 500, 20}; // criacao do retangulo aqui (tem que mandar desenhar ele la em baixo) (DA PRA FAZER AS COLISOES ASSIM)
    Rectangle botaoSingleplayer = (Rectangle){jogo.largura/3, jogo.altura/3, jogo.largura/3, 50};
    Rectangle botaoMultiplayer = (Rectangle){jogo.largura/3, jogo.altura/3 + 70, jogo.largura/3, 50};
    Vector2 mousePosition = {0};
    


    InitGame(&g, &d); //INICIANDO OS PERSONAGENS
    InitWindow(g.largura, g.altura, "Jogo");
    SetTargetFPS(60);



    // tela de menu
    while (gameStart == -1){
            if(gameStart == -1){
            mousePosition = GetMousePosition();
            Color corRetangulo1 = GRAY;
            Color corRetangulo2 = WHITE;
            BeginDrawing();
            ClearBackground(BLUE);
            if(CheckCollisionPointRec(mousePosition, botaoSingleplayer)){
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    corRetangulo1 = PINK;
                    gameStart = 1;
                }
            };

            if(CheckCollisionPointRec(mousePosition, botaoMultiplayer)){
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    corRetangulo2 = BLACK;
                    gameStart = 2;
                }
            };
            DrawRectangle(jogo.largura/3, jogo.altura/3, jogo.largura/3, 50, corRetangulo1);
            DrawText("SinglePlayer", jogo.largura/3, jogo.altura/3, 20, PINK);
            DrawRectangle(jogo.largura/3, jogo.altura/3 + 70, jogo.largura/3, 50, corRetangulo2);
            DrawText("MultiPlayer", jogo.largura/3, jogo.altura/3 + 70, 20, BLACK);
            EndDrawing();
        }
    }


        







    while (!WindowShouldClose()){



        // tela para digitar o nome de um jogador
        while(gameStart == 1){
            if (gameStart == 1){
                BeginDrawing();
                ClearBackground(GRAY);
                DrawText("Bomberman", jogo.largura/2 - MeasureText("Bomberman", 40)/2, 50, 40, BLUE);
                DrawText("Nick:", jogo.largura/2 - MeasureText("Digite seu nome:", 20)/2, jogo.altura/2 - 50, 20, WHITE);
                DrawText(nameJogador1, jogo.largura/2 - MeasureText(nameJogador1, 40)/2, jogo.altura/2, 40, WHITE);
                DrawText("Press ENTER!", jogo.largura/2 - MeasureText("Press ENTER!", 20)/2, jogo.altura/2 + 50, 20, WHITE);
                if (IsKeyPressed(KEY_BACKSPACE)){
                int length = strlen(nameJogador1);
                    if (length > 0){
                        nameJogador1[length - 1] = '\0';
                    }
                } else {
                    int key = GetKeyPressed();
                    if (key != -1 && strlen(nameJogador1) < 255){
                        int length = strlen(nameJogador1);
                        nameJogador1[length] = (char)key;
                        nameJogador1[length + 1] = '\0';
                    }
                    if (IsKeyPressed(KEY_ENTER)){
                        gameStart = 0;
                    }
                }
            }
            EndDrawing();
        }





        // tela para digitar o nome de dois jogadores
        while(gameStart == 2){
            if (gameStart == 2){
                BeginDrawing();
                ClearBackground(GRAY);

                DrawText("Bomberman", jogo.largura/2 - MeasureText("Bomberman", 40)/2, 50, 40, BLUE);
                DrawText("Nick Jogador1:", jogo.largura/4 - MeasureText("Digite nome jogador1:", 20)/2, jogo.altura/2, 20, WHITE);
                DrawText(nameJogador1, jogo.largura/4 - MeasureText(nameJogador1, 40)/2 - 30, jogo.altura/2 + 30, 40, WHITE);
                if (IsKeyPressed(KEY_BACKSPACE)){
                int length = strlen(nameJogador1);
                    if (length > 0){
                        nameJogador1[length - 1] = '\0';
                    }
                } else {
                    int key1 = GetKeyPressed();
                    if (key1 != -1 && strlen(nameJogador1) < 255){
                        int length = strlen(nameJogador1);
                        nameJogador1[length] = (char)key1;
                        nameJogador1[length + 1] = '\0';
                    }
                    if (IsKeyPressed(KEY_ENTER)){
                        // o jogo nao pode iniciar aqui 
                    }
                }

                DrawText("Bomberman", jogo.largura/2 - MeasureText("Bomberman", 40)/2, 50, 40, BLUE);
                DrawText("Nick Jogador2:", jogo.largura/2 + MeasureText("Digite nome jogador2:", 20) - 50, jogo.altura/2, 20, WHITE);
                DrawText(nameJogador2, jogo.largura/2 - MeasureText(nameJogador2, 40) - 50, jogo.altura/2, 40, WHITE);

                if (IsKeyPressed(KEY_BACKSPACE)){
                int length = strlen(nameJogador2);
                    if (length > 0){
                        nameJogador2[length - 1] = '\0';
                    }
                } else {
                    int key2 = GetKeyPressed();
                    if (key2 != -1 && strlen(nameJogador2) < 255){
                        int length = strlen(nameJogador2);
                        nameJogador2[length] = (char)key2;
                        nameJogador2[length + 1] = '\0';
                    }
                    if (IsKeyPressed(KEY_ENTER)){
                        gameStart = 0;
                    }
                }





                
                DrawText("Press ENTER!", jogo.largura/2 - MeasureText("Press ENTER!", 20)/2, jogo.altura/4, 20, WHITE);
            }
            EndDrawing();
        }


        
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