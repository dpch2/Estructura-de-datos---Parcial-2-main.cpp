#include <iostream>
#include <limits>
#include <string>

using namespace std;

// --- FUNCION DE VALIDACION ---
// Evita que el programa se rompa si se ingresan letras o simbolos
template <typename T>
T leerDato(string mensaje) {
    T valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            return valor;
        } else {
            cout << " [!] Error: Entrada no valida. Intente de nuevo.\n";
            cin.clear(); // Limpia el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta el buffer
        }
    }
}

void mostrarCabecera() {
    cout << "============================================" << endl;
    cout << "       CALCULADORA DE ESPACIO (HASH)        " << endl;
    cout << "============================================" << endl;
}

int main() {
    int hc;            // Tamaño de la tabla
    float factorCarga;
    int tipoClave;
    
    mostrarCabecera();
    
    // Entrada de datos con validacion
    hc = leerDato<int>(" > Tamanio de la tabla (hc): ");
    factorCarga = leerDato<float>(" > Factor de carga (0.25, 0.5, 1.0, 2.0): ");
    
    cout << "\n--- TIPO DE CLAVE ---" << endl;
    cout << " 1 = Clave de 1 palabra (nodo = 2 palabras)" << endl;
    cout << " 2 = Clave de 4 palabras (nodo = 5 palabras)" << endl;
    tipoClave = leerDato<int>(" > Seleccione opcion (1 o 2): ");
    
    // --- CALCULO LOGICO ---
    // n = factor_carga * hc
    int n = (int)(factorCarga * hc);
    
    cout << "\n" << string(44, '=') << endl;
    cout << "          RESULTADOS DEL ANALISIS           " << endl;
    cout << string(44, '=') << endl;
    cout << " Numero de claves (n): " << n << endl;
    
    // --- DIRECCIONAMIENTO CERRADO ---
    cout << "\n[1] DIRECCIONAMIENTO CERRADO" << endl;
    cout << "--------------------------------------------" << endl;
    
    int espacioTabla = hc; // 1 palabra por entrada de tabla (puntero)
    int espacioListas;
    int palabrasPorNodo = (tipoClave == 1) ? 2 : 5;
    
    espacioListas = n * palabrasPorNodo;
    int totalCerrado = espacioTabla + espacioListas;
    
    cout << " + Espacio tabla (punteros): " << hc << " palabras" << endl;
    cout << " + Espacio nodos: " << n << " x " << palabrasPorNodo << " = " << espacioListas << " palabras" << endl;
    cout << " >> TOTAL CERRADO: " << totalCerrado << " palabras" << endl;
    
    // --- DIRECCIONAMIENTO ABIERTO ---
    cout << "\n[2] DIRECCIONAMIENTO ABIERTO" << endl;
    cout << "--------------------------------------------" << endl;
    cout << " * Usando el mismo espacio total: " << totalCerrado << " palabras" << endl;
    
    int palabrasPorClave = (tipoClave == 1) ? 1 : 4;
    int capacidadAbierto = totalCerrado / palabrasPorClave;
    float factorCargaAbierto = (float)n / capacidadAbierto;
    
    cout << " + Capacidad max: " << totalCerrado << " / " << palabrasPorClave << " = " << capacidadAbierto << " claves" << endl;
    cout << " >> NUEVO FACTOR DE CARGA: " << factorCargaAbierto << endl;
    
    // --- RESUMEN FINAL ---
    cout << "\n" << string(44, '-') << endl;
    cout << " RESUMEN: Para " << n << " claves..." << endl;
    cout << " En Cerrado (alpha=" << factorCarga << ") ocupas " << totalCerrado << " palabras." << endl;
    cout << " En Abierto con ese espacio, el alpha baja a: " << factorCargaAbierto << endl;
    cout << string(44, '=') << endl;

    return 0;
}