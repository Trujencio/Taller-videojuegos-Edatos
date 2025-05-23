#pragma once
#include "Ficha.h"

class Nodo{

    public:
        Ficha* ficha;
        Nodo* siguiente;
        Nodo* nodoFinal;
        Nodo(Ficha* ficha);
        ~Nodo(){};
        static Nodo* agregarFicha(Nodo* head, Ficha* nuevaFicha);
        Ficha* elegirFicha(Nodo* head);
        Nodo* eliminarNodo(Nodo* head,Ficha* fichaEliminar);
        static int numeroAleatorio(int min, int max);
};