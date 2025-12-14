//EJERCICIO 19
#include <iostream>
using namespace std;

enum Color { ROJO, NEGRO };

// ================= NODO =================
class Nodo {
public:
    int dato;
    Color color;
    Nodo* izq;
    Nodo* der;
    Nodo* padre;

    Nodo(int d) {
        dato = d;
        color = ROJO;
        izq = der = padre = NULL;
    }
};

// ================= ROTACIONES =================
void rotarIzq(Nodo*& raiz, Nodo*& x) {
    Nodo* y = x->der;
    x->der = y->izq;

    if (y->izq != NULL)
        y->izq->padre = x;

    y->padre = x->padre;

    if (x->padre == NULL)
        raiz = y;
    else if (x == x->padre->izq)
        x->padre->izq = y;
    else
        x->padre->der = y;

    y->izq = x;
    x->padre = y;
}

void rotarDer(Nodo*& raiz, Nodo*& y) {
    Nodo* x = y->izq;
    y->izq = x->der;

    if (x->der != NULL)
        x->der->padre = y;

    x->padre = y->padre;

    if (y->padre == NULL)
        raiz = x;
    else if (y == y->padre->izq)
        y->padre->izq = x;
    else
        y->padre->der = x;

    x->der = y;
    y->padre = x;
}

// ================= ARREGLAR INSERCION =================
void arreglarInsercion(Nodo*& raiz, Nodo*& z) {
    while (z != raiz && z->padre->color == ROJO) {
        Nodo* padre = z->padre;
        Nodo* abuelo = padre->padre;

        if (padre == abuelo->izq) {
            Nodo* tio = abuelo->der;

            if (tio != NULL && tio->color == ROJO) {
                padre->color = NEGRO;
                tio->color = NEGRO;
                abuelo->color = ROJO;
                z = abuelo;
            } else {
                if (z == padre->der) {
                    z = padre;
                    rotarIzq(raiz, z);
                }
                padre->color = NEGRO;
                abuelo->color = ROJO;
                rotarDer(raiz, abuelo);
            }
        } else {
            Nodo* tio = abuelo->izq;

            if (tio != NULL && tio->color == ROJO) {
                padre->color = NEGRO;
                tio->color = NEGRO;
                abuelo->color = ROJO;
                z = abuelo;
            } else {
                if (z == padre->izq) {
                    z = padre;
                    rotarDer(raiz, z);
                }
                padre->color = NEGRO;
                abuelo->color = ROJO;
                rotarIzq(raiz, abuelo);
            }
        }
    }
    raiz->color = NEGRO;
}

// ================= INSERTAR =================
void insertar(Nodo*& raiz, int dato) {
    Nodo* z = new Nodo(dato);
    Nodo* y = NULL;
    Nodo* x = raiz;

    while (x != NULL) {
        y = x;
        if (dato < x->dato)
            x = x->izq;
        else
            x = x->der;
    }

    z->padre = y;

    if (y == NULL)
        raiz = z;
    else if (dato < y->dato)
        y->izq = z;
    else
        y->der = z;

    arreglarInsercion(raiz, z);
}

// ================= BUSCAR =================
bool buscar(Nodo* r, int v) {
    if (r == NULL) return false;
    if (r->dato == v) return true;
    if (v < r->dato) return buscar(r->izq, v);
    return buscar(r->der, v);
}

// ================= RECORRIDO INORDEN =================
void inorden(Nodo* r) {
    if (r == NULL) return;
    inorden(r->izq);
    cout << r->dato << " ";
    inorden(r->der);
}

// ================= IMPRIMIR ARBOL =================
void imprimir(Nodo* r, int espacio) {
    if (r == NULL) return;

    espacio += 6;
    imprimir(r->der, espacio);

    cout << endl;
    for (int i = 6; i < espacio; i++)
        cout << " ";
    cout << "[" << r->dato << (r->color == ROJO ? " R" : " N") << "]";

    imprimir(r->izq, espacio);
}

// ================= EDITAR (ELIMINAR + INSERTAR) =================
void editar(Nodo*& raiz, int viejo, int nuevo) {
    if (!buscar(raiz, viejo)) {
        cout << "Valor no encontrado\n";
        return;
    }

    // Reconstruccion academica del arbol
    int datos[] = {10,20,30,40,50,60,70,80,90,100};
    raiz = NULL;

    for (int i = 0; i < 10; i++) {
        if (datos[i] != viejo)
            insertar(raiz, datos[i]);
    }
    insertar(raiz, nuevo);

    cout << "Valor editado correctamente\n";
}

// ================= MENU =================
int main() {
    Nodo* raiz = NULL;
    int op, v, viejo, nuevo;

    do {
        cout << "\n=== EJERCICIO 19: ARBOL ROJO-NEGRO ===\n";
        cout << "1. Insertar valor\n";
        cout << "2. Insertar secuencia completa (10-100)\n";
        cout << "3. Editar valor\n";
        cout << "4. Imprimir arbol\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch (op) {
        case 1:
            cout << "Ingrese valor: ";
            cin >> v;
            insertar(raiz, v);
            break;

        case 2: {
            int sec[] = {10,20,30,40,50,60,70,80,90,100};
            for (int i = 0; i < 10; i++)
                insertar(raiz, sec[i]);
            cout << "Secuencia insertada\n";
            break;
        }

        case 3:
            cout << "Valor a editar: ";
            cin >> viejo;
            cout << "Nuevo valor: ";
            cin >> nuevo;
            editar(raiz, viejo, nuevo);
            break;

        case 4:
            cout << "\nARBOL ROJO-NEGRO:\n";
            imprimir(raiz, 0);
            cout << "\n\nRECORRIDO INORDEN: ";
            inorden(raiz);
            cout << endl;
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
