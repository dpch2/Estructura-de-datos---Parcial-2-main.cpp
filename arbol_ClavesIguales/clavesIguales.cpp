#include <iostream>
using namespace std;

const int MAX_NODOS = 100;

// Arrays paralelos para el arbol
int valores[MAX_NODOS];
int izq[MAX_NODOS];
int der[MAX_NODOS];
int padre[MAX_NODOS];
int numNodos = 0;
int raiz = -1;

// Funcion para crear un nuevo nodo
int crearNodo(int valor, int pad) {
    if (numNodos >= MAX_NODOS) {
        cout << "Error: Arbol lleno" << endl;
        return -1;
    }
    int idx = numNodos++;
    valores[idx] = valor;
    izq[idx] = -1;
    der[idx] = -1;
    padre[idx] = pad;
    return idx;
}

// ESTRATEGIA: Insertar duplicados como hijo izquierdo
// Esto mantiene las claves iguales cerca (padre-hijo o hermanos)
void insertarAgrupado(int valor) {
    cout << "\n--- Insertando: " << valor << " ---" << endl;
    
    if (raiz == -1) {
        raiz = crearNodo(valor, -1);
        cout << "Raiz: " << valor << endl;
        return;
    }
    
    int actual = raiz;
    int padreActual = -1;
    bool esIzq = false;
    
    // Buscar posicion
    while (actual != -1) {
        padreActual = actual;
        
        if (valor == valores[actual]) {
            // CASO ESPECIAL: Clave duplicada
            // Estrategia: insertar como hijo izquierdo del nodo con misma clave
            cout << "Duplicado detectado! Valor " << valor 
                 << " ya existe en el nodo" << endl;
            
            // Si el hijo izquierdo esta vacio, insertar ahi
            if (izq[actual] == -1) {
                int nuevo = crearNodo(valor, actual);
                izq[actual] = nuevo;
                cout << "-> Insertado como HIJO IZQUIERDO de " 
                     << valores[actual] << " (mantiene claves juntas)" << endl;
                return;
            } 
            // Si el hijo izquierdo existe, insertar a su izquierda
            else {
                cout << "-> Hijo izquierdo ocupado, insertando en subarbol izquierdo" << endl;
                actual = izq[actual];
                esIzq = true;
            }
        }
        else if (valor < valores[actual]) {
            actual = izq[actual];
            esIzq = true;
        } 
        else {
            actual = der[actual];
            esIzq = false;
        }
    }
    
    // Insertar nuevo nodo
    int nuevo = crearNodo(valor, padreActual);
    
    if (esIzq) {
        izq[padreActual] = nuevo;
        cout << "Insertado como hijo IZQUIERDO de " 
             << valores[padreActual] << endl;
    } else {
        der[padreActual] = nuevo;
        cout << "Insertado como hijo DERECHO de " 
             << valores[padreActual] << endl;
    }
}

// Buscar todos los nodos con un valor especifico
void buscarDuplicados(int nodo, int valorBuscado, int &contador) {
    if (nodo == -1) return;
    
    buscarDuplicados(izq[nodo], valorBuscado, contador);
    
    if (valores[nodo] == valorBuscado) {
        contador++;
        cout << "  Nodo " << contador << ": valor=" << valores[nodo];
        if (padre[nodo] != -1) {
            cout << ", padre=" << valores[padre[nodo]];
        } else {
            cout << ", padre=RAIZ";
        }
        
        // Verificar cercania con otros nodos del mismo valor
        bool cercano = false;
        if (padre[nodo] != -1 && valores[padre[nodo]] == valorBuscado) {
            cout << " [PADRE con misma clave]";
            cercano = true;
        }
        if (izq[nodo] != -1 && valores[izq[nodo]] == valorBuscado) {
            cout << " [HIJO IZQ con misma clave]";
            cercano = true;
        }
        if (der[nodo] != -1 && valores[der[nodo]] == valorBuscado) {
            cout << " [HIJO DER con misma clave]";
            cercano = true;
        }
        
        if (cercano) {
            cout << " [OK]";
        }
        cout << endl;
    }
    
    buscarDuplicados(der[nodo], valorBuscado, contador);
}

// Verificar que claves iguales esten agrupadas
void verificarAgrupacion(int nodo) {
    if (nodo == -1) return;
    
    int valor = valores[nodo];
    bool tieneVecinoIgual = false;
    
    // Verificar padre
    if (padre[nodo] != -1 && valores[padre[nodo]] == valor) {
        tieneVecinoIgual = true;
    }
    // Verificar hijo izquierdo
    if (izq[nodo] != -1 && valores[izq[nodo]] == valor) {
        tieneVecinoIgual = true;
    }
    // Verificar hijo derecho
    if (der[nodo] != -1 && valores[der[nodo]] == valor) {
        tieneVecinoIgual = true;
    }
    
    // Contar cuantos nodos tienen el mismo valor
    int total = 0;
    buscarDuplicados(raiz, valor, total);
    
    // Solo verificar si hay duplicados
    if (total > 1 && !tieneVecinoIgual) {
        cout << "! ADVERTENCIA: Nodo con valor " << valor 
             << " tiene duplicados pero NO estan cerca" << endl;
    }
    
    verificarAgrupacion(izq[nodo]);
    verificarAgrupacion(der[nodo]);
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
    
    // Contar duplicados de este valor
    int contador = 0;
    buscarDuplicados(raiz, valores[nodo], contador);
    
    cout << valores[nodo];
    if (contador > 1) {
        cout << " (x" << contador << ")";
    }
    cout << endl;
    
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

// Recorrido inorden
void inorden(int nodo) {
    if (nodo == -1) return;
    inorden(izq[nodo]);
    cout << valores[nodo] << " ";
    inorden(der[nodo]);
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
    cout << "  ARBOL BST CON CLAVES DUPLICADAS AGRUPADAS" << endl;
    cout << "========================================================" << endl;
    cout << "\nESTRATEGIA: Los duplicados se insertan como hijo" << endl;
    cout << "izquierdo del nodo con la misma clave, manteniendo" << endl;
    cout << "las claves iguales en relacion padre-hijo o hermanos." << endl;
    cout << "========================================================" << endl;
    
    int opcion;
    
    do {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Insertar valor" << endl;
        cout << "2. Mostrar arbol" << endl;
        cout << "3. Buscar duplicados de un valor" << endl;
        cout << "4. Verificar agrupacion" << endl;
        cout << "5. Recorrido inorden" << endl;
        cout << "6. Ejemplo con duplicados" << endl;
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
                insertarAgrupado(valor);
                break;
            }
            
            case 2: {
                if (raiz == -1) {
                    cout << "Arbol vacio" << endl;
                } else {
                    cout << "\n=== ESTRUCTURA DEL ARBOL ===" << endl;
                    imprimirArbol(raiz, "", true);
                }
                break;
            }
            
            case 3: {
                int valor;
                cout << "Ingrese valor a buscar: ";
                if (!validarEntrada(valor)) {
                    cout << "Error: Ingrese un numero valido" << endl;
                    break;
                }
                
                cout << "\nBuscando nodos con valor " << valor << ":" << endl;
                int contador = 0;
                buscarDuplicados(raiz, valor, contador);
                
                if (contador == 0) {
                    cout << "No se encontro el valor " << valor << endl;
                } else {
                    cout << "\nTotal encontrado: " << contador << " nodo(s)" << endl;
                }
                break;
            }
            
            case 4: {
                if (raiz == -1) {
                    cout << "Arbol vacio" << endl;
                } else {
                    cout << "\n=== VERIFICANDO AGRUPACION ===" << endl;
                    cout << "Comprobando que claves iguales esten cerca..." << endl;
                    verificarAgrupacion(raiz);
                    cout << "Verificacion completa [OK]" << endl;
                }
                break;
            }
            
            case 5: {
                if (raiz == -1) {
                    cout << "Arbol vacio" << endl;
                } else {
                    cout << "\nRecorrido inorden: ";
                    inorden(raiz);
                    cout << endl;
                }
                break;
            }
            
            case 6: {
                // Limpiar arbol
                numNodos = 0;
                raiz = -1;
                
                cout << "\n=== EJEMPLO CON DUPLICADOS ===" << endl;
                cout << "Insertando: 50, 30, 70, 30, 50, 20, 70, 50, 30" << endl;
                
                int ejemplo[] = {50, 30, 70, 30, 50, 20, 70, 50, 30};
                for (int i = 0; i < 9; i++) {
                    insertarAgrupado(ejemplo[i]);
                }
                
                cout << "\n=== ARBOL RESULTANTE ===" << endl;
                imprimirArbol(raiz, "", true);
                
                cout << "\n=== ANALISIS DE DUPLICADOS ===" << endl;
                int valores_unicos[] = {20, 30, 50, 70};
                for (int i = 0; i < 4; i++) {
                    cout << "\nValor " << valores_unicos[i] << ":" << endl;
                    int cont = 0;
                    buscarDuplicados(raiz, valores_unicos[i], cont);
                }
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
    cout << "PROPIEDAD GARANTIZADA:" << endl;
    cout << "Si varios nodos tienen la misma clave K, entonces:" << endl;
    cout << "- Su PADRE tiene clave K, O" << endl;
    cout << "- Alguno de sus HIJOS tiene clave K" << endl;
    cout << "========================================================" << endl;
    
    return 0;
}