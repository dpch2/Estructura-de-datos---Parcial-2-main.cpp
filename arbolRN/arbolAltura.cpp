//EJERCICIO 20
#include <iostream>
#include <iomanip>
using namespace std;

enum Color { ROJO, NEGRO };

struct Nodo {
    int dato;
    Color color;
    Nodo* izq;
    Nodo* der;
    Nodo* padre;

    Nodo(int v) {
        dato = v;
        color = ROJO;
        izq = der = padre = nullptr;
    }
};

class ArbolRN {
private:
    Nodo* raiz;

    void rotarIzq(Nodo*& x) {
        Nodo* y = x->der;
        x->der = y->izq;

        if (y->izq != nullptr)
            y->izq->padre = x;

        y->padre = x->padre;

        if (x->padre == nullptr)
            raiz = y;
        else if (x == x->padre->izq)
            x->padre->izq = y;
        else
            x->padre->der = y;

        y->izq = x;
        x->padre = y;
    }

    void rotarDer(Nodo*& x) {
        Nodo* y = x->izq;
        x->izq = y->der;

        if (y->der != nullptr)
            y->der->padre = x;

        y->padre = x->padre;

        if (x->padre == nullptr)
            raiz = y;
        else if (x == x->padre->der)
            x->padre->der = y;
        else
            x->padre->izq = y;

        y->der = x;
        x->padre = y;
    }

    void corregirInsertar(Nodo*& z) {
        while (z != raiz && z->padre->color == ROJO) {
            Nodo* abuelo = z->padre->padre;

            if (z->padre == abuelo->izq) {
                Nodo* tio = abuelo->der;

                if (tio && tio->color == ROJO) {
                    z->padre->color = NEGRO;
                    tio->color = NEGRO;
                    abuelo->color = ROJO;
                    z = abuelo;
                } else {
                    if (z == z->padre->der) {
                        z = z->padre;
                        rotarIzq(z);
                    }
                    z->padre->color = NEGRO;
                    abuelo->color = ROJO;
                    rotarDer(abuelo);
                }
            } else {
                Nodo* tio = abuelo->izq;

                if (tio && tio->color == ROJO) {
                    z->padre->color = NEGRO;
                    tio->color = NEGRO;
                    abuelo->color = ROJO;
                    z = abuelo;
                } else {
                    if (z == z->padre->izq) {
                        z = z->padre;
                        rotarDer(z);
                    }
                    z->padre->color = NEGRO;
                    abuelo->color = ROJO;
                    rotarIzq(abuelo);
                }
            }
        }
        raiz->color = NEGRO;
    }

    void imprimir(Nodo* n, int espacio) {
        if (!n) return;

        espacio += 8;
        imprimir(n->der, espacio);

        cout << endl;
        for (int i = 8; i < espacio; i++) cout << " ";
        cout << "[" << n->dato << (n->color == ROJO ? " R" : " N") << "]";

        imprimir(n->izq, espacio);
    }

    void inorden(Nodo* n) {
        if (!n) return;
        inorden(n->izq);
        cout << n->dato << " ";
        inorden(n->der);
    }

    int alturaNegra(Nodo* n) {
        if (!n) return 1;

        int izq = alturaNegra(n->izq);
        int der = alturaNegra(n->der);

        int suma = (n->color == NEGRO) ? 1 : 0;
        return izq + suma;
    }

    void liberar(Nodo* n) {
        if (!n) return;
        liberar(n->izq);
        liberar(n->der);
        delete n;
    }

public:
    ArbolRN() {
        raiz = nullptr;
    }

    void insertar(int valor) {
        Nodo* nuevo = new Nodo(valor);
        Nodo* y = nullptr;
        Nodo* x = raiz;

        while (x != nullptr) {
            y = x;
            if (valor < x->dato)
                x = x->izq;
            else
                x = x->der;
        }

        nuevo->padre = y;

        if (y == nullptr)
            raiz = nuevo;
        else if (valor < y->dato)
            y->izq = nuevo;
        else
            y->der = nuevo;

        corregirInsertar(nuevo);
    }

    void mostrar() {
        if (!raiz) {
            cout << "\nArbol vacio\n";
            return;
        }

        cout << "\nARBOL:\n";
        imprimir(raiz, 0);

        cout << "\n\nRECORRIDO INORDEN: ";
        inorden(raiz);

        cout << "\nAltura NEGRA: " << alturaNegra(raiz) << endl;
    }

    void reiniciar() {
        liberar(raiz);
        raiz = nullptr;
    }
};

int main() {
    ArbolRN arbol;
    int opcion, valor;

    do {
        cout << "\n==============================\n";
        cout << "EJERCICIO 20 - ARBOL ROJO NEGRO\n";
        cout << "==============================\n";
        cout << "1. Insertar valor\n";
        cout << "2. Imprimir arbol\n";
        cout << "3. Reiniciar arbol\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese valor: ";
                cin >> valor;
                arbol.insertar(valor);
                break;

            case 2:
                arbol.mostrar();
                break;

            case 3:
                arbol.reiniciar();
                cout << "Arbol reiniciado\n";
                break;
        }
    } while (opcion != 4);

    return 0;
}