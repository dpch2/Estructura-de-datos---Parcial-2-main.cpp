// EJERCICIO 2
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

// Función para leer números decimales positivos (estaturas)
double leerDecimalPositivo(const char* mensaje) {
    double valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            if (valor > 0) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return valor;
            } else {
                cout << "Error: La estatura debe ser un numero positivo mayor que 0." << endl;
            }
        } else {
            cout << "Error: Entrada invalida. Debe ingresar un numero decimal valido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Función para validar que el arreglo esté ordenado de menor a mayor
bool validarOrdenAscendente(double estaturas[], int N) {
    for (int i = 1; i < N; i++) {
        if (estaturas[i] > estaturas[i + 1]) {
            return false;
        }
    }
    return true;
}

int busquedaBinaria(double estaturas[], int N, double E_objetivo) {
    int inferior = 1;
    int superior = N;
    
    cout << "\n=== Proceso de Busqueda Binaria ===" << endl;
    cout << "Buscando estatura: " << E_objetivo << endl;
    
    while (inferior <= superior) {
        int medio = (inferior + superior) / 2;
        
        cout << "\nIteracion:" << endl;
        cout << "inferior = " << inferior << ", superior = " << superior << endl;
        cout << "medio = (" << inferior << " + " << superior << ") / 2 = " << medio << endl;
        cout << "ESTATURAS[" << medio << "] = " << estaturas[medio] << endl;
        
        if (estaturas[medio] == E_objetivo) {
            cout << "\n¡Estatura encontrada en posicion: " << medio << "!" << endl;
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
    
    cout << "\nEstatura NO encontrada en el vector" << endl;
    return -1;
}

int main() {
    int N;
    double E_objetivo;
    
    cout << "=== BUSQUEDA DE ESTATURAS ===" << endl;
    N = leerEnteroPositivo("Ingrese cantidad de estudiantes: ");
    
    double *estaturas = new double[N + 1]; // Índices de 1 a N
    
    bool ordenCorrecto = false;
    while (!ordenCorrecto) {
        cout << "\nIngrese estaturas ordenadas de MENOR a MAYOR (en metros):\n";
        for (int i = 1; i <= N; i++) {
            char mensaje[50];
            sprintf(mensaje, "ESTATURAS[%d] = ", i);
            estaturas[i] = leerDecimalPositivo(mensaje);
        }
        
        // Validar que el arreglo esté ordenado
        if (validarOrdenAscendente(estaturas, N)) {
            ordenCorrecto = true;
        } else {
            cout << "\nError: Las estaturas NO estan ordenadas de menor a mayor." << endl;
            cout << "Por favor, ingrese las estaturas nuevamente en orden ascendente." << endl;
        }
    }
    
    // Mostrar vector ingresado
    cout << "\nVector ESTATURAS ingresado:" << endl;
    cout << "{ ";
    for (int i = 1; i <= N; i++) {
        cout << estaturas[i];
        if (i < N) cout << ", ";
    }
    cout << " }" << endl;
    
    E_objetivo = leerDecimalPositivo("\nIngrese estatura a buscar: ");
    
    int resultado = busquedaBinaria(estaturas, N, E_objetivo);
    
    cout << "\n=== RESULTADO FINAL ===" << endl;
    if (resultado != -1) {
        cout << "La estatura " << E_objetivo << " se encuentra en la posicion: " << resultado << endl;
    } else {
        cout << "La estatura " << E_objetivo << " NO se encuentra en el vector" << endl;
    }
    
    delete[] estaturas;
    
    return 0;
}