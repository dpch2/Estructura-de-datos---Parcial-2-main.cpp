// EJERCICIO 7
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Declarar cantidad de pokemones
    int n;
    cout << "Cuantos Pokemones vas a ingresar? ";
    cin >> n;
    
    // Declarar arrays para guardar datos
    string nombres[100];
    int numeros[100];
    string tipos[100];
    
    // PASO 1: Ingresar datos
    cout << "\n--- INGRESA LOS DATOS ---\n";
    for(int i = 0; i < n; i++) {
        cout << "\nPokemon " << (i+1) << ":\n";
        cout << "Nombre: ";
        cin >> nombres[i];
        cout << "Numero: ";
        cin >> numeros[i];
        cout << "Tipo: ";
        cin >> tipos[i];
    }
    
    // PASO 2: Encontrar el numero mas grande
    int maximo = numeros[0];
    for(int i = 1; i < n; i++) {
        if(numeros[i] > maximo) {
            maximo = numeros[i];
        }
    }
    
    cout << "\n--- ORDENAMIENTO POR CONTEO ---\n";
    cout << "Numero maximo encontrado: " << maximo << "\n\n";
    
    // PASO 3: Crear array de conteo
    int conteo[1000];
    // Inicializar todo en 0
    for(int i = 0; i <= maximo; i++) {
        conteo[i] = 0;
    }
    
    // PASO 4: Contar cuantas veces aparece cada numero
    cout << "Contando apariciones...\n";
    for(int i = 0; i < n; i++) {
        conteo[numeros[i]]++;
        cout << "Pokemon " << nombres[i] << " (num " << numeros[i] << ") -> conteo[" << numeros[i] << "]++\n";
    }
    
    // PASO 5: Acumular conteos (suma acumulada)
    cout << "\nAcumulando conteos...\n";
    for(int i = 1; i <= maximo; i++) {
        conteo[i] = conteo[i] + conteo[i-1];
    }
    
    // PASO 6: Crear arrays ordenados
    string nombresOrdenados[100];
    int numerosOrdenados[100];
    string tiposOrdenados[100];
    
    // PASO 7: Colocar cada pokemon en su posicion correcta
    cout << "\nColocando en posiciones correctas...\n";
    for(int i = n-1; i >= 0; i--) {
        int numero = numeros[i];
        int posicion = conteo[numero] - 1;
        
        cout << nombres[i] << " (num " << numero << ") va en posicion " << posicion << "\n";
        
        numerosOrdenados[posicion] = numeros[i];
        nombresOrdenados[posicion] = nombres[i];
        tiposOrdenados[posicion] = tipos[i];
        
        conteo[numero]--;
    }
    
    // PASO 8: Mostrar resultado ordenado
    cout << "\n=== POKEMONES ORDENADOS POR NUMERO ===\n";
    for(int i = 0; i < n; i++) {
        cout << numerosOrdenados[i] << " - " << nombresOrdenados[i] << " (" << tiposOrdenados[i] << ")\n";
    }
    
    return 0;
}
