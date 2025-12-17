#include <iostream>
#include <limits>

using namespace std;

// Clase para el Nodo (en reemplazo de struct)
class Nodo {
public:
    int dato;
    Nodo* izq;
    Nodo* der;

    Nodo(int valor) {
        dato = valor;
        izq = nullptr;
        der = nullptr;
    }
};

class ArbolBusqueda {
public:
    Nodo* raiz;

    ArbolBusqueda() { raiz = nullptr; }

    // Inserción manteniendo duplicados juntos
    Nodo* insertar(Nodo* nodo, int valor) {
        if (nodo == nullptr) {
            return new Nodo(valor);
        }

        if (valor < nodo->dato) {
            nodo->izq = insertar(nodo->izq, valor);
        } else {
            // Si es mayor O IGUAL, va a la derecha para mantenerlos juntos
            nodo->der = insertar(nodo->der, valor);
        }
        return nodo;
    }

    // Visualización ASCII (Rotado 90 grados)
    void mostrarArbol(Nodo* nodo, int cont) {
        if (nodo == nullptr) return;

        mostrarArbol(nodo->der, cont + 1);

        for (int i = 0; i < cont; i++) {
            cout << "   ";
        }
        cout << nodo->dato << endl;

        mostrarArbol(nodo->izq, cont + 1);
    }
};

// Validación de entrada para evitar letras o caracteres especiales
int leerEntero() {
    int n;
    while (true) {
        if (cin >> n) {
            return n;
        } else {
            cout << "Error: Ingrese un numero valido: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    ArbolBusqueda arbol;
    int opcion, valor;

    do {
        cout << "\n--- MENU ARBOL BST (Duplicados Juntos) ---" << endl;
        cout << "1. Insertar numero" << endl;
        cout << "2. Mostrar arbol" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione: ";
        
        opcion = leerEntero();

        switch (opcion) {
            case 1:
                cout << "Ingrese valor: ";
                valor = leerEntero();
                arbol.raiz = arbol.insertar(arbol.raiz, valor);
                break;
            case 2:
                cout << "\nVisualizacion del Arbol (Raiz a la izquierda):\n" << endl;
                if (arbol.raiz == nullptr) cout << "Arbol vacio." << endl;
                else arbol.mostrarArbol(arbol.raiz, 0);
                break;
            case 3:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 3);

    return 0;
}