#include <iostream>
using namespace std;

const int MAX_NODOS = 100;

// Arrays paralelos para representar el arbol
int valores[MAX_NODOS];
int izq[MAX_NODOS];
int der[MAX_NODOS];
int numNodos = 0;
int raiz = -1;

// Funcion para crear un nuevo nodo
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

// Funcion para obtener el maximo de dos numeros
int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// *** FUNCION RECURSIVA PARA CALCULAR LA ALTURA ***
int calcularAltura(int nodo) {
    // Caso base: arbol vacio tiene altura -1
    // (algunos autores usan 0, aqui usamos -1 para que un nodo hoja tenga altura 0)
    if (nodo == -1) {
        return -1;
    }
    
    // Caso recursivo: altura = 1 + max(altura_izq, altura_der)
    int alturaIzq = calcularAltura(izq[nodo]);
    int alturaDer = calcularAltura(der[nodo]);
    
    return 1 + maximo(alturaIzq, alturaDer);
}

// Funcion recursiva auxiliar para mostrar el proceso
int calcularAlturaConProceso(int nodo, int nivel) {
    if (nodo == -1) {
        return -1;
    }
    
    // Mostrar el proceso
    for (int i = 0; i < nivel; i++) cout << "  ";
    cout << "-> Nodo " << valores[nodo] << " (nivel " << nivel << ")" << endl;
    
    int alturaIzq = calcularAlturaConProceso(izq[nodo], nivel + 1);
    int alturaDer = calcularAlturaConProceso(der[nodo], nivel + 1);
    
    int alturaActual = 1 + maximo(alturaIzq, alturaDer);
    
    for (int i = 0; i < nivel; i++) cout << "  ";
    cout << "<- Altura del nodo " << valores[nodo] << " = " << alturaActual << endl;
    
    return alturaActual;
}

// Insertar nodo en arbol binario de busqueda
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
        cout << valor << " insertado a la izquierda de " << valores[padre] << endl;
    } else {
        der[padre] = nuevo;
        cout << valor << " insertado a la derecha de " << valores[padre] << endl;
    }
}

// Imprimir arbol visual - SOLO ASCII
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

// Contar nodos (recursivo)
int contarNodos(int nodo) {
    if (nodo == -1) return 0;
    return 1 + contarNodos(izq[nodo]) + contarNodos(der[nodo]);
}

// Validar entrada numerica
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
    cout << "================================================" << endl;
    cout << "  CALCULO DE ALTURA DE ARBOL BINARIO (RECURSIVO)" << endl;
    cout << "================================================" << endl;
    
    int opcion;
    
    do {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Insertar nodo" << endl;
        cout << "2. Calcular altura (simple)" << endl;
        cout << "3. Calcular altura (con proceso)" << endl;
        cout << "4. Mostrar arbol" << endl;
        cout << "5. Ejemplo predefinido" << endl;
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
                break;
            }
            
            case 2: {
                if (raiz == -1) {
                    cout << "Arbol vacio. Altura = -1" << endl;
                } else {
                    int altura = calcularAltura(raiz);
                    cout << "\n=== RESULTADO ===" << endl;
                    cout << "Altura del arbol: " << altura << endl;
                    cout << "Numero de nodos: " << contarNodos(raiz) << endl;
                    cout << "Distancia maxima raiz-hoja: " << altura << " aristas" << endl;
                }
                break;
            }
            
            case 3: {
                if (raiz == -1) {
                    cout << "Arbol vacio. Altura = -1" << endl;
                } else {
                    cout << "\n=== PROCESO RECURSIVO ===" << endl;
                    int altura = calcularAlturaConProceso(raiz, 0);
                    cout << "\n=== RESULTADO FINAL ===" << endl;
                    cout << "Altura del arbol: " << altura << endl;
                }
                break;
            }
            
            case 4: {
                if (raiz == -1) {
                    cout << "Arbol vacio" << endl;
                } else {
                    cout << "\n=== ESTRUCTURA DEL ARBOL ===" << endl;
                    imprimirArbol(raiz, "", true);
                    cout << "\nNodos: " << contarNodos(raiz) << endl;
                    cout << "Altura: " << calcularAltura(raiz) << endl;
                }
                break;
            }
            
            case 5: {
                // Limpiar arbol actual
                numNodos = 0;
                raiz = -1;
                
                cout << "\nCreando arbol de ejemplo..." << endl;
                cout << "Insertando: 50, 30, 70, 20, 40, 60, 80, 10, 25" << endl;
                cout << "\n";
                
                int ejemplo[] = {50, 30, 70, 20, 40, 60, 80, 10, 25};
                for (int i = 0; i < 9; i++) {
                    insertar(ejemplo[i]);
                }
                
                cout << "\n=== ARBOL GENERADO ===" << endl;
                imprimirArbol(raiz, "", true);
                
                int altura = calcularAltura(raiz);
                cout << "\nAltura del arbol: " << altura << endl;
                break;
            }
            
            case 0:
                cout << "Saliendo..." << endl;
                break;
                
            default:
                cout << "Opcion invalida" << endl;
        }
        
    } while (opcion != 0);
    
    cout << "\n================================================" << endl;
    cout << "DEFINICION DE ALTURA:" << endl;
    cout << "- Arbol vacio: altura = -1" << endl;
    cout << "- Nodo hoja: altura = 0" << endl;
    cout << "- Nodo interno: altura = 1 + max(altura_izq, altura_der)" << endl;
    cout << "- La altura es el numero de ARISTAS en el camino mas largo" << endl;
    cout << "================================================" << endl;
    
    return 0;
}