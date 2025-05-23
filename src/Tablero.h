#pragma once
#include <raylib.h>
#include "Ficha.h"
#include "Nodo.h"
#include <cmath>

class Tablero {
    
    public:
        Ficha* casillas[8][8];
        Ficha* fichaSeleccionada = nullptr;
        int movPosible[8][8];
        
        Tablero();
        ~Tablero();
        
        void iniciarTablero();
        void dibujar(float tamanoCasilla);
        void colocarFicha(int fila, int columna,int jugador);
        bool manejarClick(int mouseX, int mouseY);
        void generarMatrizMov();

        bool moverFicha(Ficha* ficha, int filaDestino, int colDestino);
        bool validarMovimiento(Ficha* ficha, int filaDestino, int colDestino);
        Ficha* obtenerFicha(int fila, int columna);
    };
