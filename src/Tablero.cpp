#include "Tablero.h"

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

bool Tablero::validarMovimiento(Ficha* ficha, int filaDestino, int colDestino) {
    if (ficha == nullptr) return false;

    int filaOrigen = ficha -> getFila();
    int colOrigen = ficha -> getColumna();

    // Validar límites
    if (filaDestino < 0 || filaDestino >= 8 || colDestino < 0 || colDestino >= 8)
        return false;

    // Validar que la casilla sea negra (donde se puede jugar)
    if (movPosible[filaDestino][colDestino] == 0)
        return false;

    // Verificar que la casilla destino esté vacía
    if (casillas[filaDestino][colDestino] != nullptr)
        return false;

    int difFila = filaDestino - filaOrigen;
    int difCol = colDestino - colOrigen;

    // Lo cambié para un solo if.
    if (!ficha -> puedeMoverA(filaDestino))
        return false;

    // Movimiento simple (1 casilla diagonal)
    if (abs(difFila) == 1 && abs(difCol) == 1) {
        return true;
    }

    // Salto (2 casillas): revisar si hay una ficha del rival en medio
    if (abs(difFila) == 2 && abs(difCol) == 2) {
        int filaIntermedia = (filaOrigen + filaDestino) / 2;
        int colIntermedia = (colOrigen + colDestino) / 2;

        Ficha* fichaIntermedia = casillas[filaIntermedia][colIntermedia];

        if (fichaIntermedia != nullptr && fichaIntermedia -> getJugador() != ficha -> getJugador()) {
            return true;
        }
    }

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
bool Tablero::manejarClick(int fila, int columna) {
    if (fila < 0 || fila >= 8 || columna < 0 || columna >= 8)
        return false;

    if (fichaSeleccionada == nullptr) {
        Ficha* ficha = casillas[fila][columna];
        if (ficha != nullptr && ficha->getJugador() == 1) {  // validar turno
            fichaSeleccionada = ficha;
            return true; // seleccionó ficha
        }
        return false; // no seleccionó nada válido
    }
    else {
        if (moverFicha(fichaSeleccionada, fila, columna)) {
            fichaSeleccionada = nullptr;
            return true; // movimiento válido, turno puede cambiar
        } else {
            fichaSeleccionada = nullptr; // deselecciona en movimiento inválido
            return false;
        }
    }
}



void Tablero::colocarFicha(int fila, int columna, int jugador) {
    if (casillas[fila][columna] == nullptr){
        Ficha* ficha = new Ficha(fila, columna,jugador);
        casillas[fila][columna] = ficha;

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
                colocarFicha(fila, col,2);
                // Más adelante podrías pasar un parámetro para distinguir jugador
            }
        }
    }

    // Colocar fichas en filas 5,6,7 para jugador 2 en casillas oscuras
    for (int fila = 5; fila <= 7; ++fila) {
        for (int col = 0; col < 8; ++col) {
            if ((fila + col) % 2 == 1) {
                colocarFicha(fila, col,1);
                // Más adelante diferenciar jugador
            }
        }
    }
}

void Tablero::generarMatrizMov() {
    for (int fila = 0; fila < 8; ++fila) {
        for (int columna = 0; columna < 8; ++columna) {
            // Si la casilla es negra, ponemos un 1, sino un 0
            movPosible[fila][columna] = (fila + columna) % 2 == 1 ? 1 : 0;
        }
    }
}

bool Tablero::moverFicha(Ficha* ficha, int filaDestino, int colDestino) {
    if (!validarMovimiento(ficha, filaDestino, colDestino)) return false;

    int filaOrigen = ficha->getFila();
    int colOrigen = ficha->getColumna();

    // Ver si es un salto
    if (abs(filaDestino - filaOrigen) == 2 && abs(colDestino - colOrigen) == 2) {
        int filaIntermedia = (filaOrigen + filaDestino) / 2;
        int colIntermedia = (colOrigen + colDestino) / 2;

        if (casillas[filaIntermedia][colIntermedia] != nullptr) {
            delete casillas[filaIntermedia][colIntermedia];
            casillas[filaIntermedia][colIntermedia] = nullptr;
        }
    }

    // Mover ficha
    casillas[filaOrigen][colOrigen] = nullptr;
    casillas[filaDestino][colDestino] = ficha;
    ficha->moverA(filaDestino, colDestino);

    // // Promoción a dama
    // if ((ficha->getJugador() == 1 && filaDestino == 0) ||
    //     (ficha->getJugador() == 2 && filaDestino == 7)) {
    //     ficha -> esDama = true;
    // }

    return true;
}
