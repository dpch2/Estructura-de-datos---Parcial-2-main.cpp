#include <iostream>
using namespace std;

const int MAX_NODOS = 100;
const int MAX_PILA = 100;

// Arrays para el árbol
int valores[MAX_NODOS];
int izq[MAX_NODOS];
int der[MAX_NODOS];
int numNodos = 0;
int raiz = -1;

// Pila para el recorrido iterativo
int pila[MAX_PILA];
int tope = -1;

// ========== FUNCIONES DE PILA ==========

bool pilaVacia() {
    return tope == -1;
}

bool pilaLlena() {
    return tope >= MAX_PILA - 1;
}

void push(int valor) {
    if (pilaLlena()) {
        cout << "Error: Pila llena" << endl;
        return;
    }
    pila[++tope] = valor;
}

int pop() {
    if (pilaVacia()) {
        cout << "Error: Pila vacia" << endl;
        return -1;
    }
    return pila[tope--];
}

int peek() {
    if (pilaVacia()) {
        return -1;
    }
    return pila[tope];
}

void limpiarPila() {
    tope = -1;
}

// ========== FUNCIONES DEL ÁRBOL ==========

int crearNodo(int valor) {
    if (numNodos >= MAX_NODOS) {
        cout << "Error: Arbol lleno" << endl;
        return -1;
    }
    int idx = numNodos++;
    valores[idx] = valor;
    izq[idx] = -1;
    der[idx] = -1;
    return idx;
}

void insertar(int valor) {
    int nuevo = crearNodo(valor);
    if (nuevo == -1) return;
    
    if (raiz == -1) {
        raiz = nuevo;
        cout << "Raiz: " << valor << endl;
        return;
    }
    
    int actual = raiz;
    int padre = -1;
    
    while (actual != -1) {
        padre = actual;
        if (valor < valores[actual]) {
            actual = izq[actual];
        } else if (valor > valores[actual]) {
            actual = der[actual];
        } else {
            numNodos--;
            cout << "Valor duplicado, no se inserta" << endl;
            return;
        }
    }
    
    if (valor < valores[padre]) {
        izq[padre] = nuevo;
    } else {
        der[padre] = nuevo;
    }
}

// *** RECORRIDO INORDEN NO RECURSIVO (ITERATIVO) ***
void inordenIterativo() {
    if (raiz == -1) {
        cout << "Arbol vacio" << endl;
        return;
    }
    
    limpiarPila();
    int actual = raiz;
    
    cout << "\n=== RECORRIDO INORDEN (ITERATIVO) ===" << endl;
    cout << "Orden: ";
    
    // Algoritmo iterativo usando pila
    while (actual != -1 || !pilaVacia()) {
        
        // Ir al nodo más a la izquierda, apilando todos los nodos
        while (actual != -1) {
            push(actual);
            actual = izq[actual];
        }
        
        // El tope de la pila tiene el siguiente nodo en inorden
        actual = pop();
        
        // Procesar (imprimir) el nodo actual
        cout << valores[actual] << " ";
        
        // Ir al subárbol derecho
        actual = der[actual];
    }
    
    cout << endl;
}

// Recorrido con explicación paso a paso
void inordenIterativoDetallado() {
    if (raiz == -1) {
        cout << "Arbol vacio" << endl;
        return;
    }
    
    limpiarPila();
    int actual = raiz;
    int paso = 1;
    
    cout << "\n=== RECORRIDO INORDEN DETALLADO ===" << endl;
    
    while (actual != -1 || !pilaVacia()) {
        
        // Ir al nodo más a la izquierda
        while (actual != -1) {
            cout << "Paso " << paso++ << ": Apilar " << valores[actual] 
                 << " e ir a la izquierda" << endl;
            push(actual);
            actual = izq[actual];
        }
        
        // Desapilar y procesar
        actual = pop();
        cout << "Paso " << paso++ << ": Desapilar y visitar " 
             << valores[actual] << " *** IMPRIMIR ***" << endl;
        
        // Ir al subárbol derecho
        if (der[actual] != -1) {
            cout << "Paso " << paso++ << ": Ir al hijo derecho de " 
                 << valores[actual] << endl;
        }
        actual = der[actual];
    }
}

// Recorrido recursivo (para comparación)
void inordenRecursivo(int nodo) {
    if (nodo == -1) return;
    inordenRecursivo(izq[nodo]);
    cout << valores[nodo] << " ";
    inordenRecursivo(der[nodo]);
}

// Imprimir árbol visual
void imprimirArbol(int nodo, string prefijo, bool esIzq) {
    if (nodo == -1) return;
    
    cout << prefijo;
    cout << (esIzq ? "├──" : "└──");
    cout << valores[nodo] << endl;
    
    if (izq[nodo] != -1 || der[nodo] != -1) {
        if (izq[nodo] != -1) {
            imprimirArbol(izq[nodo], prefijo + (esIzq ? "│   " : "    "), true);
        }
        if (der[nodo] != -1) {
            imprimirArbol(der[nodo], prefijo + (esIzq ? "│   " : "    "), false);
        }
    }
}

// Validar entrada
bool validarEntrada(int &valor) {
    if (cin >> valor) {
        return true;
    } else {
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
}

int main() {
    cout << "========================================================" << endl;
    cout << "  RECORRIDO INORDEN NO RECURSIVO (ITERATIVO)" << endl;
    cout << "========================================================" << endl;
    cout << "\nEste programa usa una PILA para simular la recursion" << endl;
    cout << "y realizar el recorrido inorden de forma ITERATIVA." << endl;
    cout << "========================================================" << endl;
    
    int opcion;
    
    do {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Insertar nodo" << endl;
        cout << "2. Inorden ITERATIVO (simple)" << endl;
        cout << "3. Inorden ITERATIVO (detallado)" << endl;
        cout << "4. Inorden RECURSIVO (comparacion)" << endl;
        cout << "5. Mostrar arbol" << endl;
        cout << "6. Ejemplo predefinido" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        
        if (!validarEntrada(opcion)) {
            cout << "Error: Ingrese un numero valido" << endl;
            continue;
        }
        
        switch(opcion) {
            case 1: {
                int valor;
                cout << "Ingrese valor a insertar: ";
                if (!validarEntrada(valor)) {
                    cout << "Error: Ingrese un numero valido" << endl;
                    break;
                }
                insertar(valor);
                cout << "Valor " << valor << " insertado correctamente" << endl;
                break;
            }
            
            case 2: {
                if (raiz == -1) {
                    cout << "Arbol vacio" << endl;
                } else {
                    inordenIterativo();
                    cout << "\nEl recorrido inorden muestra las claves en ORDEN ASCENDENTE" << endl;
                }
                break;
            }
            
            case 3: {
                if (raiz == -1) {
                    cout << "Arbol vacio" << endl;
                } else {
                    inordenIterativoDetallado();
                    cout << "\nResultado final (en orden): ";
                    inordenIterativo();
                }
                break;
            }
            
            case 4: {
                if (raiz == -1) {
                    cout << "Arbol vacio" << endl;
                } else {
                    cout << "\n=== INORDEN RECURSIVO (para comparacion) ===" << endl;
                    cout << "Orden: ";
                    inordenRecursivo(raiz);
                    cout << endl;
                }
                break;
            }
            
            case 5: {
                if (raiz == -1) {
                    cout << "Arbol vacio" << endl;
                } else {
                    cout << "\n=== ESTRUCTURA DEL ARBOL ===" << endl;
                    imprimirArbol(raiz, "", false);
                    cout << "\nNodos totales: " << numNodos << endl;
                }
                break;
            }
            
            case 6: {
                // Limpiar árbol
                numNodos = 0;
                raiz = -1;
                
                cout << "\n=== CREANDO ARBOL DE EJEMPLO ===" << endl;
                cout << "Insertando: 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 65" << endl;
                
                int ejemplo[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 65};
                for (int i = 0; i < 11; i++) {
                    insertar(ejemplo[i]);
                }
                
                cout << "\n=== ARBOL GENERADO ===" << endl;
                imprimirArbol(raiz, "", false);
                
                cout << "\n=== RECORRIDO INORDEN ===" << endl;
                inordenIterativo();
                
                cout << "\nObserva que el resultado esta en ORDEN ASCENDENTE" << endl;
                break;
            }
            
            case 0:
                cout << "Saliendo..." << endl;
                break;
                
            default:
                cout << "Opcion invalida" << endl;
        }
        
    } while (opcion != 0);
    
    cout << "\n========================================================" << endl;
    cout << "ALGORITMO ITERATIVO INORDEN:" << endl;
    cout << "========================================================" << endl;
    cout << "1. Inicializar pila vacia y actual = raiz" << endl;
    cout << "2. Mientras (actual != null O pila no vacia):" << endl;
    cout << "   a) Mientras (actual != null):" << endl;
    cout << "      - Apilar actual" << endl;
    cout << "      - actual = hijo izquierdo" << endl;
    cout << "   b) actual = desapilar()" << endl;
    cout << "   c) VISITAR/IMPRIMIR actual" << endl;
    cout << "   d) actual = hijo derecho" << endl;
    cout << "========================================================" << endl;
    cout << "\nCOMPLEJIDAD:" << endl;
    cout << "- Tiempo: O(n) - visita cada nodo una vez" << endl;
    cout << "- Espacio: O(h) - altura del arbol (peor caso O(n))" << endl;
    cout << "========================================================" << endl;
    
    return 0;
}