#include "Tablero.h"
#include <cstdlib>

Tablero::Tablero() {
    for (int fila = 0; fila < 8; ++fila)
        for (int col = 0; col < 8; ++col)
            casillas[fila][col] = nullptr;

    fichaSeleccionada = nullptr;
}

Tablero::~Tablero() {
    for (int fila = 0; fila < 8; ++fila) {
        for (int col = 0; col < 8; ++col) {
            delete casillas[fila][col];
        }
    }
}

bool Tablero::validarMovimiento(int filaDestino,int colDestino){
    if (movPosible[filaDestino][colDestino] == 1){return true;}
    return false;
}

void Tablero::dibujar(float tamanoCasilla) {
    for (int fila = 0; fila < 8; ++fila) {
        for (int col = 0; col < 8; ++col) {
            Color colorCasilla = ((fila + col) % 2 == 0) ? LIGHTGRAY : DARKGRAY;
            DrawRectangle(col * tamanoCasilla, fila * tamanoCasilla, tamanoCasilla, tamanoCasilla, colorCasilla);

            if (casillas[fila][col] != nullptr)
                casillas[fila][col]->dibujar(tamanoCasilla);
        }
    }

    if (fichaSeleccionada != nullptr) {
        int fila = fichaSeleccionada->getFila();
        int col = fichaSeleccionada->getColumna();
        DrawRectangleLinesEx(
            { (float)(col * tamanoCasilla), (float)(fila * tamanoCasilla), tamanoCasilla, tamanoCasilla },
            3.0f,
            YELLOW
        );
    }
}

void Tablero::manejarClick(int mouseX, int mouseY, float tamanoCasilla) {
    int columna = mouseX / tamanoCasilla;
    int fila = mouseY / tamanoCasilla;

    if (fila < 0 || fila >= 8 || columna < 0 || columna >= 8)
        return;

    // Si no es tu turno (jugador 2), no hacer nada
    if (turnoJugador != 2) {
        return;
    }

    Ficha* fichaClickeada = casillas[fila][columna];

    if (fichaSeleccionada == nullptr) {
        // Solo puedes seleccionar fichas del jugador 2 (tú)
        if (fichaClickeada != nullptr && fichaClickeada->getJugador() == 2) {
            fichaSeleccionada = fichaClickeada;

            // (Opcional) Aquí podrías generar la matriz de movimientos válidos si quisieras expandir la lógica más adelante
            // generarMovimientosPosibles(fichaSeleccionada);
        }
    } else {
        // Si clickeamos una casilla vacía
        if (fichaClickeada == nullptr) {
            // Verificar que el movimiento está permitido según movPosible
            if (!validarMovimiento(fila, columna)) {
                fichaSeleccionada = nullptr;
                return;
            }

            int filaOrigen = fichaSeleccionada->getFila();
            int colOrigen = fichaSeleccionada->getColumna();

            // Validar que jugador 2 solo pueda mover hacia arriba (filaDestino < filaOrigen)
            if (fila >= filaOrigen) {
                fichaSeleccionada = nullptr;
                return;
            }

            if (abs(fila - filaOrigen) == 2 && abs(columna - colOrigen) == 2) {
                int filaComida = (fila + filaOrigen) / 2;
                int colComida = (columna + colOrigen) / 2;
                Ficha* fichaComida = casillas[filaComida][colComida];

                if (fichaComida != nullptr && fichaComida->getJugador() != fichaSeleccionada->getJugador()) {
                    comerFicha(fichaSeleccionada, fichaComida, fila, columna);
                    turnoJugador = 1; // Cambia turno a IA después de comer
                }
            } else {
                casillas[fila][columna] = fichaSeleccionada;
                fichaSeleccionada->moverA(fila, columna);
                casillas[filaOrigen][colOrigen] = nullptr;
                turnoJugador = 1; // Cambia turno a IA después de mover
            }
        }
        fichaSeleccionada = nullptr;
    }
}


void Tablero::colocarFicha(int fila, int columna, int jugador) {
    if (casillas[fila][columna] == nullptr){
        Ficha* ficha = new Ficha(fila, columna,jugador);
        casillas[fila][columna] = ficha;

        if (jugador == 1){
           listaFichasIA = Nodo::agregarFicha(listaFichasIA, ficha);
        }
        
    }
}

void Tablero::eliminarFicha(int fila, int columna) {
    if (casillas[fila][columna] != nullptr) {
        delete casillas[fila][columna];  // Liberás la memoria de la ficha
        casillas[fila][columna] = nullptr;  // Pones el puntero a nullptr para evitar dangling pointer
    }
}

Ficha* Tablero::obtenerFicha(int fila, int columna) {
    return casillas[fila][columna];
}

void Tablero::iniciarTablero() {
    
    // Colocar fichas en filas 0,1,2 para jugador 1 en casillas oscuras
    for (int fila = 0; fila <= 2; ++fila) {
        for (int col = 0; col < 8; ++col) {
            if ((fila + col) % 2 == 1) {
                colocarFicha(fila, col,1);
                // Más adelante podrías pasar un parámetro para distinguir jugador
            }
        }
    }

    // Colocar fichas en filas 5,6,7 para jugador 2 en casillas oscuras
    for (int fila = 5; fila <= 7; ++fila) {
        for (int col = 0; col < 8; ++col) {
            if ((fila + col) % 2 == 1) {
                colocarFicha(fila, col,2);
                // Más adelante diferenciar jugador
            }
        }
    }
}

void Tablero::comerFicha(Ficha* atacante, Ficha* comida, int filaDestino, int colDestino) {
    if (!atacante || !comida) return;

    // Eliminamos la ficha comida usando fila y columna en vez del puntero
    eliminarFicha(comida->getFila(), comida->getColumna());

    // Posiciones origen
    int filaOrigen = atacante->getFila();
    int colOrigen = atacante->getColumna();

    // Movemos la ficha atacante
    casillas[filaDestino][colDestino] = atacante;
    casillas[filaOrigen][colOrigen] = nullptr;
    atacante->moverA(filaDestino, colDestino);
}

void Tablero::generarMatrizMov() {
    for (int fila = 0; fila < 8; ++fila) {
        for (int columna = 0; columna < 8; ++columna) {
            // Si la casilla es negra, ponemos un 1, sino un 0
            movPosible[fila][columna] = (fila + columna) % 2 == 1 ? 1 : 0;
        }
    }
}

void jugarCPU(){

}