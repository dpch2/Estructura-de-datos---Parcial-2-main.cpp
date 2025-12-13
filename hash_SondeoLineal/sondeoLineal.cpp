// EJERCICIO 5
#include <iostream>
using namespace std;

const int TAM = 10;
const int VACIO = -1;
const int BORRADO = -2;

// Variables globales simples
int tabla[TAM];

// Función de dispersión (hash)
int funcionHash(int clave) {
    return clave % TAM;
}

// Inicializar tabla
void inicializar() {
    for(int i = 0; i < TAM; i++) {
        tabla[i] = VACIO;
    }
}

// Mostrar tabla
void mostrar() {
    cout << "\n=== TABLA DE DISPERSION ===\n";
    for(int i = 0; i < TAM; i++) {
        cout << "Posicion [" << i << "]: ";
        if(tabla[i] == VACIO) 
            cout << "VACIO";
        else if(tabla[i] == BORRADO) 
            cout << "BORRADO";
        else 
            cout << tabla[i];
        cout << endl;
    }
    cout << "===========================\n";
}

// INSERTAR con sondeo lineal
bool insertar(int clave) {
    int pos = funcionHash(clave);
    int posInicial = pos;
    int intentos = 0;
    
    cout << "\n--- INSERTANDO " << clave << " ---\n";
    cout << "Hash inicial: " << pos << endl;
    
    // Buscar posición vacía o borrada
    while(intentos < TAM) {
        cout << "Intento " << (intentos + 1) << ": Posicion " << pos;
        
        if(tabla[pos] == VACIO || tabla[pos] == BORRADO) {
            tabla[pos] = clave;
            cout << " -> INSERTADO\n";
            return true;
        }
        
        if(tabla[pos] == clave) {
            cout << " -> YA EXISTE\n";
            return false;
        }
        
        cout << " -> OCUPADA (valor: " << tabla[pos] << ")\n";
        pos = (posInicial + intentos + 1) % TAM;
        intentos++;
    }
    
    cout << "TABLA LLENA - NO SE PUDO INSERTAR\n";
    return false;
}

// BUSCAR con sondeo lineal
int buscar(int clave) {
    int pos = funcionHash(clave);
    int posInicial = pos;
    int intentos = 0;
    
    cout << "\n--- BUSCANDO " << clave << " ---\n";
    cout << "Hash inicial: " << pos << endl;
    
    while(intentos < TAM) {
        cout << "Intento " << (intentos + 1) << ": Posicion " << pos;
        
        // Si encontramos la clave
        if(tabla[pos] == clave) {
            cout << " -> ENCONTRADO\n";
            return pos;
        }
        
        // Si encontramos celda vacía, la clave no existe
        if(tabla[pos] == VACIO) {
            cout << " -> VACIO (clave no existe)\n";
            return -1;
        }
        
        // Si está borrada o tiene otra clave, seguir buscando
        cout << " -> ";
        if(tabla[pos] == BORRADO) 
            cout << "BORRADO";
        else 
            cout << "Otro valor (" << tabla[pos] << ")";
        cout << " (continuar)\n";
        
        pos = (posInicial + intentos + 1) % TAM;
        intentos++;
    }
    
    cout << "NO ENCONTRADO (tabla recorrida completa)\n";
    return -1;
}

// BORRAR con sondeo lineal
bool borrar(int clave) {
    int pos = funcionHash(clave);
    int posInicial = pos;
    int intentos = 0;
    
    cout << "\n--- BORRANDO " << clave << " ---\n";
    cout << "Hash inicial: " << pos << endl;
    
    while(intentos < TAM) {
        cout << "Intento " << (intentos + 1) << ": Posicion " << pos;
        
        // Si encontramos la clave
        if(tabla[pos] == clave) {
            tabla[pos] = BORRADO;
            cout << " -> BORRADO\n";
            return true;
        }
        
        // Si encontramos celda vacía, la clave no existe
        if(tabla[pos] == VACIO) {
            cout << " -> VACIO (clave no existe)\n";
            return false;
        }
        
        // Si está borrada o tiene otra clave, seguir buscando
        cout << " -> ";
        if(tabla[pos] == BORRADO) 
            cout << "BORRADO";
        else 
            cout << "Otro valor (" << tabla[pos] << ")";
        cout << " (continuar)\n";
        
        pos = (posInicial + intentos + 1) % TAM;
        intentos++;
    }
    
    cout << "NO ENCONTRADO (tabla recorrida completa)\n";
    return false;
}

int main() {
    inicializar();
    int opcion, clave;
    
    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Insertar clave\n";
        cout << "2. Buscar clave\n";
        cout << "3. Borrar clave\n";
        cout << "4. Mostrar tabla\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                cout << "Ingrese clave a insertar: ";
                cin >> clave;
                insertar(clave);
                mostrar();
                break;
            case 2:
                cout << "Ingrese clave a buscar: ";
                cin >> clave;
                buscar(clave);
                break;
            case 3:
                cout << "Ingrese clave a borrar: ";
                cin >> clave;
                borrar(clave);
                mostrar();
                break;
            case 4:
                mostrar();
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
        }
    } while(opcion != 0);
    
    return 0;
}