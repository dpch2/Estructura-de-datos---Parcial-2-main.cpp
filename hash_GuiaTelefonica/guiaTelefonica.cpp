//EJERCICIO 10
#include <iostream>
#include <string>
using namespace std;

const int TAMANO = 10;

// Variables globales para la tabla hash
int telefonos[TAMANO];
string nombres[TAMANO];
string apellidos[TAMANO];
string direcciones[TAMANO];
bool ocupado[TAMANO];

// Inicializar tabla
void inicializar() {
    for (int i = 0; i < TAMANO; i++) {
        ocupado[i] = false;
        telefonos[i] = 0;
        nombres[i] = "";
        apellidos[i] = "";
        direcciones[i] = "";
    }
}

// Función hash simple
int funcionHash(int telefono) {
    return telefono % TAMANO;
}

// Insertar contacto
void insertar() {
    int telefono;
    string nombre, apellido, direccion;
    
    cout << "\n--- INSERTAR CONTACTO ---" << endl;
    cout << "Telefono: ";
    cin >> telefono;
    cin.ignore();
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Apellido: ";
    getline(cin, apellido);
    cout << "Direccion: ";
    getline(cin, direccion);
    
    int indice = funcionHash(telefono);
    int intentos = 0;
    
    // Buscar posición libre (sondeo lineal)
    while (ocupado[indice] && intentos < TAMANO) {
        indice = (indice + 1) % TAMANO;
        intentos++;
    }
    
    if (intentos == TAMANO) {
        cout << "ERROR: Tabla llena" << endl;
        return;
    }
    
    // Guardar datos
    telefonos[indice] = telefono;
    nombres[indice] = nombre;
    apellidos[indice] = apellido;
    direcciones[indice] = direccion;
    ocupado[indice] = true;
    
    cout << "Contacto guardado en posicion: " << indice << endl;
}

// Buscar contacto
void buscar() {
    int telefono;
    cout << "\n--- BUSCAR CONTACTO ---" << endl;
    cout << "Telefono a buscar: ";
    cin >> telefono;
    
    int indice = funcionHash(telefono);
    int intentos = 0;
    
    // Buscar el teléfono
    while (intentos < TAMANO) {
        if (ocupado[indice] && telefonos[indice] == telefono) {
            cout << "\nCONTACTO ENCONTRADO:" << endl;
            cout << "Posicion: " << indice << endl;
            cout << "Telefono: " << telefonos[indice] << endl;
            cout << "Nombre: " << nombres[indice] << endl;
            cout << "Apellido: " << apellidos[indice] << endl;
            cout << "Direccion: " << direcciones[indice] << endl;
            return;
        }
        indice = (indice + 1) % TAMANO;
        intentos++;
    }
    
    cout << "Contacto NO encontrado" << endl;
}

// Mostrar toda la tabla
void mostrarTodo() {
    cout << "\n--- TABLA HASH COMPLETA ---" << endl;
    for (int i = 0; i < TAMANO; i++) {
        cout << "Posicion " << i << ": ";
        if (ocupado[i]) {
            cout << telefonos[i] << " - " << nombres[i] 
                 << " " << apellidos[i] << endl;
        } else {
            cout << "[VACIO]" << endl;
        }
    }
}

// Eliminar contacto
void eliminar() {
    int telefono;
    cout << "\n--- ELIMINAR CONTACTO ---" << endl;
    cout << "Telefono a eliminar: ";
    cin >> telefono;
    
    int indice = funcionHash(telefono);
    int intentos = 0;
    
    while (intentos < TAMANO) {
        if (ocupado[indice] && telefonos[indice] == telefono) {
            ocupado[indice] = false;
            cout << "Contacto eliminado de la posicion: " << indice << endl;
            return;
        }
        indice = (indice + 1) % TAMANO;
        intentos++;
    }
    
    cout << "Contacto NO encontrado" << endl;
}

int main() {
    inicializar();
    int opcion;
    
    do {
        cout << "\n========== GUIA TELEFONICA ==========" << endl;
        cout << "1. Insertar contacto" << endl;
        cout << "2. Buscar contacto" << endl;
        cout << "3. Eliminar contacto" << endl;
        cout << "4. Mostrar tabla completa" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: insertar(); break;
            case 2: buscar(); break;
            case 3: eliminar(); break;
            case 4: mostrarTodo(); break;
            case 0: cout << "Saliendo..." << endl; break;
            default: cout << "Opcion invalida" << endl;
        }
    } while (opcion != 0);
    
    return 0;
}