#include "Ficha.h"

Ficha::Ficha(int fila, int columna,int jugador){
    this -> fila = fila;
    this -> columna = columna;
    this -> jugador = jugador;
}

void Ficha::dibujar(float tamanoCasilla) {
    float x = columna * tamanoCasilla + tamanoCasilla / 2;
    float y = fila * tamanoCasilla + tamanoCasilla / 2;
    float radio = tamanoCasilla * 0.4f;

    Color color;
    
    if (this -> jugador == 1){color = RED;}

    else{color = BLACK;}
    
    DrawCircle(x, y, radio, color);
}

bool Ficha::puedeMoverA(int filaDestino) {
    if (this -> getEsDama()) return true;
    if (jugador == 1) return filaDestino < fila;
    if (jugador == 2) return filaDestino > fila; 
    return false;
}

void Ficha::moverA(int nuevaFila, int nuevaColumna) {
    fila = nuevaFila;
    columna = nuevaColumna;
}

int Ficha::getFila(){return fila;}
int Ficha::getColumna(){ return columna; }
int Ficha::getJugador(){ return jugador; }
bool Ficha::getEsDama(){return esDama;}

