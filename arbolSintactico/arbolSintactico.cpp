//EJERCICIO 16
#include <iostream>
using namespace std;

class Nodo {
public:
    char dato;
    Nodo* izq;
    Nodo* der;

    Nodo(char d) {
        dato = d;
        izq = NULL;
        der = NULL;
    }
};

void dibujar(Nodo* n, int nivel) {
    if (n == NULL) return;

    dibujar(n->der, nivel + 1);

    for (int i = 0; i < nivel; i++)
        cout << "    ";
    cout << n->dato << endl;

    dibujar(n->izq, nivel + 1);
}

int main() {
    // Construccion manual del arbol:
    // ((A+B)*C) + (D+E)

    Nodo* raiz = new Nodo('+');

    raiz->izq = new Nodo('*');
    raiz->der = new Nodo('+');

    raiz->izq->izq = new Nodo('+');
    raiz->izq->der = new Nodo('C');

    raiz->izq->izq->izq = new Nodo('A');
    raiz->izq->izq->der = new Nodo('B');

    raiz->der->izq = new Nodo('D');
    raiz->der->der = new Nodo('E');

    cout << "ARBOL DE ANALISIS SINTACTICO\n\n";
    dibujar(raiz, 0);

    return 0;
}

