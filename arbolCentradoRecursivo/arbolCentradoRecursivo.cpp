//EJERCICIO 18
#include <iostream>
using namespace std;

// ================= NODO =================
class Nodo {
public:
    int dato;
    Nodo* izq;
    Nodo* der;

    Nodo(int d) {
        dato = d;
        izq = NULL;
        der = NULL;
    }
};

// ================= VALIDACION =================
int leerEntero() {
    int x;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Dato invalido. Ingrese un numero entero: ";
    }
    return x;
}

// ================= INSERTAR (BST SIMPLE) =================
void insertar(Nodo*& r, int v) {
    if (r == NULL) {
        r = new Nodo(v);
    } else if (v < r->dato) {
        insertar(r->izq, v);
    } else {
        insertar(r->der, v);
    }
}

// ================= DIBUJO RECURSIVO CENTRADO =================
void dibujarCentrado(Nodo* r, int inicio, int fin, int nivel) {
    if (r == NULL || inicio > fin) return;

    int pos = (inicio + fin) / 2;

    // bajar lineas segun nivel
    for (int i = 0; i < nivel; i++)
        cout << endl;

    // espacios hasta la posicion
    for (int i = 0; i < pos; i++)
        cout << " ";

    cout << r->dato;

    // llamadas recursivas
    dibujarCentrado(r->izq, inicio, pos - 1, nivel + 1);
    dibujarCentrado(r->der, pos + 1, fin, nivel + 1);
}

// ================= MENU =================
void menu() {
    cout << "\nMENU EJERCICIO 18\n";
    cout << "1. Insertar\n";
    cout << "2. Dibujar arbol centrado\n";
    cout << "3. Salir\n";
    cout << "Opcion: ";
}

// ================= MAIN =================
int main() {
    Nodo* raiz = NULL;
    int op, v;

    do {
        menu();
        op = leerEntero();

        switch (op) {
        case 1:
            cout << "Ingrese numero: ";
            v = leerEntero();
            insertar(raiz, v);
            break;

        case 2:
            cout << "\nARBOL CENTRADO (RECURSIVO):\n";
            dibujarCentrado(raiz, 0, 80, 0);
            cout << endl;
            break;

        case 3:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida\n";
        }

    } while (op != 3);

    return 0;
}
