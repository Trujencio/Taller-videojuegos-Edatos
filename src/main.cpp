#include <raylib.h>
#include "Tablero.h"

int main() {
    const int anchoPantalla = 640;
    const int altoPantalla = 640;
    const float tamanoCasilla = anchoPantalla / 8.0f;

    InitWindow(anchoPantalla, altoPantalla, "Damas con poderes especiales - Test");

    Tablero tablero;
    tablero.iniciarTablero();
    tablero.generarMatrizMov();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        tablero.dibujar(tamanoCasilla);

        EndDrawing();

        // Manejar clicks del mouse para mover fichas
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();
            tablero.manejarClick(mouseX, mouseY, tamanoCasilla);
        }
    }

    CloseWindow();
    return 0;
}
