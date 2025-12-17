#include <iostream>
#include <cstdlib>
using namespace std;

// Mapeo de letras a numeros para ordenamiento
int letraANumero(char c) {
    switch(c) {
        case 'B': return 1;
        case 'D': return 2;
        case 'E': return 3;
        case 'J': return 4;
        case 'L': return 5;
        case 'M': return 6;
        case 'O': return 7;
        case 'P': return 8;
        case 'U': return 9;
        default: return 0;
    }
}

// Clase Nodo simple
class Nodo {
public:
    char datos[3];
    int numDatos;
    Nodo* hijos[4];
    
    Nodo() {
        numDatos = 0;
        for (int i = 0; i < 4; i++)
            hijos[i] = NULL;
        for (int i = 0; i < 3; i++)
            datos[i] = '\0';
    }
    
    bool esHoja() {
        return hijos[0] == NULL;
    }
    
    bool estaLleno() {
        return numDatos == 3;
    }
    
    void insertarDato(char valor) {
        int valorNum = letraANumero(valor);
        int i = numDatos - 1;
        
        while (i >= 0 && valorNum < letraANumero(datos[i])) {
            datos[i + 1] = datos[i];
            i--;
        }
        datos[i + 1] = valor;
        numDatos++;
    }
};

// Clase ArbolBPlus simple
class ArbolBPlus {
private:
    Nodo* raiz;
    
    // Dividir hijo lleno del padre en posicion idx
    void dividirHijo(Nodo* padre, int idx) {
        Nodo* hijoLleno = padre->hijos[idx];
        Nodo* nuevoHijo = new Nodo();
        
        // Dato medio sube al padre
        char medio = hijoLleno->datos[1];
        
        // Nuevo hijo recibe el ultimo dato
        nuevoHijo->datos[0] = hijoLleno->datos[2];
        nuevoHijo->numDatos = 1;
        
        // Si tiene hijos, redistribuir
        if (!hijoLleno->esHoja()) {
            nuevoHijo->hijos[0] = hijoLleno->hijos[2];
            nuevoHijo->hijos[1] = hijoLleno->hijos[3];
            hijoLleno->hijos[2] = NULL;
            hijoLleno->hijos[3] = NULL;
        }
        
        // Hijo lleno se queda solo con primer dato
        hijoLleno->numDatos = 1;
        
        // Insertar medio en padre y ajustar punteros
        for (int i = padre->numDatos; i > idx; i--) {
            padre->datos[i] = padre->datos[i - 1];
            padre->hijos[i + 1] = padre->hijos[i];
        }
        
        padre->datos[idx] = medio;
        padre->hijos[idx + 1] = nuevoHijo;
        padre->numDatos++;
    }
    
    // Insertar en subarbol con raiz x (no lleno)
    void insertarNoLleno(Nodo* x, char k) {
        int i = x->numDatos - 1;
        int kNum = letraANumero(k);
        
        if (x->esHoja()) {
            // Insertar en hoja
            x->insertarDato(k);
        } else {
            // Encontrar hijo donde va k
            while (i >= 0 && kNum < letraANumero(x->datos[i]))
                i--;
            i++;
            
            // Si hijo esta lleno, dividir primero
            if (x->hijos[i]->estaLleno()) {
                dividirHijo(x, i);
                
                // Despues de dividir, k puede ir al nuevo hijo
                if (kNum > letraANumero(x->datos[i]))
                    i++;
            }
            
            insertarNoLleno(x->hijos[i], k);
        }
    }
    
    void imprimirNivel(Nodo* nodo, int nivel, int actual) {
        if (nodo == NULL)
            return;
        
        if (actual == nivel) {
            cout << "[";
            for (int i = 0; i < nodo->numDatos; i++) {
                cout << nodo->datos[i];
                if (i < nodo->numDatos - 1)
                    cout << " ";
            }
            cout << "] ";
        } else {
            for (int i = 0; i <= nodo->numDatos; i++) {
                imprimirNivel(nodo->hijos[i], nivel, actual + 1);
            }
        }
    }
    
    int altura(Nodo* nodo) {
        if (nodo == NULL)
            return 0;
        if (nodo->esHoja())
            return 1;
        return 1 + altura(nodo->hijos[0]);
    }
    
    void imprimirVisual(Nodo* nodo, int nivel, string prefijo, bool ultimo) {
        if (nodo == NULL)
            return;
        
        cout << prefijo;
        
        if (nivel > 0)
            cout << (ultimo ? "+-- " : "|-- ");
        
        cout << "[";
        for (int i = 0; i < nodo->numDatos; i++) {
            cout << nodo->datos[i];
            if (i < nodo->numDatos - 1)
                cout << " ";
        }
        cout << "]";
        
        if (nodo->esHoja())
            cout << " (hoja)";
        
        cout << endl;
        
        if (!nodo->esHoja()) {
            string nuevo = prefijo + (nivel > 0 ? (ultimo ? "    " : "|   ") : "");
            
            for (int i = 0; i <= nodo->numDatos; i++) {
                if (nodo->hijos[i])
                    imprimirVisual(nodo->hijos[i], nivel + 1, nuevo, i == nodo->numDatos);
            }
        }
    }
    
    void borrarArbol(Nodo* nodo) {
        if (nodo == NULL)
            return;
        
        // Borrar todos los hijos recursivamente
        if (!nodo->esHoja()) {
            for (int i = 0; i <= nodo->numDatos; i++) {
                borrarArbol(nodo->hijos[i]);
            }
        }
        
        delete nodo;
    }
    
public:
    ArbolBPlus() {
        raiz = new Nodo();
    }
    
    ~ArbolBPlus() {
        borrarArbol(raiz);
    }
    
    void limpiar() {
        borrarArbol(raiz);
        raiz = new Nodo();
        cout << "\n*** Arbol borrado completamente ***\n" << endl;
    }
    
    void insertar(char k) {
        Nodo* r = raiz;
        
        if (r->estaLleno()) {
            // Crear nueva raiz
            Nodo* s = new Nodo();
            raiz = s;
            s->hijos[0] = r;
            
            // Dividir vieja raiz
            dividirHijo(s, 0);
            
            // Insertar en nueva estructura
            insertarNoLleno(s, k);
        } else {
            insertarNoLleno(r, k);
        }
    }
    
    void imprimir() {
        if (!raiz) {
            cout << "Arbol vacio" << endl;
            return;
        }
        
        int h = altura(raiz);
        
        cout << "\nArbol B+ (altura: " << h << " niveles)\n" << endl;
        
        for (int i = 1; i <= h; i++) {
            cout << "Nivel " << i << ": ";
            imprimirNivel(raiz, i, 1);
            cout << endl;
        }
        
        cout << "\nEstructura visual:" << endl;
        imprimirVisual(raiz, 0, "", true);
        cout << endl;
    }
};

int leerOpcion() {
    char entrada[100];
    cin >> entrada;
    
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (entrada[i] < '0' || entrada[i] > '9')
            return -1;
    }
    
    return atoi(entrada);
}

char leerLetra() {
    char entrada[100];
    cin >> entrada;
    
    if (entrada[0] >= 'A' && entrada[0] <= 'Z' && entrada[1] == '\0')
        return entrada[0];
    if (entrada[0] >= 'a' && entrada[0] <= 'z' && entrada[1] == '\0')
        return entrada[0] - 32;
    
    return '\0';
}

int main() {
    ArbolBPlus arbol;
    
    char secuencia[] = {'E', 'E', 'E', 'O', 'M', 'P', 'J', 'B', 'U', 'L', 'D'};
    int total = 11;
    int actual = 0;
    
    cout << "\n============================================" << endl;
    cout << "  ARBOL B+ (2-3-4) - FIGURA 15.1" << endl;
    cout << "============================================\n" << endl;
    cout << "Objetivo: [E M] / [B D E] [E J L] [O P U]" << endl;
    cout << "\nMapeo: B=1, D=2, E=3, J=4, L=5, M=6, O=7, P=8, U=9" << endl;
    cout << "Secuencia: E E E O M P J B U L D\n" << endl;
    
    while (actual < total) {
        cout << "--- Menu ---" << endl;
        cout << "Insertar: " << secuencia[actual];
        cout << " (val=" << letraANumero(secuencia[actual]) << ")";
        
        int contE = 0;
        for (int i = 0; i < actual; i++)
            if (secuencia[i] == 'E')
                contE++;
        if (secuencia[actual] == 'E')
            cout << " [E#" << (contE + 1) << "]";
        
        cout << " - " << actual << "/" << total << endl;
        cout << "1. Insertar\n2. Ver arbol\n3. Insertar manual\n4. Borrar arbol\n5. Salir" << endl;
        cout << "Opcion: ";
        
        int op = leerOpcion();
        
        if (op == -1) {
            cout << "\nError: solo numeros\n" << endl;
            continue;
        }
        
        switch (op) {
            case 1: {
                char letra = secuencia[actual];
                cout << "\n>>> Insertando " << letra << " (" << letraANumero(letra) << ")\n";
                arbol.insertar(letra);
                arbol.imprimir();
                actual++;
                
                if (actual >= total) {
                    cout << "========================================" << endl;
                    cout << "¡ARBOL COMPLETO!" << endl;
                    cout << "========================================\n" << endl;
                    arbol.imprimir();
                }
                break;
            }
            case 2:
                arbol.imprimir();
                break;
            case 3: {
                cout << "Letra: ";
                char l = leerLetra();
                if (l == '\0' || letraANumero(l) == 0) {
                    cout << "Error: letra invalida\n" << endl;
                    break;
                }
                cout << "\n>>> Insertando " << l << " (" << letraANumero(l) << ")\n";
                arbol.insertar(l);
                arbol.imprimir();
                break;
            }
            case 4: {
                cout << "\n¿Seguro que desea borrar el arbol? (S/N): ";
                char confirma;
                cin >> confirma;
                if (confirma == 'S' || confirma == 's') {
                    arbol.limpiar();
                    actual = 0;
                    cout << "Puede comenzar la secuencia nuevamente." << endl;
                } else {
                    cout << "Operacion cancelada." << endl;
                }
                break;
            }
            case 5:
                cout << "Saliendo..." << endl;
                return 0;
            default:
                cout << "Opcion invalida\n" << endl;
        }
    }
    
    while (true) {
        cout << "--- Menu Final ---" << endl;
        cout << "1. Ver arbol\n2. Insertar\n3. Borrar arbol\n4. Salir" << endl;
        cout << "Opcion: ";
        
        int op = leerOpcion();
        
        if (op == -1) {
            cout << "Error: solo numeros\n" << endl;
            continue;
        }
        
        switch (op) {
            case 1:
                arbol.imprimir();
                break;
            case 2: {
                cout << "Letra: ";
                char l = leerLetra();
                if (l == '\0' || letraANumero(l) == 0) {
                    cout << "Error: letra invalida\n" << endl;
                    break;
                }
                cout << "\n>>> Insertando " << l << "\n";
                arbol.insertar(l);
                arbol.imprimir();
                break;
            }
            case 3: {
                cout << "\n¿Seguro que desea borrar el arbol? (S/N): ";
                char confirma;
                cin >> confirma;
                if (confirma == 'S' || confirma == 's') {
                    arbol.limpiar();
                    actual = 0;
                    cout << "Puede reiniciar la secuencia desde el menu principal." << endl;
                    cout << "\nVolviendo al menu principal...\n" << endl;
                    // Salir del menu final para volver al principal
                    goto menu_principal;
                } else {
                    cout << "Operacion cancelada." << endl;
                }
                break;
            }
            case 4:
                cout << "Saliendo..." << endl;
                return 0;
            default:
                cout << "Opcion invalida\n" << endl;
        }
    }
    
    menu_principal:
    // Etiqueta para volver al menu principal después de borrar
    
    return 0;
}