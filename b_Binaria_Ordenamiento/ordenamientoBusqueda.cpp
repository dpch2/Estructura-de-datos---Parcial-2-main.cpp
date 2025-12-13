// EJERCICIO 9
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Variables simples - Arrays paralelos
    string nombres[100];
    string maestros[100];
    string tipo[100]; // "Jedi" o "Sith"
    int total = 0;
    
    cout << "=== SISTEMA DE JEDI Y SITH ===" << endl;
    cout << "Cuantos personajes desea ingresar? ";
    cin >> total;
    cin.ignore();
    
    // ENTRADA DE DATOS
    for(int i = 0; i < total; i++) {
        cout << "\n--- Personaje " << (i+1) << " ---" << endl;
        cout << "Nombre: ";
        getline(cin, nombres[i]);
        cout << "Maestro: ";
        getline(cin, maestros[i]);
        cout << "Tipo (Jedi/Sith): ";
        getline(cin, tipo[i]);
    }
    
    // a. ORDENAR POR NOMBRE (Bubble Sort)
    cout << "\n\n=== a. LISTA ORDENADA POR NOMBRE ===" << endl;
    string tempN, tempM, tempT;
    for(int i = 0; i < total-1; i++) {
        for(int j = 0; j < total-i-1; j++) {
            if(nombres[j] > nombres[j+1]) {
                // Intercambiar nombres
                tempN = nombres[j];
                nombres[j] = nombres[j+1];
                nombres[j+1] = tempN;
                // Intercambiar maestros
                tempM = maestros[j];
                maestros[j] = maestros[j+1];
                maestros[j+1] = tempM;
                // Intercambiar tipos
                tempT = tipo[j];
                tipo[j] = tipo[j+1];
                tipo[j+1] = tempT;
            }
        }
    }
    
    for(int i = 0; i < total; i++) {
        cout << i+1 << ". " << nombres[i] << " - Maestro: " 
             << maestros[i] << " - Tipo: " << tipo[i] << endl;
    }
    
    // b. LISTAR SOLO JEDI ORDENADOS
    cout << "\n\n=== b. LISTA DE JEDI ===" << endl;
    int contJedi = 0;
    for(int i = 0; i < total; i++) {
        if(tipo[i] == "Jedi" || tipo[i] == "jedi") {
            contJedi++;
            cout << contJedi << ". " << nombres[i] 
                 << " - Maestro: " << maestros[i] << endl;
        }
    }
    cout << "Total Jedi: " << contJedi << endl;
    
    // c. LISTAR SOLO SITH ORDENADOS
    cout << "\n\n=== c. LISTA DE SITH ===" << endl;
    int contSith = 0;
    for(int i = 0; i < total; i++) {
        if(tipo[i] == "Sith" || tipo[i] == "sith") {
            contSith++;
            cout << contSith << ". " << nombres[i] 
                 << " - Maestro: " << maestros[i] << endl;
        }
    }
    cout << "Total Sith: " << contSith << endl;
    
    // d. APRENDICES DE PALPATINE Y OBI-WAN
    cout << "\n\n=== d. APRENDICES ===" << endl;
    
    cout << "\nAprendices de Palpatine:" << endl;
    int contPalp = 0;
    for(int i = 0; i < total; i++) {
        if(maestros[i] == "Palpatine" || maestros[i] == "palpatine") {
            contPalp++;
            cout << "  - " << nombres[i] << endl;
        }
    }
    cout << "Total: " << contPalp << " aprendices" << endl;
    
    cout << "\nAprendices de Obi-Wan Kenobi:" << endl;
    int contObi = 0;
    for(int i = 0; i < total; i++) {
        if(maestros[i] == "Obi-Wan Kenobi" || maestros[i] == "Obi-Wan" 
           || maestros[i] == "obi-wan kenobi" || maestros[i] == "obi-wan") {
            contObi++;
            cout << "  - " << nombres[i] << endl;
        }
    }
    cout << "Total: " << contObi << " aprendices" << endl;
    
    // e. BUSCAR DARTH MALAK
    cout << "\n\n=== e. BUSQUEDA DE DARTH MALAK ===" << endl;
    bool encontrado = false;
    for(int i = 0; i < total; i++) {
        if(nombres[i] == "Darth Malak" || nombres[i] == "darth malak" 
           || nombres[i] == "Dath Malak" || nombres[i] == "dath malak") {
            encontrado = true;
            cout << "ENCONTRADO!" << endl;
            cout << "Nombre: " << nombres[i] << endl;
            cout << "Maestro: " << maestros[i] << endl;
            cout << "Tipo: " << tipo[i] << endl;
            break;
        }
    }
    if(!encontrado) {
        cout << "Darth Malak NO esta en la lista" << endl;
    }
    
    // f. POSICION DE YODA
    cout << "\n\n=== f. POSICION DE YODA ===" << endl;
    bool yodaEncontrado = false;
    for(int i = 0; i < total; i++) {
        if(nombres[i] == "Yoda" || nombres[i] == "yoda") {
            yodaEncontrado = true;
            cout << "Yoda se encuentra en la posicion: " << (i+1) << endl;
            cout << "Informacion:" << endl;
            cout << "  Nombre: " << nombres[i] << endl;
            cout << "  Maestro: " << maestros[i] << endl;
            cout << "  Tipo: " << tipo[i] << endl;
            break;
        }
    }
    if(!yodaEncontrado) {
        cout << "Yoda NO esta en la lista" << endl;
    }
    
    return 0;
}