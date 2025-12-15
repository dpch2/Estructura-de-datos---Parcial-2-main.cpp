// EJERCICIO 17: Comparacion de Espacio (Pila vs Cola)
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

// ================= INSERTAR =================
// Insercion forzada a la izquierda (arbol degenerado)
void insertar(Nodo*& raiz, int valor) {
    if (raiz == NULL) {
        raiz = new Nodo(valor);
    } else {
        insertar(raiz->izq, valor);
    }
}

// ================= PREORDEN (PILA) =================
void preorden(Nodo* r) {
    if (r == NULL) return;
    cout << r->dato << " ";
    preorden(r->izq);
    preorden(r->der);
}

// ================= DIBUJAR ARBOL =================
void dibujar(Nodo* r, int nivel) {
    if (r == NULL) return;

    dibujar(r->der, nivel + 1);
    for (int i = 0; i < nivel; i++)
        cout << "    ";
    cout << r->dato << endl;
    dibujar(r->izq, nivel + 1);
}

// ================= EDITAR =================
bool editar(Nodo* r, int viejo, int nuevo) {
    if (r == NULL) return false;

    if (r->dato == viejo) {
        r->dato = nuevo;
        return true;
    }
    return editar(r->izq, viejo, nuevo) || editar(r->der, viejo, nuevo);
}

// ================= ELIMINAR (SOLO HOJAS) =================
bool eliminar(Nodo*& r, int valor) {
    if (r == NULL) return false;

    if (r->dato == valor && r->izq == NULL && r->der == NULL) {
        delete r;
        r = NULL;
        return true;
    }

    return eliminar(r->izq, valor) || eliminar(r->der, valor);
}

// ================= COLA PARA NIVELES =================
class Cola {
public:
    Nodo* dato;
    Cola* sig;

    Cola(Nodo* n) {
        dato = n;
        sig = NULL;
    }
};

void encolar(Cola*& frente, Cola*& fin, Nodo* n) {
    Cola* nuevo = new Cola(n);
    if (fin == NULL) {
        frente = fin = nuevo;
    } else {
        fin->sig = nuevo;
        fin = nuevo;
    }
}

Nodo* desencolar(Cola*& frente, Cola*& fin) {
    if (frente == NULL) return NULL;

    Cola* aux = frente;
    Nodo* n = aux->dato;
    frente = frente->sig;

    if (frente == NULL)
        fin = NULL;

    delete aux;
    return n;
}

// ================= RECORRIDO POR NIVELES (COLA) =================
void porNiveles(Nodo* raiz) {
    if (raiz == NULL) return;

    Cola* frente = NULL;
    Cola* fin = NULL;

    encolar(frente, fin, raiz);

    while (frente != NULL) {
        Nodo* actual = desencolar(frente, fin);
        cout << actual->dato << " ";

        if (actual->izq)
            encolar(frente, fin, actual->izq);
        if (actual->der)
            encolar(frente, fin, actual->der);
    }
}

// ================= MENU =================
void menu() {
    cout << "\nMENU EJERCICIO 17\n";
    cout << "1. Insertar\n";
    cout << "2. Editar\n";
    cout << "3. Eliminar (solo hojas)\n";
    cout << "4. Imprimir recorridos y arbol\n";
    cout << "5. Salir\n";
    cout << "Opcion: ";
}

// ================= MAIN =================
int main() {
    Nodo* raiz = NULL;
    int op, a, b;

    do {
        menu();
        op = leerEntero();

        switch (op) {
        case 1:
            cout << "Ingrese numero a insertar: ";
            a = leerEntero();
            insertar(raiz, a);
            break;

        case 2:
            cout << "Valor a editar: ";
            a = leerEntero();
            cout << "Nuevo valor: ";
            b = leerEntero();
            if (!editar(raiz, a, b))
                cout << "Dato no encontrado\n";
            break;

        case 3:
            cout << "Valor a eliminar (solo hojas): ";
            a = leerEntero();
            if (!eliminar(raiz, a))
                cout << "No se pudo eliminar (no es hoja o no existe)\n";
            break;

        case 4:
            cout << "\nPREORDEN (PILA):\n";
            preorden(raiz);

            cout << "\n\nPOR NIVELES (COLA):\n";
            porNiveles(raiz);

            cout << "\n\nARBOL:\n";
            dibujar(raiz, 0);
            break;

        case 5:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida\n";
        }

    } while (op != 5);

    return 0;
}
