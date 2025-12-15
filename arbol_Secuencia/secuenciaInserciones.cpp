#include <iostream>
using namespace std;

void imprimirArbol234() {
    cout << "\n          [E M]" << endl;
    cout << "         /  |  \\" << endl;
    cout << "        /   |   \\" << endl;
    cout << "   [BDE] [EJL] [OPU]" << endl;
    cout << endl;
}

void simularInsercion(char clave, int paso) {
    cout << "Paso " << paso << ": Insertar '" << clave << "'" << endl;
    
    switch(paso) {
        case 1:
            cout << "  - Primera insercion: [E]" << endl;
            break;
        case 2:
            cout << "  - Insertar M > E: [E M]" << endl;
            break;
        case 3:
            cout << "  - Insertar B < E: necesita ir a la izquierda" << endl;
            cout << "  - Dividir raiz: M sube, E y B quedan separados" << endl;
            cout << "  - Resultado: [M] con hijos [B E] y hoja derecha vacia" << endl;
            break;
        case 4:
            cout << "  - Insertar D: B < D < E, va al hijo izquierdo" << endl;
            cout << "  - Hijo izquierdo: [B D E]" << endl;
            break;
        case 5:
            cout << "  - Insertar E: va al hijo izquierdo que ya esta lleno [B D E]" << endl;
            cout << "  - Division: D sube a la raiz" << endl;
            cout << "  - Raiz: [D M], hijos: [B], [E E], []" << endl;
            break;
        case 6:
            cout << "  - Insertar J: D < J < M, va al hijo central" << endl;
            cout << "  - Hijo central: [E E J]" << endl;
            break;
        case 7:
            cout << "  - Insertar L: va al hijo central que ya esta lleno" << endl;
            cout << "  - Division necesaria: ajuste de estructura" << endl;
            break;
        case 8:
            cout << "  - Insertar O: M < O, va al hijo derecho" << endl;
            cout << "  - Hijo derecho: [O]" << endl;
            break;
        case 9:
            cout << "  - Insertar P: va al hijo derecho" << endl;
            cout << "  - Hijo derecho: [O P]" << endl;
            break;
        case 10:
            cout << "  - Insertar U: va al hijo derecho" << endl;
            cout << "  - Hijo derecho: [O P U]" << endl;
            break;
    }
    cout << endl;
}

int main() {
    cout << "=============================================" << endl;
    cout << "  CONSTRUCCION DE ARBOL 2-3-4 DE LA IMAGEN" << endl;
    cout << "=============================================" << endl;
    
    cout << "\nARBOL OBJETIVO:";
    imprimirArbol234();
    
    cout << "ANALISIS: El arbol tiene:" << endl;
    cout << "  - Raiz: [E M] (2 claves)" << endl;
    cout << "  - Hijo izq: [B D E] (3 claves)" << endl;
    cout << "  - Hijo centro: [E J L] (3 claves)" << endl;
    cout << "  - Hijo der: [O P U] (3 claves)" << endl;
    cout << "\n=============================================" << endl;
    
    // Propuesta de secuencia
    char secuencia[] = {'E', 'M', 'B', 'D', 'E', 'J', 'L', 'O', 'P', 'U'};
    int n = 10;
    
    cout << "\nSECUENCIA PROPUESTA: ";
    for (int i = 0; i < n; i++) {
        cout << secuencia[i];
        if (i < n-1) cout << ", ";
    }
    cout << "\n\n=============================================" << endl;
    cout << "SIMULACION PASO A PASO:" << endl;
    cout << "=============================================" << endl;
    
    for (int i = 0; i < n; i++) {
        simularInsercion(secuencia[i], i+1);
    }
    
    cout << "=============================================" << endl;
    cout << "\nOTRAS SECUENCIAS POSIBLES:" << endl;
    cout << "=============================================" << endl;
    
    cout << "\nOpcion 1 (mas natural):" << endl;
    cout << "  E, M, J, L, B, D, E, O, P, U" << endl;
    cout << "  - Construye primero la parte central" << endl;
    
    cout << "\nOpcion 2 (balanceada):" << endl;
    cout << "  M, E, B, D, E, J, L, O, P, U" << endl;
    cout << "  - Empieza con M como pivote" << endl;
    
    cout << "\nOpcion 3 (de la imagen):" << endl;
    cout << "  E, M, B, D, E, J, L, O, P, U" << endl;
    cout << "  - Secuencia mas probable" << endl;
    
    cout << "\n=============================================" << endl;
    cout << "NOTA IMPORTANTE:" << endl;
    cout << "=============================================" << endl;
    cout << "Hay MULTIPLES secuencias que pueden generar" << endl;
    cout << "este mismo arbol 2-3-4. La estructura final" << endl;
    cout << "depende del algoritmo especifico de insercion" << endl;
    cout << "y de como maneja las divisiones de nodos." << endl;
    
    cout << "\nPara verificar cual es LA secuencia correcta," << endl;
    cout << "seria necesario implementar el algoritmo" << endl;
    cout << "completo de arbol 2-3-4 y probar cada opcion." << endl;
    
    cout << "\n=============================================" << endl;
    cout << "CONVERSION A ARBOL ROJO-NEGRO:" << endl;
    cout << "=============================================" << endl;
    cout << "Un arbol 2-3-4 se puede representar como" << endl;
    cout << "un arbol rojo-negro donde:" << endl;
    cout << "  - Nodos 2: un nodo negro" << endl;
    cout << "  - Nodos 3: nodo negro + 1 hijo rojo" << endl;
    cout << "  - Nodos 4: nodo negro + 2 hijos rojos" << endl;
    
    return 0;
}