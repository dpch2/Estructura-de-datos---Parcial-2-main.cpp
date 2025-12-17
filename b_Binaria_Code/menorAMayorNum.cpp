#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int TAMANO = 10;

// Estructuras de datos (Arrays paralelos)
int telefonos[TAMANO];
string nombres[TAMANO];
string apellidos[TAMANO];
string direcciones[TAMANO];
bool ocupado[TAMANO];

// --- VALIDACION DE ENTRADA ---
int leerEntero(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        } else {
            cout << " [!] Error: Ingrese un numero valido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Inicializar tabla
void inicializar() {
    for (int i = 0; i < TAMANO; i++) {
        ocupado[i] = false;
    }
}

int funcionHash(int telefono) {
    return telefono % TAMANO;
}

void insertar() {
    cout << "\n--- NUEVO CONTACTO ---" << endl;
    int tel = leerEntero(" > Telefono: ");
    string nom, ape, dir;
    
    cout << " > Nombre: "; getline(cin, nom);
    cout << " > Apellido: "; getline(cin, ape);
    cout << " > Direccion: "; getline(cin, dir);
    
    int indice = funcionHash(tel);
    int intentos = 0;
    
    // Sondeo lineal para encontrar espacio o actualizar
    while (ocupado[indice] && telefonos[indice] != tel && intentos < TAMANO) {
        indice = (indice + 1) % TAMANO;
        intentos++;
    }
    
    if (intentos == TAMANO) {
        cout << "\n [!] ERROR: La memoria de la guia esta llena." << endl;
        return;
    }
    
    telefonos[indice] = tel;
    nombres[indice] = nom;
    apellidos[indice] = ape;
    direcciones[indice] = dir;
    ocupado[indice] = true;
    
    cout << " [+] Guardado exitosamente en indice: " << indice << endl;
}

void buscar() {
    cout << "\n--- BUSQUEDA DE CONTACTO ---" << endl;
    int tel = leerEntero(" > Ingrese numero a buscar: ");
    
    int indice = funcionHash(tel);
    int intentos = 0;
    
    while (intentos < TAMANO) {
        if (ocupado[indice] && telefonos[indice] == tel) {
            cout << "\n========================================" << endl;
            cout << " CONTACTO ENCONTRADO EN INDICE " << indice << endl;
            cout << "========================================" << endl;
            cout << " Nombre:    " << nombres[indice] << " " << apellidos[indice] << endl;
            cout << " Telefono:  " << telefonos[indice] << endl;
            cout << " Direccion: " << direcciones[indice] << endl;
            return;
        }
        indice = (indice + 1) % TAMANO;
        intentos++;
    }
    cout << " [!] El contacto no existe en la guia." << endl;
}

void mostrarTodo() {
    cout << "\n========== VISTA DE LA TABLA HASH ==========" << endl;
    cout << "IND\t| ESTADO\t| DATOS" << endl;
    cout << "--------------------------------------------" << endl;
    for (int i = 0; i < TAMANO; i++) {
        cout << " [" << i << "]\t| ";
        if (ocupado[i]) {
            cout << "OCUPADO\t| " << telefonos[i] << " - " << nombres[i] << endl;
        } else {
            cout << "VACIO\t| ----" << endl;
        }
    }
}

void eliminar() {
    cout << "\n--- ELIMINAR REGISTRO ---" << endl;
    int tel = leerEntero(" > Numero a borrar: ");
    
    int indice = funcionHash(tel);
    int intentos = 0;
    
    while (intentos < TAMANO) {
        if (ocupado[indice] && telefonos[indice] == tel) {
            ocupado[indice] = false;
            cout << " [-] Contacto eliminado de la posicion " << indice << endl;
            return;
        }
        indice = (indice + 1) % TAMANO;
        intentos++;
    }
    cout << " [!] No se encontro el numero para eliminar." << endl;
}

int main() {
    inicializar();
    int opcion;
    
    do {
        cout << "\n========================================" << endl;
        cout << "        SISTEMA HASH: TELEFONOS         " << endl;
        cout << "========================================" << endl;
        cout << " 1. [ + ] Insertar Contacto" << endl;
        cout << " 2. [ ? ] Buscar por Telefono" << endl;
        cout << " 3. [ - ] Eliminar Contacto" << endl;
        cout << " 4. [ L ] Listar Tabla Hash" << endl;
        cout << " 0. [ X ] Salir" << endl;
        cout << "----------------------------------------" << endl;
        opcion = leerEntero(" >> Seleccione una opcion: ");
        
        switch(opcion) {
            case 1: insertar(); break;
            case 2: buscar(); break;
            case 3: eliminar(); break;
            case 4: mostrarTodo(); break;
            case 0: cout << "Cerrando sistema..." << endl; break;
            default: cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
    
    return 0;
}