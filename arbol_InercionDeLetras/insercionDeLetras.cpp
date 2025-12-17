#include <iostream>
#include <cstdlib>
using namespace std;

// Clase Nodo para el arbol rojinegro
class Nodo {
public:
    char dato;
    bool esRojo;
    Nodo* izq;
    Nodo* der;
    Nodo* padre;
    
    Nodo(char valor) {
        dato = valor;
        esRojo = true;
        izq = NULL;
        der = NULL;
        padre = NULL;
    }
};

// Clase ArbolRojinegro
class ArbolRojinegro {
private:
    Nodo* raiz;
    
    // Rotacion izquierda
    void rotarIzquierda(Nodo* x) {
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
    
    // Rotacion derecha
    void rotarDerecha(Nodo* y) {
        Nodo* x = y->izq;
        y->izq = x->der;
        
        if (x->der != NULL)
            x->der->padre = y;
        
        x->padre = y->padre;
        
        if (y->padre == NULL)
            raiz = x;
        else if (y == y->padre->der)
            y->padre->der = x;
        else
            y->padre->izq = x;
        
        x->der = y;
        y->padre = x;
    }
    
    // Corregir violaciones despues de insertar
    void corregirInsercion(Nodo* k) {
        while (k->padre != NULL && k->padre->esRojo) {
            if (k->padre == k->padre->padre->izq) {
                Nodo* tio = k->padre->padre->der;
                
                // Caso 1: El tio es rojo
                if (tio != NULL && tio->esRojo) {
                    k->padre->esRojo = false;
                    tio->esRojo = false;
                    k->padre->padre->esRojo = true;
                    k = k->padre->padre;
                } else {
                    // Caso 2: El tio es negro y k es hijo derecho
                    if (k == k->padre->der) {
                        k = k->padre;
                        rotarIzquierda(k);
                    }
                    // Caso 3: El tio es negro y k es hijo izquierdo
                    k->padre->esRojo = false;
                    k->padre->padre->esRojo = true;
                    rotarDerecha(k->padre->padre);
                }
            } else {
                Nodo* tio = k->padre->padre->izq;
                
                // Caso 1: El tio es rojo
                if (tio != NULL && tio->esRojo) {
                    k->padre->esRojo = false;
                    tio->esRojo = false;
                    k->padre->padre->esRojo = true;
                    k = k->padre->padre;
                } else {
                    // Caso 2: El tio es negro y k es hijo izquierdo
                    if (k == k->padre->izq) {
                        k = k->padre;
                        rotarDerecha(k);
                    }
                    // Caso 3: El tio es negro y k es hijo derecho
                    k->padre->esRojo = false;
                    k->padre->padre->esRojo = true;
                    rotarIzquierda(k->padre->padre);
                }
            }
            
            if (k == raiz)
                break;
        }
        raiz->esRojo = false;
    }
    
    // Funcion auxiliar para imprimir
    void imprimirAuxiliar(Nodo* nodo, int nivel, char prefijo) {
        if (nodo == NULL)
            return;
        
        imprimirAuxiliar(nodo->der, nivel + 1, '/');
        
        for (int i = 0; i < nivel; i++)
            cout << "    ";
        
        if (nivel > 0)
            cout << prefijo << "---";
        
        cout << nodo->dato;
        if (nodo->esRojo)
            cout << "(R)";
        else
            cout << "(N)";
        cout << endl;
        
        imprimirAuxiliar(nodo->izq, nivel + 1, '\\');
    }
    
public:
    ArbolRojinegro() {
        raiz = NULL;
    }
    
    // Insertar nodo
    void insertar(char dato) {
        Nodo* nuevoNodo = new Nodo(dato);
        
        Nodo* padre = NULL;
        Nodo* actual = raiz;
        
        // Buscar posicion para insertar
        while (actual != NULL) {
            padre = actual;
            if (nuevoNodo->dato < actual->dato)
                actual = actual->izq;
            else
                actual = actual->der;
        }
        
        nuevoNodo->padre = padre;
        
        if (padre == NULL) {
            raiz = nuevoNodo;
        } else if (nuevoNodo->dato < padre->dato) {
            padre->izq = nuevoNodo;
        } else {
            padre->der = nuevoNodo;
        }
        
        // Si es la raiz, colorear de negro
        if (nuevoNodo->padre == NULL) {
            nuevoNodo->esRojo = false;
            return;
        }
        
        // Si el abuelo es NULL, retornar
        if (nuevoNodo->padre->padre == NULL)
            return;
        
        // Corregir el arbol
        corregirInsercion(nuevoNodo);
    }
    
    // Imprimir arbol
    void imprimir() {
        if (raiz == NULL) {
            cout << "El arbol esta vacio." << endl;
            return;
        }
        cout << "\nVisualizacion del arbol (R=Rojo, N=Negro):\n" << endl;
        imprimirAuxiliar(raiz, 0, ' ');
        cout << endl;
    }
    
    // Verificar si existe un nodo
    bool existe(char dato) {
        Nodo* actual = raiz;
        while (actual != NULL) {
            if (dato == actual->dato)
                return true;
            if (dato < actual->dato)
                actual = actual->izq;
            else
                actual = actual->der;
        }
        return false;
    }
};

// Funcion para validar entrada numerica
int leerOpcion() {
    char entrada[100];
    cin >> entrada;
    
    // Verificar que solo contiene digitos
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (entrada[i] < '0' || entrada[i] > '9') {
            return -1;
        }
    }
    
    return atoi(entrada);
}

int main() {
    ArbolRojinegro arbol;
    char siguienteLetra = 'A';
    int opcion;
    
    cout << "\n========================================" << endl;
    cout << "   ARBOL ROJINEGRO - INSERCION A-K" << endl;
    cout << "========================================\n" << endl;
    
    while (siguienteLetra <= 'K') {
        cout << "\n--- Menu Principal ---" << endl;
        cout << "Siguiente letra a insertar: " << siguienteLetra << endl;
        cout << "\n1. Insertar letra " << siguienteLetra << endl;
        cout << "2. Visualizar arbol" << endl;
        cout << "3. Salir" << endl;
        cout << "\nIngrese opcion: ";
        
        opcion = leerOpcion();
        
        if (opcion == -1) {
            cout << "\nError: Ingrese solo numeros." << endl;
            continue;
        }
        
        switch (opcion) {
            case 1: {
                cout << "\nInsertando letra " << siguienteLetra << "..." << endl;
                arbol.insertar(siguienteLetra);
                cout << "Letra " << siguienteLetra << " insertada correctamente." << endl;
                
                // Mostrar arbol despues de insertar
                arbol.imprimir();
                
                siguienteLetra++;
                
                if (siguienteLetra > 'K') {
                    cout << "\n¡Todas las letras de A a K han sido insertadas!" << endl;
                    cout << "\nArbol final:" << endl;
                    arbol.imprimir();
                    
                    cout << "\nCONCLUSION:" << endl;
                    cout << "Cuando las claves se insertan en orden ascendente en un" << endl;
                    cout << "arbol rojinegro, el arbol se autobalancea mediante rotaciones" << endl;
                    cout << "y recoloreos para mantener sus propiedades:" << endl;
                    cout << "1. La raiz siempre es negra" << endl;
                    cout << "2. No puede haber dos nodos rojos consecutivos" << endl;
                    cout << "3. Todos los caminos tienen la misma cantidad de nodos negros" << endl;
                    cout << "Esto previene la degeneracion en una lista enlazada." << endl;
                }
                break;
            }
            case 2:
                arbol.imprimir();
                break;
            case 3:
                cout << "\nSaliendo del programa..." << endl;
                return 0;
            default:
                cout << "\nOpcion invalida. Ingrese 1, 2 o 3." << endl;
        }
    }
    
    return 0;
}