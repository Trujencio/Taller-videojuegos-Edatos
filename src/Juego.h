#pragma once
#include "Tablero.h"

class Juego {
    private:
        Tablero tablero;
        int turnoJugador;              // 1 = jugador, 2 = CPU
        float tamanoCasilla;

    public:
        Juego(float tamanoCasilla);
        void dibujarTablero();
        bool recibirClick(int mouseX, int mouseY);
        void actualizar();
        bool turnoCPU();
};
