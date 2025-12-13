// Busqueda Binaria con uso de variable Bandera (BAN) para indicar si se encontro. EJERCICIO 3
#include <iostream>
using namespace std;

int main() {
    int N, X;
    int IZQ, DER, CEN;
    int BAN = 0;
    int iteracion = 1;
    
    cout << "=== BUSQUEDA BINARIA ===" << endl;
    cout << "Ingrese la cantidad de elementos (N): ";
    cin >> N;
    
    int VECTOR[N];
    
    cout << "\nIngrese " << N << " numeros ORDENADOS de menor a mayor:\n";
    for (int i = 0; i < N; i++) {
        cout << "VECTOR[" << i << "] = ";
        cin >> VECTOR[i];
    }
    
    cout << "\nVECTOR ingresado: { ";
    for (int i = 0; i < N; i++) {
        cout << VECTOR[i];
        if (i < N - 1) cout << ", ";
    }
    cout << " }" << endl;
    
    cout << "\nIngrese el numero a buscar (X): ";
    cin >> X;
    
    // Inicializar límites
    IZQ = 0;
    DER = N - 1;
    
    cout << "\n--- PROCESO DE BUSQUEDA ---" << endl;
    cout << "Buscando X = " << X << endl;
    cout << "Limites iniciales: IZQ = " << IZQ << ", DER = " << DER << endl;
    
    // Búsqueda binaria
    while (IZQ <= DER && BAN == 0) {
        cout << "\n** Iteracion " << iteracion << " **" << endl;
        
        // Calcular centro
        CEN = (IZQ + DER) / 2;
        
        cout << "CEN = (IZQ + DER) / 2" << endl;
        cout << "CEN = (" << IZQ << " + " << DER << ") / 2" << endl;
        cout << "CEN = " << (IZQ + DER) << " / 2" << endl;
        cout << "CEN = " << CEN << endl;
        
        cout << "VECTOR[" << CEN << "] = " << VECTOR[CEN] << endl;
        
        // Comparar
        if (VECTOR[CEN] == X) {
            cout << "Comparacion: " << VECTOR[CEN] << " == " << X << " -> VERDADERO" << endl;
            cout << "Elemento encontrado!" << endl;
            BAN = 1;
        }
        else if (X < VECTOR[CEN]) {
            cout << "Comparacion: " << X << " < " << VECTOR[CEN] << " -> VERDADERO" << endl;
            cout << "Buscar en mitad IZQUIERDA" << endl;
            cout << "DER = CEN - 1 = " << CEN << " - 1 = " << (CEN - 1) << endl;
            DER = CEN - 1;
        }
        else {
            cout << "Comparacion: " << X << " > " << VECTOR[CEN] << " -> VERDADERO" << endl;
            cout << "Buscar en mitad DERECHA" << endl;
            cout << "IZQ = CEN + 1 = " << CEN << " + 1 = " << (CEN + 1) << endl;
            IZQ = CEN + 1;
        }
        
        if (BAN == 0) {
            cout << "Nuevos limites: IZQ = " << IZQ << ", DER = " << DER << endl;
        }
        
        iteracion++;
    }
    
    // Resultado
    cout << "\n=== RESULTADO ===" << endl;
    if (BAN == 1) {
        cout << "El numero " << X << " se encuentra en la posicion: " << CEN << endl;
        cout << "BAN = " << BAN << " (elemento encontrado)" << endl;
    }
    else {
        cout << "El numero " << X << " NO se encuentra en el vector." << endl;
        cout << "BAN = " << BAN << " (elemento no encontrado)" << endl;
        cout << "Condicion de salida: IZQ > DER (" << IZQ << " > " << DER << ")" << endl;
    }
    
    return 0;
}
