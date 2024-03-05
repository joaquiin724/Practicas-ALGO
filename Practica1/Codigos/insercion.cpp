/**
   @file Ordenaci�n por inserci�n
*/

#include <chrono>
using namespace std::chrono;   
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>






/* ************************************************************ */ 
/*  M�todo de ordenaci�n por inserci�n  */

/**
   @brief Ordena un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
template<typename P>
inline static void insercion(P T[], int num_elem);



/**
   @brief Ordena parte de un vector por el m�todo de inserci�n.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de inserci�n.
*/
template<typename P>
static void insercion_lims(P T[], int inicial, int final);



/**
   Implementaci�n de las funciones
**/
template<typename P>
inline static void insercion(P T[], int num_elem)
{
  insercion_lims(T, 0, num_elem);
}

template<typename P>
static void insercion_lims(P T[], int inicial, int final)
{
  int i, j;
  P aux;
  for (i = inicial + 1; i < final; i++) {
    j = i;
    while ((T[j] < T[j-1]) && (j > 0)) {
      aux = T[j];
      T[j] = T[j-1];
      T[j-1] = aux;
      j--;
    };
  };
}

// Programa principal para probar el algoritmo de ordenación por inserción

int main(int argc, char *argv[]) {

    int size = atoi(argv[1]);

    high_resolution_clock::time_point tantes, tdespues;
    duration<double> transcurrido;

    int tipo = atoi(argv[2]); // 1: int, 2: float, 3: double

    // Crear el array según el tipo especificado
    if (tipo == 1) { // int
        int *T = new int[size];
        // Verificación si la memoria fue asignada exitosamente
        assert(T);
        for (int i = 0; i < size; ++i) {
            // Hacer cast a int de random()
            T[i] = static_cast<int>(random());
        }
        tantes = high_resolution_clock::now();
        insercion(T, size);
        tdespues = high_resolution_clock::now();
        transcurrido = duration_cast<duration<double>>(tdespues - tantes);
        cout << transcurrido.count();
        delete[] T;
    } else if (tipo == 2) { // float
        float *T = new float[size];
        // Verificación si la memoria fue asignada exitosamente
        assert(T);
        for (int i = 0; i < size; ++i) {
            // Hacer cast a float de random()
            T[i] = static_cast<float>(random());
        }
        tantes = high_resolution_clock::now();
        insercion(T, size);
        tdespues = high_resolution_clock::now();
        transcurrido = duration_cast<duration<double>>(tdespues - tantes);
        cout << transcurrido.count();
        delete[] T;
    } else { // double
        double *T = new double[size];
        // Verificación si la memoria fue asignada exitosamente
        assert(T);
        for (int i = 0; i < size; ++i) {
            // Hacer cast a double de random()
            T[i] = static_cast<double>(random());
        }
        tantes = high_resolution_clock::now();
        insercion(T, size);
        tdespues = high_resolution_clock::now();
        transcurrido = duration_cast<duration<double>>(tdespues - tantes);
        cout << transcurrido.count();
        delete[] T;
    }

    return 0;
}
