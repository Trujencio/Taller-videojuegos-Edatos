#pragma once
#include <raylib.h>
#include <cmath>

class Ficha {
    private:
        int fila;
        int columna;
        int jugador;
        bool esDama = false;
    
    public:
        Ficha(int fila, int columna,int jugador);

        void dibujar(float tamanoCasilla);
        void moverA(int nuevaFila, int nuevaColumna);
        bool puedeMoverA(int filaDestino);
        int getFila();
        int getColumna();
        int getJugador();
        bool getEsDama();
};
