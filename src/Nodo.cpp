#include "Nodo.h"
#include <random>

Nodo::Nodo(Ficha* ficha){
    this -> ficha = ficha;
    this -> siguiente = nullptr;
}

Ficha* Nodo::elegirFicha(Nodo* head){
    int NodoAElegir = numeroAleatorio(1,this -> fichasVivas);
    int indiceNodo = 1;
    Nodo* nodoAux = head;
    
    while (indiceNodo != NodoAElegir || nodoAux != nullptr){
        nodoAux = nodoAux -> siguiente;
    }
    return nodoAux -> ficha;
}

Nodo* Nodo::eliminarNodo(Nodo* head,Ficha* fichaEliminada){
    if (head == nullptr || fichaEliminada == nullptr){return nullptr;}

    Nodo* nodoEliminar = head;
    if (fichaEliminada == head -> ficha){
        head = head -> siguiente;
        delete nodoEliminar;
        this -> fichasVivas = fichasVivas - 1;
        return head;
    }
    
    Nodo* nodoPrevio = head;
    Nodo* nodoActual = head -> siguiente;
    
    while (nodoActual != nullptr && nodoActual -> ficha != fichaEliminada){
        nodoPrevio = nodoActual;
        nodoActual = nodoActual -> siguiente;
    }
    
    if (nodoActual != nullptr){
        nodoEliminar = nodoActual;
        nodoPrevio -> siguiente = nodoActual -> siguiente;
        delete nodoEliminar;
        this -> fichasVivas = fichasVivas - 1;
    }
    
    return head;
   
}


// Generar un número entero entre min y max (ambos incluidos)
int numeroAleatorio(int min, int max) {
    static std::random_device rd;   // fuente de entropía (solo una vez)
    static std::mt19937 gen(rd());  // generador con semilla
    std::uniform_int_distribution<> distrib(min, max); // distribución uniforme
    return distrib(gen);
}
