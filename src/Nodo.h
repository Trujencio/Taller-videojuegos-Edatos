#pragma once
#include "Ficha.h"

class Nodo{

    public:
        Ficha* ficha;
        Nodo* siguiente;
        Nodo* nodoFinal;
        int fichasVivas = 12;
        Nodo(Ficha* ficha);
        ~Nodo(){};
        static Nodo* agregarFicha(Nodo* head, Ficha* nuevaFicha);
        Ficha* elegirFicha(Nodo* head);
        Nodo* eliminarNodo(Nodo* head,Ficha* fichaEliminar); 
};