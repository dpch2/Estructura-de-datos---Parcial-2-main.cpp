#include <iostream>
#include <limits>

using namespace std;

// --- CLASE NODO DEL ÁRBOL ---
class Nodo {
public:
    int dato;
    Nodo* izq;
    Nodo* der;

    Nodo(int valor) : dato(valor), izq(nullptr), der(nullptr) {}
};

// --- CLASE NODO PARA LA PILA (Necesaria para el recorrido no recursivo) ---
class NodoPila {
public:
    Nodo* ptrArbol;
    NodoPila* siguiente;
    NodoPila(Nodo* n) : ptrArbol(n), siguiente(nullptr) {}
};

// --- CLASE PILA MANUAL (Sin usar librerías externas) ---
class Pila {
private:
    NodoPila* tope;
public:
    Pila() : tope(nullptr) {}
    bool estaVacia() { return tope == nullptr; }
    void push(Nodo* n) {
        NodoPila* nuevo = new NodoPila(n);
        nuevo->siguiente = tope;
        tope = nuevo;
    }
    Nodo* pop() {
        if (estaVacia()) return nullptr;
        NodoPila* temp = tope;
        Nodo* n = temp->ptrArbol;
        tope = tope->siguiente;
        delete temp;
        return n;
    }
};

// --- CLASE ÁRBOL BINARIO ---
class ArbolBusqueda {
public:
    Nodo* raiz;
    ArbolBusqueda() : raiz(nullptr) {}

    // Inserción manteniendo duplicados juntos
    void insertar(int valor) {
        Nodo* nuevo = new Nodo(valor);
        if (raiz == nullptr) {
            raiz = nuevo;
            return;
        }
        Nodo* aux = raiz;
        Nodo* padre = nullptr;
        while (aux != nullptr) {
            padre = aux;
            if (valor < aux->dato) aux = aux->izq;
            else aux = aux->der; // Duplicados van a la derecha
        }
        if (valor < padre->dato) padre->izq = nuevo;
        else padre->der = nuevo;
    }

    // RECORRIDO IN-ORDER NO RECURSIVO (Uso de Pila)
    void inOrderNoRecursivo() {
        if (raiz == nullptr) return;
        Pila p;
        Nodo* actual = raiz;
        while (actual != nullptr || !p.estaVacia()) {
            while (actual != nullptr) {
                p.push(actual);
                actual = actual->izq;
            }
            actual = p.pop();
            cout << actual->dato << " ";
            actual = actual->der;
        }
        cout << endl;
    }

    // ELIMINAR UN NODO ESPECÍFICO
    Nodo* eliminarNodo(Nodo* r, int clave) {
        if (r == nullptr) return r;
        if (clave < r->dato) r->izq = eliminarNodo(r->izq, clave);
        else if (clave > r->dato) r->der = eliminarNodo(r->der, clave);
        else { // Encontrado
            if (r->izq == nullptr) {
                Nodo* temp = r->der;
                delete r;
                return temp;
            } else if (r->der == nullptr) {
                Nodo* temp = r->izq;
                delete r;
                return temp;
            }
            // Nodo con dos hijos: buscar sucesor in-order
            Nodo* temp = r->der;
            while (temp->izq != nullptr) temp = temp->izq;
            r->dato = temp->dato;
            r->der = eliminarNodo(r->der, temp->dato);
        }
        return r;
    }

    // ELIMINAR TODO EL ÁRBOL (Post-order para no perder punteros)
    void limpiarArbol(Nodo* n) {
        if (n == nullptr) return;
        limpiarArbol(n->izq);
        limpiarArbol(n->der);
        delete n;
    }

    void mostrarArbol(Nodo* n, int cont) {
        if (n == nullptr) return;
        mostrarArbol(n->der, cont + 1);
        for (int i = 0; i < cont; i++) cout << "   ";
        cout << n->dato << endl;
        mostrarArbol(n->izq, cont + 1);
    }
};

// Validación de entrada
int leerEntero() {
    int n;
    while (!(cin >> n)) {
        cout << "Error. Ingrese un numero: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return n;
}

int main() {
    ArbolBusqueda arbol;
    int opcion, valor;

    do {
        cout << "\n--- MENU BST AVANZADO ---" << endl;
        cout << "1. Insertar numero" << endl;
        cout << "2. Mostrar arbol (Estructura)" << endl;
        cout << "3. Imprimir In-Order (No recursivo)" << endl;
        cout << "4. Eliminar un numero especifico" << endl;
        cout << "5. Vaciar/Eliminar arbol completo" << endl;
        cout << "6. Salir" << endl;
        cout << "Opcion: ";
        opcion = leerEntero();

        switch (opcion) {
            case 1:
                cout << "Valor: ";
                arbol.insertar(leerEntero());
                break;
            case 2:
                if (!arbol.raiz) cout << "Vacio." << endl;
                else arbol.mostrarArbol(arbol.raiz, 0);
                break;
            case 3:
                cout << "Recorrido In-Order: ";
                arbol.inOrderNoRecursivo();
                break;
            case 4:
                cout << "Numero a borrar: ";
                valor = leerEntero();
                arbol.raiz = arbol.eliminarNodo(arbol.raiz, valor);
                break;
            case 5:
                arbol.limpiarArbol(arbol.raiz);
                arbol.raiz = nullptr;
                cout << "Arbol eliminado." << endl;
                break;
        }
    } while (opcion != 6);

    return 0;
}