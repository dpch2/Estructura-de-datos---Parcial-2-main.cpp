// EJERCICIO 4
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

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
    
    // Parámetros
    int n, m;
    cout << "Ingrese n (tamaño del arreglo E): ";
    cin >> n;
    cout << "Ingrese m (tamaño del conjunto S): ";
    cin >> m;
    
    if (n > m) {
        cout << "Error: n debe ser <= m" << endl;
        return 1;
    }
    
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
    cout << "Promedio teórico (⌊log₂(n)⌋ + 1): " << promedioTeorico << endl;
    cout << "\nFórmula: C(n,m) = ⌊log₂(" << n << ")⌋ + 1 = " << promedioTeorico << endl;
    
    // Liberar memoria
    delete[] E;
    delete[] S;
    
    return 0;
}