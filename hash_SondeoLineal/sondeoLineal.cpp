// EJERCICIO 5
#include <iostream>
#include <cctype>
#include <cstring>
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

// ========== VALIDACIONES AGREGADAS ==========

// Función para validar y leer un número entero
bool leerEntero(int &valor) {
    char buffer[100];
    bool valido = false;
    
    while(!valido) {
        cin.getline(buffer, 100);
        
        // Verificar que no esté vacío
        if(strlen(buffer) == 0) {
            cout << "ERROR: No puede estar vacio. Ingrese un numero: ";
            continue;
        }
        
        // Verificar que todos los caracteres sean dígitos (o signo negativo al inicio)
        bool esNumero = true;
        int inicio = 0;
        
        // Permitir signo negativo al inicio
        if(buffer[0] == '-') {
            inicio = 1;
            if(strlen(buffer) == 1) {
                esNumero = false;
            }
        }
        
        for(int i = inicio; buffer[i] != '\0'; i++) {
            if(!isdigit(buffer[i])) {
                esNumero = false;
                break;
            }
        }
        
        if(!esNumero) {
            cout << "ERROR: Debe ingresar solo numeros enteros. Intente nuevamente: ";
            continue;
        }
        
        // Convertir string a entero
        valor = 0;
        int signo = 1;
        inicio = 0;
        
        if(buffer[0] == '-') {
            signo = -1;
            inicio = 1;
        }
        
        for(int i = inicio; buffer[i] != '\0'; i++) {
            valor = valor * 10 + (buffer[i] - '0');
        }
        valor *= signo;
        
        valido = true;
    }
    
    return true;
}

// Función para validar opción del menú
bool leerOpcionMenu(int &opcion) {
    char buffer[100];
    bool valido = false;
    
    while(!valido) {
        cin.getline(buffer, 100);
        
        // Verificar que no esté vacío
        if(strlen(buffer) == 0) {
            cout << "ERROR: Debe ingresar una opcion. Intente nuevamente: ";
            continue;
        }
        
        // Verificar que sea un solo dígito entre 0-4
        if(strlen(buffer) == 1 && isdigit(buffer[0])) {
            opcion = buffer[0] - '0';
            if(opcion >= 0 && opcion <= 4) {
                valido = true;
            } else {
                cout << "ERROR: Opcion invalida. Debe ser entre 0 y 4. Intente nuevamente: ";
            }
        } else {
            cout << "ERROR: Debe ingresar un numero entre 0 y 4. Intente nuevamente: ";
        }
    }
    
    return true;
}

// ========== FIN VALIDACIONES ==========

// INSERTAR con sondeo lineal
bool insertar(int clave) {
    // VALIDACION AGREGADA: no permitir valores reservados
    if(clave == VACIO || clave == BORRADO) {
        cout << "\nERROR: No se pueden insertar los valores " << VACIO << " o " << BORRADO << " (reservados del sistema)\n";
        return false;
    }
    
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
    // VALIDACION AGREGADA: no buscar valores reservados
    if(clave == VACIO || clave == BORRADO) {
        cout << "\nERROR: No se pueden buscar los valores " << VACIO << " o " << BORRADO << " (reservados del sistema)\n";
        return -1;
    }
    
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
    // VALIDACION AGREGADA: no borrar valores reservados
    if(clave == VACIO || clave == BORRADO) {
        cout << "\nERROR: No se pueden borrar los valores " << VACIO << " o " << BORRADO << " (reservados del sistema)\n";
        return false;
    }
    
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
        leerOpcionMenu(opcion); // VALIDACION AGREGADA
        
        switch(opcion) {
            case 1:
                cout << "Ingrese clave a insertar: ";
                leerEntero(clave); // VALIDACION AGREGADA
                insertar(clave);
                mostrar();
                break;
            case 2:
                cout << "Ingrese clave a buscar: ";
                leerEntero(clave); // VALIDACION AGREGADA
                buscar(clave);
                break;
            case 3:
                cout << "Ingrese clave a borrar: ";
                leerEntero(clave); // VALIDACION AGREGADA
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