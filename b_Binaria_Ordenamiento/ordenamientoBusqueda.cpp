#include <iostream>
#include <string>
#include <limits>

using namespace std;

// --- FUNCION DE VALIDACION PARA NUMEROS ---
int leerEntero(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        } else {
            cout << " [!] Error: Ingrese un numero entero positivo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void dibujarSeparador() {
    cout << "----------------------------------------------------" << endl;
}

int main() {
    string nombres[100], maestros[100], tipo[100];
    int total = 0;

    cout << "========================================" << endl;
    cout << "      SISTEMA DE ARCHIVOS GALACTICOS    " << endl;
    cout << "========================================" << endl;
    
    total = leerEntero(" > Cantidad de personajes a registrar: ");

    // 1. ENTRADA DE DATOS
    for(int i = 0; i < total; i++) {
        cout << "\n[ Registro #" << (i+1) << " ]" << endl;
        cout << " -> Nombre del personaje: ";
        getline(cin, nombres[i]);
        cout << " -> Maestro asignado: ";
        getline(cin, maestros[i]);
        cout << " -> Afiliacion (Jedi/Sith): ";
        getline(cin, tipo[i]);
    }

    // 2. ORDENAMIENTO BUBBLE SORT (Por Nombre)
    // Mantiene sincronizados los 3 arreglos paralelos
    for(int i = 0; i < total - 1; i++) {
        for(int j = 0; j < total - i - 1; j++) {
            if(nombres[j] > nombres[j+1]) {
                swap(nombres[j], nombres[j+1]);
                swap(maestros[j], maestros[j+1]);
                swap(tipo[j], tipo[j+1]);
            }
        }
    }

    // 3. PRESENTACION DE REPORTES
    cout << "\n\n========================================" << endl;
    cout << "       REPORTES DE LA ORDEN             " << endl;
    cout << "========================================" << endl;

    // a. Lista Completa Ordenada
    cout << "\n[A] LISTADO ALFABETICO GENERAL:" << endl;
    dibujarSeparador();
    for(int i = 0; i < total; i++) {
        cout << " " << i+1 << ". " << nombres[i] << " | Maestro: " << maestros[i] << " | (" << tipo[i] << ")" << endl;
    }

    // b y c. Filtrado por Afiliacion
    int cJedi = 0, cSith = 0;
    cout << "\n[B] MAESTROS Y APRENDICES JEDI:" << endl;
    for(int i = 0; i < total; i++) {
        if(tipo[i] == "Jedi" || tipo[i] == "jedi") {
            cout << "  - " << nombres[i] << " (Maestro: " << maestros[i] << ")" << endl;
            cJedi++;
        }
    }
    cout << " Total Jedi: " << cJedi << endl;

    cout << "\n[C] LORES Y APRENDICES SITH:" << endl;
    for(int i = 0; i < total; i++) {
        if(tipo[i] == "Sith" || tipo[i] == "sith") {
            cout << "  - " << nombres[i] << " (Maestro: " << maestros[i] << ")" << endl;
            cSith++;
        }
    }
    cout << " Total Sith: " << cSith << endl;

    // d. Busqueda de Aprendices Especificos
    cout << "\n[D] BUSQUEDA POR MAESTRO (Palpatine/Obi-Wan):" << endl;
    int cP = 0, cO = 0;
    for(int i = 0; i < total; i++) {
        string m = maestros[i];
        if(m == "Palpatine" || m == "palpatine") cP++;
        if(m == "Obi-Wan Kenobi" || m == "Obi-Wan" || m == "obi-wan") cO++;
    }
    cout << " -> Aprendices de Palpatine: " << cP << endl;
    cout << " -> Aprendices de Obi-Wan: " << cO << endl;

    // e y f. Localizacion de Objetivos
    cout << "\n[E/F] LOCALIZACION DE INDIVIDUOS:" << endl;
    bool malak = false, yoda = false;
    for(int i = 0; i < total; i++) {
        if(nombres[i] == "Darth Malak" || nombres[i] == "darth malak") {
            cout << " [+] Darth Malak: ENCONTRADO en archivos." << endl;
            malak = true;
        }
        if(nombres[i] == "Yoda" || nombres[i] == "yoda") {
            cout << " [+] Yoda: LOCALIZADO en posicion " << i+1 << " del registro." << endl;
            yoda = true;
        }
    }
    if(!malak) cout << " [-] Darth Malak: No figura en los registros." << endl;
    if(!yoda) cout << " [-] Yoda: No figura en los registros." << endl;

    cout << "\n========================================" << endl;
    cout << "      FIN DEL REPORTE GALACTICO         " << endl;
    cout << "========================================" << endl;

    return 0;
}