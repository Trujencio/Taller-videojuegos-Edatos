#include "Juego.h"

Juego::Juego(float tamanoCasilla) {
    tablero.iniciarTablero();
    tablero.generarMatrizMov();
}

void Juego::dibujarTablero() {
    tablero.dibujar(tamanoCasilla);
}

bool Juego::recibirClick(int mouseX, int mouseY) {
    int fila = mouseY / tamanoCasilla;
    int columna = mouseX / tamanoCasilla;

    // Aquí llamamos a la función en Tablero que maneja la lógica con fila y columna
    return tablero.manejarClick(fila, columna);
}

