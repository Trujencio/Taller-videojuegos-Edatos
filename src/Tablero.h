#pragma once
#include <raylib.h>
#include "Ficha.h"
#include "Nodo.h"

class Tablero {
    
    public:
        Ficha* casillas[8][8];
        Ficha* fichaSeleccionada = nullptr;
        int movPosible[8][8];
        int turnoJugador = 2;
        Nodo* listaFichasIA = nullptr;
                
        Tablero();
        ~Tablero();
        
        void iniciarTablero();
        void dibujar(float tamanoCasilla);
        void colocarFicha(int fila, int columna,int jugador);
        void eliminarFicha(int fila, int columna);
        void comerFicha(Ficha* atacante, Ficha* comida, int filaDestino, int colDestino);
        void manejarClick(int mouseX, int mouseY, float tamanoCasilla);
        void generarMatrizMov();
        void jugarCPU();
        bool validarMovimiento(int filaDestino, int colDestino);
        Ficha* obtenerFicha(int fila, int columna);
    };
