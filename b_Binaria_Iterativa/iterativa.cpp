//EJERCICIO 1
#include <iostream>
using namespace std;

// Función de búsqueda binaria
int busquedaBinaria(int v[], int n, int nbus) {
    int izq = 0;
    int der = n - 1;
    int iteracion = 1;
    
    cout << "\n=== Proceso de Búsqueda Binaria ===" << endl;
    cout << "Buscando el número: " << nbus << endl;
    cout << "Tamaño del arreglo: " << n << endl;
    
    while (izq <= der) {
        int medio = (izq + der) / 2;
        
        cout << "\n--- Iteración " << iteracion << " ---" << endl;
        cout << "Límites: izq = " << izq << ", der = " << der << endl;
        cout << "Índice medio: medio = (" << izq << " + " << der << ") / 2 = " << medio << endl;
        cout << "Valor en v[" << medio << "] = " << v[medio] << endl;
        
        // Elemento encontrado
        if (v[medio] == nbus) {
            cout << "\n¡Elemento encontrado!" << endl;
            cout << "v[" << medio << "] == " << nbus << endl;
            return medio;
        }
        // El elemento está en la mitad derecha
        else if (v[medio] < nbus) {
            cout << "Decisión: " << v[medio] << " < " << nbus << endl;
            cout << "El número está en la mitad derecha" << endl;
            cout << "Ajustando: izq = medio + 1 = " << medio << " + 1 = " << (medio + 1) << endl;
            izq = medio + 1;
        }
        // El elemento está en la mitad izquierda
        else {
            cout << "Decisión: " << v[medio] << " > " << nbus << endl;
            cout << "El número está en la mitad izquierda" << endl;
            cout << "Ajustando: der = medio - 1 = " << medio << " - 1 = " << (medio - 1) << endl;
            der = medio - 1;
        }
        
        iteracion++;
    }
    
    cout << "\n¡Elemento no encontrado en el arreglo!" << endl;
    return -1;
}

int main() {
    int n, nbus;
    
    cout << "=== BÚSQUEDA BINARIA ===" << endl;
    cout << "Ingrese el tamaño del arreglo: ";
    cin >> n;
    
    int v[n];
    
    cout << "\nIngrese " << n << " números ORDENADOS de forma ASCENDENTE:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "v[" << i << "] = ";
        cin >> v[i];
    }
    
    cout << "\nArreglo ingresado: { ";
    for (int i = 0; i < n; i++) {
        cout << v[i];
        if (i < n - 1) cout << ", ";
    }
    cout << " }" << endl;
    
    cout << "\nIngrese el numero a buscar: ";
    cin >> nbus;
    
    int resultado = busquedaBinaria(v, n, nbus);
    
    cout << "\n=== RESULTADO FINAL ===" << endl;
    if (resultado != -1) {
        cout << "El número " << nbus << " se encuentra en la posición: " << resultado << endl;
    } else {
        cout << "El número " << nbus << " NO se encuentra en el arreglo." << endl;
    }
    
    return 0;
}
