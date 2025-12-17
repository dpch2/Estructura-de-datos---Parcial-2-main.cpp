#include <iostream>
#include <limits>

using namespace std;

// --- ESTRUCTURAS DE DATOS ---
class Nodo {
public:
    int dato;
    Nodo *izq, *der;
    Nodo(int valor) : dato(valor), izq(nullptr), der(nullptr) {}
};

class AuxNode {
public:
    Nodo* ptr;
    AuxNode* sig;
    AuxNode(Nodo* n) : ptr(n), sig(nullptr) {}
};

// --- ESTRUCTURAS AUXILIARES MANUALES ---
class Cola {
    AuxNode *frente, *final;
public:
    Cola() : frente(nullptr), final(nullptr) {}
    bool vacia() { return frente == nullptr; }
    void encolar(Nodo* n) {
        AuxNode* nuevo = new AuxNode(n);
        if (vacia()) frente = final = nuevo;
        else { final->sig = nuevo; final = nuevo; }
    }
    Nodo* desencolar() {
        if (vacia()) return nullptr;
        AuxNode* temp = frente;
        Nodo* n = temp->ptr;
        frente = frente->sig;
        delete temp;
        return n;
    }
};

class Pila {
    AuxNode* tope;
public:
    Pila() : tope(nullptr) {}
    bool vacia() { return tope == nullptr; }
    void push(Nodo* n) {
        AuxNode* nuevo = new AuxNode(n);
        nuevo->sig = tope;
        tope = nuevo;
    }
    Nodo* pop() {
        if (vacia()) return nullptr;
        AuxNode* temp = tope;
        Nodo* n = temp->ptr;
        tope = tope->sig;
        delete temp;
        return n;
    }
};

// --- CLASE ARBOL ---
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
            else curr = curr->der; // Mantiene duplicados juntos a la derecha
        }
        if (v < padre->dato) padre->izq = nuevo;
        else padre->der = nuevo;
    }

    void preOrder(Nodo* n) {
        if (!n) return;
        cout << "[" << n->dato << "] ";
        preOrder(n->izq);
        preOrder(n->der);
    }

    void inOrderNoRecursivo() {
        if (!raiz) return;
        Pila p;
        Nodo* curr = raiz;
        while (curr || !p.vacia()) {
            while (curr) { p.push(curr); curr = curr->izq; }
            curr = p.pop();
            cout << "[" << curr->dato << "] ";
            curr = curr->der;
        }
    }

    void postOrder(Nodo* n) {
        if (!n) return;
        postOrder(n->izq);
        postOrder(n->der);
        cout << "[" << n->dato << "] ";
    }

    void recorridoNiveles() {
        if (!raiz) return;
        Cola c;
        c.encolar(raiz);
        while (!c.vacia()) {
            Nodo* actual = c.desencolar();
            cout << "[" << actual->dato << "] ";
            if (actual->izq) c.encolar(actual->izq);
            if (actual->der) c.encolar(actual->der);
        }
    }

    void mostrarEstructura(Nodo* n, int h) {
        if (!n) return;
        mostrarEstructura(n->der, h + 1);
        for (int i = 0; i < h; i++) cout << "      ";
        cout << "--(" << n->dato << ")" << endl;
        mostrarEstructura(n->izq, h + 1);
    }

    Nodo* eliminarNodo(Nodo* r, int clave) {
        if (!r) return nullptr;
        if (clave < r->dato) r->izq = eliminarNodo(r->izq, clave);
        else if (clave > r->dato) r->der = eliminarNodo(r->der, clave);
        else {
            if (!r->izq) { Nodo* t = r->der; delete r; return t; }
            if (!r->der) { Nodo* t = r->izq; delete r; return t; }
            Nodo* t = r->der;
            while (t->izq) t = t->izq;
            r->dato = t->dato;
            r->der = eliminarNodo(r->der, t->dato);
        }
        return r;
    }

    void vaciar(Nodo* n) {
        if (!n) return;
        vaciar(n->izq);
        vaciar(n->der);
        delete n;
    }
};

// --- INTERFAZ Y VALIDACION ---
int leerEntero() {
    int x;
    while (!(cin >> x)) {
        cout << " >> Error: Ingrese solo numeros: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return x;
}

void dibujarCabecera(string titulo) {
    cout << "\n========================================" << endl;
    cout << "   " << titulo << endl;
    cout << "========================================" << endl;
}

int main() {
    Arbol t;
    int op, val;

    do {
        dibujarCabecera("GESTION DE ARBOL BINARIO (BST)");
        cout << " 1. Insertar Nuevo Numero" << endl;
        cout << " 2. Visualizar Estructura (ASCII)" << endl;
        cout << " 3. Recorrido Pre-Order" << endl;
        cout << " 4. Recorrido Simetrico (In-Order)" << endl;
        cout << " 5. Recorrido Post-Order" << endl;
        cout << " 6. Recorrido por Niveles (BFS)" << endl;
        cout << " 7. Eliminar un Numero" << endl;
        cout << " 8. Vaciar Arbol Completo" << endl;
        cout << " 9. Salir del Programa" << endl;
        cout << "----------------------------------------" << endl;
        cout << " Seleccione una opcion: ";
        op = leerEntero();

        switch(op) {
            case 1:
                cout << " > Valor a insertar: ";
                t.insertar(leerEntero());
                break;
            case 2:
                cout << "\nESTRUCTURA VISUAL (Raiz a la izquierda):" << endl;
                if (!t.raiz) cout << " ( Arbol vacio )" << endl;
                else t.mostrarEstructura(t.raiz, 0);
                break;
            case 3:
                cout << "\nPRE-ORDER: "; t.preOrder(t.raiz); cout << endl;
                break;
            case 4:
                cout << "\nIN-ORDER (Iterativo): "; t.inOrderNoRecursivo(); cout << endl;
                break;
            case 5:
                cout << "\nPOST-ORDER: "; t.postOrder(t.raiz); cout << endl;
                break;
            case 6:
                cout << "\nNIVELES: "; t.recorridoNiveles(); cout << endl;
                break;
            case 7:
                cout << " Valor a eliminar: ";
                val = leerEntero();
                t.raiz = t.eliminarNodo(t.raiz, val);
                break;
            case 8:
                t.vaciar(t.raiz);
                t.raiz = nullptr;
                cout << "\n Arbol vaciado exitosamente." << endl;
                break;
            case 9:
                cout << "\nSaliendo..." << endl;
                break;
            default:
                cout << "\n Opcion no valida." << endl;
        }
    } while (op != 9);

    return 0;
}