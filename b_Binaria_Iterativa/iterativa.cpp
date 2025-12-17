//EJERCICIO 1
#include <iostream>
#include <limits>
using namespace std;

// Función para validar entrada de enteros positivos
int leerEnteroPositivo(const char* mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            if (valor > 0) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return valor;
            } else {
                cout << "Error: Debe ingresar un numero entero positivo mayor que 0." << endl;
            }
        } else {
            cout << "Error: Entrada invalida. Debe ingresar un numero entero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Función para leer cualquier entero (puede ser negativo)
int leerEntero(const char* mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        } else {
            cout << "Error: Entrada invalida. Debe ingresar un numero entero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Función para validar que el arreglo esté ordenado ascendentemente
bool validarOrdenAscendente(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (v[i] > v[i + 1]) {
            return false;
        }
    }
    return true;
}

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
    n = leerEnteroPositivo("Ingrese el tamaño del arreglo: ");
    
    int *v = new int[n];
    
    bool ordenCorrecto = false;
    while (!ordenCorrecto) {
        cout << "\nIngrese " << n << " números ORDENADOS de forma ASCENDENTE:" << endl;
        for (int i = 0; i < n; i++) {
            char mensaje[50];
            sprintf(mensaje, "v[%d] = ", i);
            v[i] = leerEntero(mensaje);
        }
        
        // Validar que el arreglo esté ordenado
        if (validarOrdenAscendente(v, n)) {
            ordenCorrecto = true;
        } else {
            cout << "\nError: El arreglo NO está ordenado de forma ascendente." << endl;
            cout << "Por favor, ingrese los números nuevamente en orden ascendente." << endl;
        }
    }
    
    cout << "\nArreglo ingresado: { ";
    for (int i = 0; i < n; i++) {
        cout << v[i];
        if (i < n - 1) cout << ", ";
    }
    cout << " }" << endl;
    
    nbus = leerEntero("\nIngrese el numero a buscar: ");
    
    int resultado = busquedaBinaria(v, n, nbus);
    
    cout << "\n=== RESULTADO FINAL ===" << endl;
    if (resultado != -1) {
        cout << "El número " << nbus << " se encuentra en la posición: " << resultado << endl;
    } else {
        cout << "El número " << nbus << " NO se encuentra en el arreglo." << endl;
    }
    
    delete[] v;
    
    return 0;
}