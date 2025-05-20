#pragma once
#include <raylib.h>

class Ficha {
private:
    int fila;
    int columna;
    int jugador;
public:
    Ficha(int fila, int columna,int jugador);

    void dibujar(float tamanoCasilla);
    void moverA(int nuevaFila, int nuevaColumna);

    int getFila();
    int getColumna();
    int getJugador();
};
