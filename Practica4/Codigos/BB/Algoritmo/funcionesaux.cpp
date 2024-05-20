#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstring>
#include <set>
#include <algorithm>
#include <queue>
#include <fstream>
#include <sstream>
#include <string_view>
#include <chrono>
#include <ranges>
#include <numeric>

using namespace std;

/**
 * Función para calcular el mínimo de una matriz de distancias, excluyendo los valores de 0 y 
 * se pasan como parámetro las filas que se deben ignorar en la búsqueda del mínimo.
 * 
 * @param matriz matriz de de adyacencia entre los puntos
 * @param filas_a_ignorar filas que se deben ignorar en la búsqueda del mínimo
 * 
 * @return suma de los mínimos de cada fila
*/
double minimo(const std::vector<std::vector<double>>& matriz, const std::vector<int>& filas_a_ignorar = {}) {
    double suma_minimos = 0.0;

    for (int i = 0; i < matriz.size(); ++i) {
        if (std::ranges::find(filas_a_ignorar, i) != filas_a_ignorar.end()) { continue;}

        if (!matriz[i].empty()) {
            auto minimo_fila = std::ranges::min(matriz[i] | std::views::filter([](double valor) { return valor > 0;}),
             std::less<>(), [](double valor) { return valor; });

            if (minimo_fila < std::numeric_limits<double>::max()) {
                suma_minimos += minimo_fila;
            }
        }
    }

    return suma_minimos;
}

/**
 * Función para encontrar los números faltantes desde 0 hasta n en un vector de enteros
 * 
 * @param vec vector de enteros donde buscar
 * @param n número máximo a buscar
 * 
 * @return vector con los números faltantes
*/
std::vector<int> numeros_faltantes(const std::vector<int>& vec, int n) {
    // Crear un set con los números presentes en el vector dado
    std::set<int> presentes(vec.begin(), vec.end());

    // Encontrar los números que no están presentes
    std::vector<int> faltantes;
    for (int i : std::views::iota(0, n + 1)) {
        if (!presentes.contains(i)) {
            faltantes.push_back(i);
        }
    }

    return faltantes;
}

/**
 * @brief Estructura para almacenar los datos de un nodo en el algoritmo de Branch and Bound
 */
struct Nodo {
    vector<int> path; // Vector que almacena el orden de los nodos visitados hasta el nodo actual
    double distancia_recorrida; // Distancia recorrida hasta el nodo actual
    double cota_inferior; // Cota inferior para el nodo actual

    /**
     * @brief Constructor de la estructura Nodo
     * 
     * @param inicial vector con el orden de los nodos visitados hasta el nodo actual
     * @param dist_rec distancia recorrida hasta el nodo actual
     * @param cota_inf cota inferior para el nodo actual
     */
    Nodo(vector<int>& inicial, double dist_rec, double cota_inf) {
        path = inicial;
        distancia_recorrida = dist_rec;
        cota_inferior = cota_inf;
    }
};
/**
 * Función comparador de nodos para la cola de prioridad en el algoritmo de Branch and Bound.
*/
struct Comparador {
    bool operator()(const Nodo& a, const Nodo& b) {
        return a.distancia_recorrida > b.distancia_recorrida; // Min-Heap basado en el costo actual
    }
};


/**
 * @brief This function calculates the minimum distance required to visit
 * all the points in the vector once, to do so, it generates all the possible
 * permutations of the vector and calculates the distance needed to visit all
 * the points in the order of the permutation.
 * 
 * @note Distance from first to last point has to be calculated to make a closed path.
 * @note iota generates a sequence of numbers from 0 to n.
 * @note If needed, it can return the permutation that generates the minimum distance.
 * 
 * @param adjacencyMatrix matriz con la distancia entre los puntos
 * @param startNode nodo inicial
 * @return std::vector<int> vector con el orden de los nodos que minimiza la distancia
 */
std::vector<int> bruteForceTSP(const std::vector<std::vector<double>>& adjacencyMatrix, int startNode) {
    int numNodes = adjacencyMatrix.size();
    std::vector<int> nodes(numNodes);
    std::iota(nodes.begin(), nodes.end(), 0);
    nodes.erase(std::remove(nodes.begin(), nodes.end(), startNode), nodes.end());

    double minDistance = std::numeric_limits<double>::max();
    std::vector<int> bestPermutation;
    do {
        double distance = 0;
        int previousNode = startNode;
        for (int i = 0; i < nodes.size(); ++i) {
            distance += adjacencyMatrix[previousNode][nodes[i]];
            previousNode = nodes[i];
        }
        distance += adjacencyMatrix[previousNode][startNode];
        
        if (distance < minDistance) {
            minDistance = distance;
            bestPermutation = nodes;
        }
    } while (std::next_permutation(nodes.begin(), nodes.end()));

    std::vector<int> bestPath;
    bestPath.push_back(startNode);
    for (int node : bestPermutation) {
        bestPath.push_back(node);
    }
    bestPath.push_back(startNode);

    return bestPath;
}


/**
 * Función para resolver el problema del viajante de comercio utilizando el algoritmo de Branch and Bound.
 * La idea es la siguiente:
 *  - Se crea un nodo con el punto inicial y se agrega a la cola de prioridad.
 *  - Mientras la cola no esté vacía:
 *   - Se extrae el nodo con menor costo actual (a partir de la cota inferior y haciendo uso del comparador
 *     definido anteriormente).
 *   - Si el camino actual tiene todos los puntos añadimos el inicial para tener el camino completo y
 *    calculamos la distancia total, si es mejor que la actual, actualizamos la solución.
 *   - Si no, se generan los nodos hijos con los puntos faltantes y se agregan a la cola de prioridad.
 * Versión 2, con un mayor parecido al código presentado en las diapositivas, pero misma eficiencia.
 * 
 * @param points vector con los puntos a visitar
 * @param distancias matriz de distancias entre los puntos
 * @param inicial punto inicial
 * 
 * @return vector con el camino que minimiza la distancia total
*/
vector<int> branch_and_bound2 (vector<int>& points, vector< vector<double>> &distancias, int inicial){
    priority_queue<Nodo, vector<Nodo>, Comparador> no_visitados;
    vector<int> mejor_camino = {inicial};
    Nodo actual( mejor_camino, 0, minimo(distancias));
    no_visitados.push(actual);

    double costo_minimo = numeric_limits<double>::infinity();
    mejor_camino.clear();

    while (!no_visitados.empty()) {
        actual = no_visitados.top();
        no_visitados.pop();

        if(actual.cota_inferior < costo_minimo ){
            vector<int> faltantes = numeros_faltantes(actual.path, points.size()-1);
            for (int i = 0; i < faltantes.size(); ++i) {
                Nodo nuevo= actual;
                nuevo.path.push_back(faltantes[i]);
                nuevo.distancia_recorrida= nuevo.distancia_recorrida+ distancias[actual.path.back()][faltantes[i]];
                nuevo.cota_inferior = nuevo.distancia_recorrida + minimo(distancias, nuevo.path);
                
                if (nuevo.path.size() == points.size()) {
                    nuevo.distancia_recorrida += distancias[nuevo.path.back()][inicial];
                    nuevo.path.push_back(inicial);
                    if (nuevo.distancia_recorrida < costo_minimo) {
                        costo_minimo = nuevo.distancia_recorrida;
                        mejor_camino = nuevo.path;
                    }
                } 
                else{
                    no_visitados.push(nuevo);
                }
            }
        }
    }

    return mejor_camino;

}