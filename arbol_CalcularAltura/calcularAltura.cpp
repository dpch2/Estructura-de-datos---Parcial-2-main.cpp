#include <iostream>
#include <limits>
#include <algorithm> // Para usar la funcion max

using namespace std;

// --- ESTRUCTURA DEL NODO ---
class Nodo {
public:
    int dato;
    Nodo *izq, *der;
    Nodo(int valor) : dato(valor), izq(nullptr), der(nullptr) {}
};

// --- CLASE ARBOL CON FUNCION RECURSIVA DE ALTURA ---
class Arbol {
public:
    Nodo* raiz;
    Arbol() : raiz(nullptr) {}

    void insertar(int v) {
        Nodo* nuevo = new Nodo(v);
        if (!raiz) { raiz = nuevo; return; }
        Nodo *curr = raiz, *padre = nullptr;
        while (curr) {
            padre = curr;
            if (v < curr->dato) curr = curr->izq;
            else curr = curr->der;
        }
        if (v < padre->dato) padre->izq = nuevo;
        else padre->der = nuevo;
    }

    // --- FUNCION RECURSIVA PARA LA ALTURA ---
    int calcularAltura(Nodo* nodo) {
        if (nodo == nullptr) {
            return 0; // Caso base: arbol vacio o llegamos al final
        } else {
            // Calcular la altura de cada subarbol
            int alturaIzq = calcularAltura(nodo->izq);
            int alturaDer = calcularAltura(nodo->der);

            // Retornar la altura mayor mas 1 (el nodo actual)
            return 1 + max(alturaIzq, alturaDer);
        }
    }

    void mostrarEstructura(Nodo* n, int h) {
        if (!n) return;
        mostrarEstructura(n->der, h + 1);
        for (int i = 0; i < h; i++) cout << "      ";
        cout << "--(" << n->dato << ")" << endl;
        mostrarEstructura(n->izq, h + 1);
    }
};

int leerEntero() {
    int x;
    while (!(cin >> x)) {
        cout << " >> Error: Ingrese un numero: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return x;
}

int main() {
    Arbol t;
    int op;

    do {
        cout << "\n========================================" << endl;
        cout << "       CALCULO DE ALTURA RECURSIVA      " << endl;
        cout << "========================================" << endl;
        cout << " 1. [ + ] Insertar Numero" << endl;
        cout << " 2. [ V ] Ver Estructura" << endl;
        cout << " 3. [ H ] Calcular Altura del Arbol" << endl;
        cout << " 4. [ X ] Salir" << endl;
        cout << "----------------------------------------" << endl;
        cout << " >> Seleccione: ";
        op = leerEntero();

        switch(op) {
            case 1:
                cout << " > Valor: ";
                t.insertar(leerEntero());
                break;
            case 2:
                if (!t.raiz) cout << "Arbol vacio." << endl;
                else t.mostrarEstructura(t.raiz, 0);
                break;
            case 3:
                cout << "\n >> La altura del arbol es: " << t.calcularAltura(t.raiz) << " niveles." << endl;
                break;
        }
    } while (op != 4);

    return 0;
}