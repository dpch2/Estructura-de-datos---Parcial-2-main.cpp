#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_NODOS = 50;
const bool ROJO = true;
const bool NEGRO = false;

// Arrays paralelos para simular nodos
char claves[MAX_NODOS];
bool colores[MAX_NODOS];
int izq[MAX_NODOS];
int der[MAX_NODOS];
int padre[MAX_NODOS];
int numNodos = 0;
int raiz = -1;

// Función para crear un nuevo nodo
int crearNodo(char clave, bool color, int p) {
    if (numNodos >= MAX_NODOS) {
        cout << "Error: Arbol lleno" << endl;
        return -1;
    }
    int idx = numNodos++;
    claves[idx] = clave;
    colores[idx] = color;
    izq[idx] = -1;
    der[idx] = -1;
    padre[idx] = p;
    return idx;
}

// Obtener color de un nodo (negro si es null)
bool obtenerColor(int nodo) {
    return (nodo == -1) ? NEGRO : colores[nodo];
}

// Rotación izquierda
void rotarIzq(int x) {
    if (x == -1 || der[x] == -1) return;
    
    int y = der[x];
    der[x] = izq[y];
    
    if (izq[y] != -1) {
        padre[izq[y]] = x;
    }
    
    padre[y] = padre[x];
    
    if (padre[x] == -1) {
        raiz = y;
    } else if (x == izq[padre[x]]) {
        izq[padre[x]] = y;
    } else {
        der[padre[x]] = y;
    }
    
    izq[y] = x;
    padre[x] = y;
}

// Rotación derecha
void rotarDer(int y) {
    if (y == -1 || izq[y] == -1) return;
    
    int x = izq[y];
    izq[y] = der[x];
    
    if (der[x] != -1) {
        padre[der[x]] = y;
    }
    
    padre[x] = padre[y];
    
    if (padre[y] == -1) {
        raiz = x;
    } else if (y == der[padre[y]]) {
        der[padre[y]] = x;
    } else {
        izq[padre[y]] = x;
    }
    
    der[x] = y;
    padre[y] = x;
}

// Balancear después de inserción
void balancearInsercion(int k) {
    while (k != raiz && obtenerColor(padre[k]) == ROJO) {
        int p = padre[k];
        int abuelo = padre[p];
        
        if (abuelo == -1) break;
        
        if (p == izq[abuelo]) {
            int tio = der[abuelo];
            
            if (obtenerColor(tio) == ROJO) {
                // Caso 1: Tío rojo
                colores[p] = NEGRO;
                colores[tio] = NEGRO;
                colores[abuelo] = ROJO;
                k = abuelo;
            } else {
                if (k == der[p]) {
                    // Caso 2: Nodo es hijo derecho
                    k = p;
                    rotarIzq(k);
                    p = padre[k];
                    abuelo = padre[p];
                }
                // Caso 3: Nodo es hijo izquierdo
                colores[p] = NEGRO;
                if (abuelo != -1) {
                    colores[abuelo] = ROJO;
                    rotarDer(abuelo);
                }
            }
        } else {
            int tio = izq[abuelo];
            
            if (obtenerColor(tio) == ROJO) {
                // Caso 1: Tío rojo
                colores[p] = NEGRO;
                colores[tio] = NEGRO;
                colores[abuelo] = ROJO;
                k = abuelo;
            } else {
                if (k == izq[p]) {
                    // Caso 2: Nodo es hijo izquierdo
                    k = p;
                    rotarDer(k);
                    p = padre[k];
                    abuelo = padre[p];
                }
                // Caso 3: Nodo es hijo derecho
                colores[p] = NEGRO;
                if (abuelo != -1) {
                    colores[abuelo] = ROJO;
                    rotarIzq(abuelo);
                }
            }
        }
    }
    colores[raiz] = NEGRO;
}

// Insertar nodo
void insertar(char clave) {
    int z = crearNodo(clave, ROJO, -1);
    if (z == -1) return;
    
    cout << "\n--- Insertando: " << clave << " ---" << endl;
    
    if (raiz == -1) {
        raiz = z;
        colores[raiz] = NEGRO;
        cout << "Primera insercion - raiz es " << clave << " (NEGRO)" << endl;
        return;
    }
    
    int actual = raiz;
    int padreActual = -1;
    
    while (actual != -1) {
        padreActual = actual;
        if (clave < claves[actual]) {
            actual = izq[actual];
        } else if (clave > claves[actual]) {
            actual = der[actual];
        } else {
            numNodos--;
            cout << "Clave duplicada, no se inserta" << endl;
            return;
        }
    }
    
    padre[z] = padreActual;
    if (clave < claves[padreActual]) {
        izq[padreActual] = z;
        cout << clave << " insertado como hijo IZQ de " << claves[padreActual] << " (ROJO)" << endl;
    } else {
        der[padreActual] = z;
        cout << clave << " insertado como hijo DER de " << claves[padreActual] << " (ROJO)" << endl;
    }
    
    if (obtenerColor(padreActual) == ROJO) {
        cout << "Conflicto ROJO-ROJO detectado, balanceando..." << endl;
        balancearInsercion(z);
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
    
    cout << claves[nodo] << (colores[nodo] == ROJO ? "(R)" : "(N)") << endl;
    
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

int main() {
    cout << "=== ARBOL ROJO-NEGRO: INSERCION DE A HASTA K ===" << endl;
    cout << "================================================" << endl;
    
    // Insertar letras de A a K
    for (char c = 'A'; c <= 'K'; c++) {
        insertar(c);
        
        cout << "\nArbol actual:" << endl;
        imprimirArbol(raiz, "", true);
        cout << "------------------------------------------------" << endl;
    }
    
    cout << "\n=== ANALISIS GENERAL ===" << endl;
    cout << "\nAl insertar claves en ORDEN ASCENDENTE en un arbol rojo-negro:" << endl;
    cout << "1. Sin balanceo, se formaria una lista enlazada (peor caso O(n))" << endl;
    cout << "2. El arbol rojo-negro realiza ROTACIONES y RECOLOREOS automaticos" << endl;
    cout << "3. Mantiene altura balanceada: h <= 2*log2(n+1)" << endl;
    cout << "4. Cada insercion puede causar hasta O(log n) rotaciones" << endl;
    cout << "5. Resultado: arbol balanceado con busqueda O(log n)" << endl;
    
    cout << "\n=== ARBOL FINAL ===" << endl;
    imprimirArbol(raiz, "", true);
    
    return 0;
}