#include <raylib.h>
#include "Juego.h"

int main() {
    const int anchoPantalla = 640;
    const int altoPantalla = 640;
    const float tamanoCasilla = anchoPantalla / 8.0f;

    InitWindow(anchoPantalla, altoPantalla, "Damas con poderes especiales - Test");

    Juego juego(tamanoCasilla);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        

        EndDrawing();

        
    }

    CloseWindow();
    return 0;
}
