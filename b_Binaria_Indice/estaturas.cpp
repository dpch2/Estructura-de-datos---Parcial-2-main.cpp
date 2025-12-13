// EJERCICIO 2
#include <iostream>
using namespace std;

int busquedaBinaria(double estaturas[], int N, double E_objetivo) {
    int inferior = 1;
    int superior = N;
    
    cout << "\nBuscando estatura: " << E_objetivo << endl;
    
    while (inferior <= superior) {
        int medio = (inferior + superior) / 2;
        
        cout << "\nIteracion:" << endl;
        cout << "inferior = " << inferior << ", superior = " << superior << endl;
        cout << "medio = (" << inferior << " + " << superior << ") / 2 = " << medio << endl;
        cout << "ESTATURAS[" << medio << "] = " << estaturas[medio] << endl;
        
        if (estaturas[medio] == E_objetivo) {
            cout << "\nEstatura encontrada en posicion: " << medio << endl;
            return medio;
        }
        else if (estaturas[medio] < E_objetivo) {
            cout << estaturas[medio] << " < " << E_objetivo << " -> Buscar en mitad superior" << endl;
            inferior = medio + 1;
        }
        else {
            cout << estaturas[medio] << " > " << E_objetivo << " -> Buscar en mitad inferior" << endl;
            superior = medio - 1;
        }
    }
    
    cout << "\nEstatura NO encontrada" << endl;
    return -1;
}

int main() {
    int N;
    double E_objetivo;
    
    cout << "Ingrese cantidad de estudiantes: ";
    cin >> N;
    
    double estaturas[N + 1];
    
    cout << "\nIngrese estaturas ordenadas de menor a mayor:\n";
    for (int i = 1; i <= N; i++) {
        cout << "ESTATURAS[" << i << "] = ";
        cin >> estaturas[i];
    }
    
    cout << "\nIngrese estatura a buscar: ";
    cin >> E_objetivo;
    
    int resultado = busquedaBinaria(estaturas, N, E_objetivo);
    
    cout << "\n--- RESULTADO ---" << endl;
    if (resultado != -1) {
        cout << "Posicion: " << resultado << endl;
    } else {
        cout << "Estatura no encontrada en el vector" << endl;
    }
    
    return 0;
}