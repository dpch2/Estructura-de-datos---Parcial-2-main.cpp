//EJERCICIO 8
#include <iostream>
#include <string>
using namespace std;

int main() {
    int cantidad;
    
    cout << "Cuantos Funko Pop vas a ingresar? ";
    cin >> cantidad;
    
    // 4 arrays simples
    int numero[100];
    string nombre[100];
    string coleccion[100];
    float precio[100];
    
    // INGRESAR DATOS
    for(int i = 0; i < cantidad; i++) {
        cout << "\n--- Funko " << (i+1) << " ---" << endl;
        cout << "Numero: ";
        cin >> numero[i];
        cin.ignore();
        cout << "Nombre: ";
        getline(cin, nombre[i]);
        cout << "Coleccion: ";
        getline(cin, coleccion[i]);
        cout << "Precio: ";
        cin >> precio[i];
    }
    
    // A) ORDENAR POR NUMERO
    cout << "\n\n--- A) ORDENADOS POR NUMERO ---" << endl;
    for(int i = 0; i < cantidad; i++) {
        for(int j = i+1; j < cantidad; j++) {
            if(numero[i] > numero[j]) {
                // cambiar numero
                int temp1 = numero[i];
                numero[i] = numero[j];
                numero[j] = temp1;
                
                // cambiar nombre
                string temp2 = nombre[i];
                nombre[i] = nombre[j];
                nombre[j] = temp2;
                
                // cambiar coleccion
                string temp3 = coleccion[i];
                coleccion[i] = coleccion[j];
                coleccion[j] = temp3;
                
                // cambiar precio
                float temp4 = precio[i];
                precio[i] = precio[j];
                precio[j] = temp4;
            }
        }
    }
    
    for(int i = 0; i < cantidad; i++) {
        cout << numero[i] << " - " << nombre[i] << " - " << coleccion[i] << " - $" << precio[i] << endl;
    }
    
    // B) BUSCAR POR COLECCION
    cout << "\n\n--- B) BUSCAR POR COLECCION ---" << endl;
    string buscar;
    cin.ignore();
    cout << "Que coleccion quieres buscar? ";
    getline(cin, buscar);
    
    for(int i = 0; i < cantidad; i++) {
        if(coleccion[i] == buscar) {
            cout << numero[i] << " - " << nombre[i] << " - $" << precio[i] << endl;
        }
    }
    
    // C) BUSCAR NUMERO 130 DE STAR WARS
    cout << "\n\n--- C) BUSCAR NUMERO 130 DE STAR WARS ---" << endl;
    for(int i = 0; i < cantidad; i++) {
        if(numero[i] == 130 && coleccion[i] == "Star Wars") {
            cout << "SI EXISTE!" << endl;
            cout << "Nombre: " << nombre[i] << endl;
            cout << "Precio: $" << precio[i] << endl;
        }
    }
    
    // D) BUSCAR TODOS LOS NUMERO 295
    cout << "\n\n--- D) TODOS LOS NUMERO 295 ---" << endl;
    for(int i = 0; i < cantidad; i++) {
        if(numero[i] == 295) {
            cout << nombre[i] << " - " << coleccion[i] << " - $" << precio[i] << endl;
        }
    }
    
    // E) BUSCAR DARTH VADER Y CAPITANA MARVEL
    cout << "\n\n--- E) DARTH VADER Y CAPITANA MARVEL ---" << endl;
    for(int i = 0; i < cantidad; i++) {
        if(nombre[i] == "Darth Vader" || nombre[i] == "Capitana Marvel") {
            cout << numero[i] << " - " << nombre[i] << " - " << coleccion[i] << " - $" << precio[i] << endl;
        }
    }
    
    // F) BUSCAR RED SKULL, THANOS Y GALACTUS
    cout << "\n\n--- F) RED SKULL, THANOS Y GALACTUS ---" << endl;
    for(int i = 0; i < cantidad; i++) {
        if(nombre[i] == "Red Skull" || nombre[i] == "Thanos" || nombre[i] == "Galactus") {
            cout << nombre[i] << " - " << numero[i] << " - " << coleccion[i] << " - $" << precio[i] << endl;
        }
    }
    
    // G) SUMAR PRECIOS DE TONY STARK E IRON MAN
    cout << "\n\n--- G) COSTO TONY STARK E IRON MAN ---" << endl;
    float suma = 0;
    for(int i = 0; i < cantidad; i++) {
        if(nombre[i] == "Tony Stark" || nombre[i] == "Iron Man") {
            cout << nombre[i] << " - $" << precio[i] << endl;
            suma = suma + precio[i];
        }
    }
    cout << "TOTAL: $" << suma << endl;
    
    // H) CALCULAR PROMEDIOS
    cout << "\n\n--- H) PROMEDIOS Y TOTALES ---" << endl;
    
    // Promedio de TODOS
    float todosSuma = 0;
    for(int i = 0; i < cantidad; i++) {
        todosSuma = todosSuma + precio[i];
    }
    float promedio = todosSuma / cantidad;
    cout << "Promedio de todos: $" << promedio << endl;
    
    // Total de ROCKS
    float rocksTotal = 0;
    for(int i = 0; i < cantidad; i++) {
        if(coleccion[i] == "Rocks") {
            rocksTotal = rocksTotal + precio[i];
        }
    }
    cout << "Total Rocks: $" << rocksTotal << endl;
    
    // Total de HARRY POTTER
    float hpTotal = 0;
    for(int i = 0; i < cantidad; i++) {
        if(coleccion[i] == "Harry Potter") {
            hpTotal = hpTotal + precio[i];
        }
    }
    cout << "Total Harry Potter: $" << hpTotal << endl;
    
    return 0;
}
