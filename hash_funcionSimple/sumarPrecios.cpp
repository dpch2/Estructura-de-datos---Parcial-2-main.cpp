#include <iostream>
#include <string>
#include <limits>
#include <iomanip> // Para formato de decimales en el precio

using namespace std;

// --- FUNCIONES DE VALIDACION ---
int leerEntero(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        } else {
            cout << " [!] Error: Ingrese un numero entero.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

float leerFloat(string mensaje) {
    float valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        } else {
            cout << " [!] Error: Ingrese un precio valido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void dibujarCabecera(string titulo) {
    cout << "\n====================================================" << endl;
    cout << "          " << titulo << endl;
    cout << "====================================================" << endl;
}

int main() {
    int cantidad;
    dibujarCabecera("GESTOR DE COLECCION FUNKO POP");
    cantidad = leerEntero(" > Cuantos Funko Pop vas a ingresar? ");

    int numero[100];
    string nombre[100];
    string coleccion[100];
    float precio[100];

    // 1. INGRESO DE DATOS
    for(int i = 0; i < cantidad; i++) {
        cout << "\n[ Registro #" << (i+1) << " ]" << endl;
        numero[i] = leerEntero(" -> Numero de serie: ");
        cout << " -> Nombre del personaje: ";
        getline(cin, nombre[i]);
        cout << " -> Coleccion (ej. Star Wars, Marvel): ";
        getline(cin, coleccion[i]);
        precio[i] = leerFloat(" -> Precio: $");
    }

    // 2. ORDENAMIENTO (Bubble Sort por Numero)
    for(int i = 0; i < cantidad - 1; i++) {
        for(int j = 0; j < cantidad - i - 1; j++) {
            if(numero[j] > numero[j+1]) {
                // Intercambio sincronizado de los 4 arreglos
                swap(numero[j], numero[j+1]);
                swap(nombre[j], nombre[j+1]);
                swap(coleccion[j], coleccion[j+1]);
                swap(precio[j], precio[j+1]);
            }
        }
    }

    // 3. REPORTES
    dibujarCabecera("A) INVENTARIO ORDENADO POR SERIE");
    cout << "No.\t| NOMBRE\t\t| COLECCION\t| PRECIO" << endl;
    cout << "----------------------------------------------------" << endl;
    for(int i = 0; i < cantidad; i++) {
        cout << " #" << numero[i] << "\t| " << nombre[i] << (nombre[i].length() < 8 ? "\t\t| " : "\t| ") 
             << coleccion[i] << "\t| $" << fixed << setprecision(2) << precio[i] << endl;
    }

    dibujarCabecera("B) BUSQUEDA POR COLECCION");
    string buscar;
    cout << " > Ingrese coleccion a filtrar: ";
    getline(cin, buscar);
    for(int i = 0; i < cantidad; i++) {
        if(coleccion[i] == buscar) {
            cout << " [+] " << nombre[i] << " (#" << numero[i] << ") - $" << precio[i] << endl;
        }
    }

    dibujarCabecera("C al G) FILTROS ESPECIFICOS");
    float sumaIronMan = 0;
    for(int i = 0; i < cantidad; i++) {
        // C) Star Wars 130
        if(numero[i] == 130 && coleccion[i] == "Star Wars") 
            cout << " [!] EXISTE: " << nombre[i] << " de Star Wars (#130)" << endl;
        
        // D) Numero 295
        if(numero[i] == 295) 
            cout << " [!] NUMERO 295: " << nombre[i] << " (" << coleccion[i] << ")" << endl;
            
        // E/F) Personajes Iconicos
        if(nombre[i] == "Darth Vader" || nombre[i] == "Capitana Marvel" || 
           nombre[i] == "Red Skull" || nombre[i] == "Thanos" || nombre[i] == "Galactus") {
            cout << " [!] ICONO ENCONTRADO: " << nombre[i] << " (#" << numero[i] << ")" << endl;
        }

        // G) Suma Tony Stark/Iron Man
        if(nombre[i] == "Tony Stark" || nombre[i] == "Iron Man") {
            sumaIronMan += precio[i];
        }
    }
    cout << " >> Costo total Tony Stark + Iron Man: $" << sumaIronMan << endl;

    dibujarCabecera("H) ANALISIS DE COSTOS");
    float todosSuma = 0, rocksTotal = 0, hpTotal = 0;
    for(int i = 0; i < cantidad; i++) {
        todosSuma += precio[i];
        if(coleccion[i] == "Rocks") rocksTotal += precio[i];
        if(coleccion[i] == "Harry Potter") hpTotal += precio[i];
    }
    cout << " -> Promedio general de la coleccion: $" << (cantidad > 0 ? todosSuma/cantidad : 0) << endl;
    cout << " -> Inversion total en 'Rocks': $" << rocksTotal << endl;
    cout << " -> Inversion total en 'Harry Potter': $" << hpTotal << endl;

    return 0;
}