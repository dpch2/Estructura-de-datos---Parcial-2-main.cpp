// EJERCICIO 4
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
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

// Función para validar que n <= m
void validarRelacionNM(int &n, int &m) {
    while (n > m) {
        cout << "Error: n debe ser <= m" << endl;
        cout << "\nIngrese los valores nuevamente:" << endl;
        n = leerEnteroPositivo("Ingrese n (tamaño del arreglo E): ");
        m = leerEnteroPositivo("Ingrese m (tamaño del conjunto S): ");
    }
}

// Búsqueda binaria que cuenta comparaciones
int busquedaBinaria(int E[], int inicio, int fin, int K, int &comparaciones) {
    comparaciones = 0;
    
    while (inicio <= fin) {
        comparaciones++;
        int medio = (inicio + fin) / 2;
        
        if (E[medio] == K) {
            return medio;  // Encontrado
        }
        
        if (E[medio] < K) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    
    return -1;  // No encontrado
}

int main() {
    srand(time(0));
    
    // Parámetros con validación
    int n, m;
    n = leerEnteroPositivo("Ingrese n (tamaño del arreglo E): ");
    m = leerEnteroPositivo("Ingrese m (tamaño del conjunto S): ");
    
    // Validar que n <= m
    validarRelacionNM(n, m);
    
    // Crear arreglo E con n elementos ordenados
    int *E = new int[n];
    for (int i = 0; i < n; i++) {
        E[i] = i * 2;  // Elementos pares: 0, 2, 4, 6, ...
    }
    
    // Crear conjunto S con m elementos
    int *S = new int[m];
    for (int i = 0; i < n; i++) {
        S[i] = E[i];  // Primeros n elementos son los de E
    }
    for (int i = n; i < m; i++) {
        S[i] = i * 2 + 1;  // Resto son impares: no están en E
    }
    
    // Realizar experimento: 10000 búsquedas aleatorias
    int numPruebas = 10000;
    int totalComparaciones = 0;
    int comparaciones;
    
    for (int i = 0; i < numPruebas; i++) {
        int K = S[rand() % m];  // Elegir K al azar de S
        busquedaBinaria(E, 0, n - 1, K, comparaciones);
        totalComparaciones += comparaciones;
    }
    
    double promedioExperimental = (double)totalComparaciones / numPruebas;
    double promedioTeorico = floor(log2(n)) + 1;
    
    // Resultados
    cout << "\n=== RESULTADOS ===" << endl;
    cout << "n = " << n << ", m = " << m << endl;
    cout << "\nPromedio experimental de comparaciones: " << promedioExperimental << endl;
    cout << "Promedio teorico (⌊log₂(n)⌋ + 1): " << promedioTeorico << endl;
    cout << "\nFormula: C(n,m) = ⌊log₂(" << n << ")⌋ + 1 = " << promedioTeorico << endl;
    
    // Liberar memoria
    delete[] E;
    delete[] S;
    
    return 0;
}