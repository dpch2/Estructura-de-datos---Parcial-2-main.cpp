// EJERCICIO 6
#include <iostream>
using namespace std;

int main() {
    int hc; // Tamaño de la tabla
    float factorCarga;
    int tipoClave;
    
    cout << "=== CALCULADORA DE ESPACIO ===\n\n";
    
    // Entrada de datos
    cout << "Tamanio de la tabla (hc): ";
    cin >> hc;
    
    cout << "Factor de carga (0.25, 0.5, 1.0, 2.0): ";
    cin >> factorCarga;
    
    cout << "Tipo de clave:\n";
    cout << "1 = Clave de 1 palabra (nodo=2 palabras)\n";
    cout << "2 = Clave de 4 palabras (nodo=5 palabras)\n";
    cout << "Opcion: ";
    cin >> tipoClave;
    
    // Calcular número de claves
    int n = factorCarga * hc;
    
    cout << "\n========== RESULTADOS ==========\n";
    cout << "Numero de claves (n): " << n << "\n\n";
    
    // DIRECCIONAMIENTO CERRADO
    cout << "--- DIRECCIONAMIENTO CERRADO ---\n";
    
    int espacioTabla = hc;
    int espacioListas;
    int totalCerrado;
    
    if(tipoClave == 1) {
        espacioListas = n * 2; // cada nodo = 2 palabras
        cout << "Espacio tabla: " << hc << " palabras\n";
        cout << "Espacio listas: " << n << " nodos x 2 = " << espacioListas << " palabras\n";
    } else {
        espacioListas = n * 5; // cada nodo = 5 palabras
        cout << "Espacio tabla: " << hc << " palabras\n";
        cout << "Espacio listas: " << n << " nodos x 5 = " << espacioListas << " palabras\n";
    }
    
    totalCerrado = espacioTabla + espacioListas;
    cout << "TOTAL CERRADO: " << totalCerrado << " palabras\n";
    
    // DIRECCIONAMIENTO ABIERTO
    cout << "\n--- DIRECCIONAMIENTO ABIERTO ---\n";
    cout << "Usando el mismo espacio: " << totalCerrado << " palabras\n";
    
    int capacidadAbierto;
    float factorCargaAbierto;
    
    if(tipoClave == 1) {
        capacidadAbierto = totalCerrado; // 1 palabra por clave
        cout << "Capacidad: " << totalCerrado << " / 1 = " << capacidadAbierto << " claves\n";
    } else {
        capacidadAbierto = totalCerrado / 4; // 4 palabras por clave
        cout << "Capacidad: " << totalCerrado << " / 4 = " << capacidadAbierto << " claves\n";
    }
    
    factorCargaAbierto = (float)n / capacidadAbierto;
    cout << "Factor de carga: " << n << " / " << capacidadAbierto << " = " << factorCargaAbierto << "\n";
    
    cout << "\n========== RESUMEN ==========\n";
    cout << "Factor cerrado: " << factorCarga << " -> Factor abierto: " << factorCargaAbierto << "\n";
    
    return 0;
}