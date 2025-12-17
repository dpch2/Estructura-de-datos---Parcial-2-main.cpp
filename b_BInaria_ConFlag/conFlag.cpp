// Busqueda Binaria con uso de variable Bandera (BAN) para indicar si se encontro. EJERCICIO 3
#include <iostream>
#include <limits>
using namespace std;

// Función para validar entrada de enteros positivos
int leerEnteroPositivo(const char* mensaje, int min, int max) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            if (valor >= min && valor <= max) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return valor;
            } else {
                cout << "Error: Debe ingresar un numero entre " << min << " y " << max << "." << endl;
            }
        } else {
            cout << "Error: Entrada invalida. Debe ingresar un numero entero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Función para leer cualquier entero
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
bool validarOrdenAscendente(int VECTOR[], int N) {
    for (int i = 0; i < N - 1; i++) {
        if (VECTOR[i] > VECTOR[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int N, X;
    int IZQ, DER, CEN;
    int BAN = 0;
    int iteracion = 1;
    
    cout << "=== BUSQUEDA BINARIA ===" << endl;
    N = leerEnteroPositivo("Ingrese la cantidad de elementos (N) [1-50]: ", 1, 50);
    
    int *VECTOR = new int[N];
    
    bool ordenCorrecto = false;
    while (!ordenCorrecto) {
        cout << "\nIngrese " << N << " numeros ORDENADOS de menor a mayor:\n";
        for (int i = 0; i < N; i++) {
            char mensaje[50];
            sprintf(mensaje, "VECTOR[%d] = ", i);
            VECTOR[i] = leerEntero(mensaje);
        }
        
        // Validar que el arreglo esté ordenado
        if (validarOrdenAscendente(VECTOR, N)) {
            ordenCorrecto = true;
        } else {
            cout << "\nError: El arreglo NO esta ordenado de forma ascendente." << endl;
            cout << "Por favor, ingrese los numeros nuevamente en orden ascendente." << endl;
        }
    }
    
    cout << "\nVECTOR ingresado: { ";
    for (int i = 0; i < N; i++) {
        cout << VECTOR[i];
        if (i < N - 1) cout << ", ";
    }
    cout << " }" << endl;
    
    X = leerEntero("\nIngrese el numero a buscar (X): ");
    
    // Inicializar límites
    IZQ = 0;
    DER = N - 1;
    
    cout << "\n--- PROCESO DE BUSQUEDA ---" << endl;
    cout << "Buscando X = " << X << endl;
    cout << "Limites iniciales: IZQ = " << IZQ << ", DER = " << DER << endl;
    
    // Búsqueda binaria con variable bandera (BAN)
    while (IZQ <= DER && BAN == 0) {
        cout << "\n** Iteracion " << iteracion << " **" << endl;
        
        // Calcular centro (divide el intervalo en dos partes)
        CEN = (IZQ + DER) / 2;
        
        cout << "CEN = (IZQ + DER) / 2" << endl;
        cout << "CEN = (" << IZQ << " + " << DER << ") / 2" << endl;
        cout << "CEN = " << (IZQ + DER) << " / 2" << endl;
        cout << "CEN = " << CEN << endl;
        
        cout << "VECTOR[" << CEN << "] = " << VECTOR[CEN] << endl;
        
        // Comparar con el elemento central
        if (VECTOR[CEN] == X) {
            cout << "Comparacion: " << VECTOR[CEN] << " == " << X << " -> VERDADERO" << endl;
            cout << "¡Elemento encontrado!" << endl;
            BAN = 1;  // Bandera activada: elemento encontrado
        }
        else if (X < VECTOR[CEN]) {
            cout << "Comparacion: " << X << " < " << VECTOR[CEN] << " -> VERDADERO" << endl;
            cout << "Buscar en mitad IZQUIERDA (redefinir extremo derecho)" << endl;
            cout << "DER = CEN - 1 = " << CEN << " - 1 = " << (CEN - 1) << endl;
            DER = CEN - 1;  // Redefinir extremo derecho
        }
        else {
            cout << "Comparacion: " << X << " > " << VECTOR[CEN] << " -> VERDADERO" << endl;
            cout << "Buscar en mitad DERECHA (redefinir extremo izquierdo)" << endl;
            cout << "IZQ = CEN + 1 = " << CEN << " + 1 = " << (CEN + 1) << endl;
            IZQ = CEN + 1;  // Redefinir extremo izquierdo
        }
        
        if (BAN == 0) {
            cout << "Nuevos limites: IZQ = " << IZQ << ", DER = " << DER << endl;
            cout << "Espacio de busqueda reducido a la mitad" << endl;
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
        cout << "Espacio de busqueda anulado: IZQ > DER (" << IZQ << " > " << DER << ")" << endl;
    }
    
    cout << "\nNumero total de iteraciones: " << (iteracion - 1) << endl;
    
    delete[] VECTOR;
    
    return 0;
}