#include <iostream>
using namespace std;

const int MAX_NODOS = 50;
const int MAX_COLA = 50;

// Arrays para el árbol
char valores[MAX_NODOS];
int izq[MAX_NODOS];
int der[MAX_NODOS];
int numNodos = 0;

// Cola para recorrido por niveles
int cola[MAX_COLA];
int frente = 0;
int final = -1;

// ========== FUNCIONES DE COLA ==========

bool colaVacia() {
    return final < frente;
}

bool colaLlena() {
    return final >= MAX_COLA - 1;
}

void encolar(int valor) {
    if (colaLlena()) {
        cout << "Error: Cola llena" << endl;
        return;
    }
    if (final == -1) {
        frente = 0;
        final = 0;
    } else {
        final++;
    }
    cola[final] = valor;
}

int desencolar() {
    if (colaVacia()) {
        return -1;
    }
    int valor = cola[frente];
    frente++;
    if (frente > final) {
        frente = 0;
        final = -1;
    }
    return valor;
}

void limpiarCola() {
    frente = 0;
    final = -1;
}

// ========== FUNCIONES DEL ÁRBOL ==========

int crearNodo(char valor) {
    if (numNodos >= MAX_NODOS) {
        return -1;
    }
    int idx = numNodos++;
    valores[idx] = valor;
    izq[idx] = -1;
    der[idx] = -1;
    return idx;
}

// *** 1. ORDEN PREVIO (PreOrder: Raíz-Izq-Der) ***
void preorden(int nodo) {
    if (nodo == -1) return;
    
    cout << valores[nodo] << " ";      // 1. Visitar raíz
    preorden(izq[nodo]);                // 2. Recorrer izquierdo
    preorden(der[nodo]);                // 3. Recorrer derecho
}

// *** 2. ORDEN SIMÉTRICO (InOrder: Izq-Raíz-Der) ***
void inorden(int nodo) {
    if (nodo == -1) return;
    
    inorden(izq[nodo]);                 // 1. Recorrer izquierdo
    cout << valores[nodo] << " ";       // 2. Visitar raíz
    inorden(der[nodo]);                 // 3. Recorrer derecho
}

// *** 3. ORDEN POSTERIOR (PostOrder: Izq-Der-Raíz) ***
void postorden(int nodo) {
    if (nodo == -1) return;
    
    postorden(izq[nodo]);               // 1. Recorrer izquierdo
    postorden(der[nodo]);               // 2. Recorrer derecho
    cout << valores[nodo] << " ";       // 3. Visitar raíz
}

// *** 4. ORDEN DE NIVEL (Level Order: por niveles) ***
void porNiveles(int raiz) {
    if (raiz == -1) return;
    
    limpiarCola();
    encolar(raiz);
    
    while (!colaVacia()) {
        int actual = desencolar();
        cout << valores[actual] << " ";
        
        if (izq[actual] != -1) {
            encolar(izq[actual]);
        }
        if (der[actual] != -1) {
            encolar(der[actual]);
        }
    }
}

// Imprimir árbol visual con ASCII simple
void imprimirArbol(int nodo, string prefijo, bool esUltimo) {
    if (nodo == -1) return;
    
    cout << prefijo;
    
    if (esUltimo) {
        cout << "+-- ";
        prefijo += "    ";
    } else {
        cout << "+-- ";
        prefijo += "|   ";
    }
    
    cout << valores[nodo] << endl;
    
    // Contar hijos existentes
    bool tieneIzq = (izq[nodo] != -1);
    bool tieneDer = (der[nodo] != -1);
    
    if (tieneIzq) {
        imprimirArbol(izq[nodo], prefijo, !tieneDer);
    }
    if (tieneDer) {
        imprimirArbol(der[nodo], prefijo, true);
    }
}

// Construir el árbol de la Figura 4.3
int construirArbolFigura43() {
    // Crear todos los nodos
    int O = crearNodo('O');   // Raíz
    int C = crearNodo('C');   // Hijo izq de O
    int M = crearNodo('M');   // Hijo der de O
    int A = crearNodo('A');   // Hijo izq de C
    int O2 = crearNodo('O');  // Hijo der de C
    int P = crearNodo('P');   // Hijo izq de M
    int L = crearNodo('L');   // Hijo der de M
    int R = crearNodo('R');   // Hijo der de A
    int B = crearNodo('B');   // Hijo izq de O2
    int L2 = crearNodo('L');  // Hijo der de O2
    int E = crearNodo('E');   // Hijo izq de P
    int T = crearNodo('T');   // Hijo izq de L
    int O3 = crearNodo('O');  // Hijo der de L
    
    // Conectar nodos según la figura
    izq[O] = C;
    der[O] = M;
    
    izq[C] = A;
    der[C] = O2;
    
    izq[M] = P;
    der[M] = L;
    
    der[A] = R;
    
    izq[O2] = B;
    der[O2] = L2;
    
    izq[P] = E;
    
    izq[L] = T;
    der[L] = O3;
    
    return O; // Retorna la raíz
}

int main() {
    cout << "============================================================" << endl;
    cout << "  RECORRIDOS DEL ARBOL BINARIO COMPLETO (Figura 4.3)" << endl;
    cout << "============================================================" << endl;
    
    // Construir el árbol de la figura
    int raiz = construirArbolFigura43();
    
    cout << "\n=== ESTRUCTURA DEL ARBOL ===" << endl;
    cout << "\n                O" << endl;
    cout << "              /   \\" << endl;
    cout << "             C     M" << endl;
    cout << "            / \\   / \\" << endl;
    cout << "           A   O P   L" << endl;
    cout << "            \\  / \\   / \\" << endl;
    cout << "             R B L E   T O" << endl;
    
    cout << "\n\n=== REPRESENTACION VISUAL ===" << endl;
    imprimirArbol(raiz, "", true);
    
    cout << "\n============================================================" << endl;
    cout << "  RESULTADOS DE LOS RECORRIDOS" << endl;
    cout << "============================================================" << endl;
    
    cout << "\n1. ORDEN PREVIO (PreOrder: Raiz-Izq-Der):" << endl;
    cout << "   Orden: ";
    preorden(raiz);
    cout << endl;
    cout << "   Explicacion: Visita primero la raiz, luego subarbol izq, luego der" << endl;
    
    cout << "\n2. ORDEN SIMETRICO (InOrder: Izq-Raiz-Der):" << endl;
    cout << "   Orden: ";
    inorden(raiz);
    cout << endl;
    cout << "   Explicacion: Visita subarbol izq, luego raiz, luego subarbol der" << endl;
    
    cout << "\n3. ORDEN POSTERIOR (PostOrder: Izq-Der-Raiz):" << endl;
    cout << "   Orden: ";
    postorden(raiz);
    cout << endl;
    cout << "   Explicacion: Visita subarbol izq, luego subarbol der, luego raiz" << endl;
    
    cout << "\n4. ORDEN DE NIVEL (Level Order: por niveles):" << endl;
    cout << "   Orden: ";
    porNiveles(raiz);
    cout << endl;
    cout << "   Explicacion: Visita los nodos nivel por nivel (BFS)" << endl;
    
    cout << "\n============================================================" << endl;
    cout << "  COMPARACION DE RECORRIDOS" << endl;
    cout << "============================================================" << endl;
    
    cout << "\nNIVEL 0 (Raiz):     O" << endl;
    cout << "NIVEL 1:            C, M" << endl;
    cout << "NIVEL 2:            A, O, P, L" << endl;
    cout << "NIVEL 3:            R, B, L, E, T, O" << endl;
    
    cout << "\n============================================================" << endl;
    cout << "  CARACTERISTICAS DE CADA RECORRIDO" << endl;
    cout << "============================================================" << endl;
    
    cout << "\nPREORDEN (Raiz-Izq-Der):" << endl;
    cout << "  - Util para copiar arboles" << endl;
    cout << "  - Usado en expresiones prefijas (notacion polaca)" << endl;
    cout << "  - La raiz se visita PRIMERO" << endl;
    
    cout << "\nINORDEN (Izq-Raiz-Der):" << endl;
    cout << "  - En BST da elementos en ORDEN ASCENDENTE" << endl;
    cout << "  - Usado en expresiones infijas" << endl;
    cout << "  - La raiz se visita EN MEDIO" << endl;
    
    cout << "\nPOSTORDEN (Izq-Der-Raiz):" << endl;
    cout << "  - Util para eliminar arboles (borra hojas primero)" << endl;
    cout << "  - Usado en expresiones postfijas (RPN)" << endl;
    cout << "  - La raiz se visita AL FINAL" << endl;
    
    cout << "\nPOR NIVELES:" << endl;
    cout << "  - Recorre por anchura (BFS)" << endl;
    cout << "  - Util para arboles de decision" << endl;
    cout << "  - Requiere cola (no se puede hacer facilmente recursivo)" << endl;
    
    cout << "\n============================================================" << endl;
    
    return 0;
}