#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstring>
#include <algorithm>
#include <queue>
#include <fstream>
#include <sstream>
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
double minimo(const vector<vector<double>>& matriz, const vector<int>& filas_a_ignorar = vector<int>()) {
    double suma_minimos = 0.0;

    for (int i = 0; i < matriz.size(); ++i) {
        // Verificar si la fila actual debe ser ignorada
        if (find(filas_a_ignorar.begin(), filas_a_ignorar.end(), i) != filas_a_ignorar.end()) {
            continue; // Saltar esta fila
        }

        if (!matriz[i].empty()) {
            // Encontrar el mínimo de la fila excluyendo los valores de 0
            double minimo_fila = numeric_limits<double>::infinity();
            for (double valor : matriz[i]) {
                if (valor > 0 && valor < minimo_fila) {
                    minimo_fila = valor;
                }
            }
            // Asegurar que el mínimo es menor que infinito y sumarlo
            if (minimo_fila != numeric_limits<double>::infinity()) {
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
vector<int> numeros_faltantes(const vector<int>& vec, int n) {
    vector<bool> presente(n + 2, false); // Vector para marcar los números presentes, de 0 a n

    // Marcar los números presentes en el vector dado
    for (int num : vec) {
        if (num >= 0 && num <= n) {
            presente[num] = true;
        }
    }

    // Encontrar los números que no están presentes
    vector<int> faltantes;
    for (int i = 0; i <= n; ++i) {
        if (!presente[i]) {
            faltantes.push_back(i);
        }
    }

    return faltantes;
}


/**
 * @brief Estructura para almacenar los datos de un nodo en el algoritmo de Branch and Bound
*/
struct Nodo {
    /**
     * @brief Miembros de la estructura Nodo
    */
    vector<int> path;

    /**
     * @brief Distancia recorrida hasta el nodo actual
    */
    double distancia_recorrida;

    /**
     * @brief Cota inferior para el nodo actual
    */
    double cota_inferior;

    /**
     * @brief Constructor de la estructura Nodo
    */
    Nodo(vector<int>&inicial, double dist_rec, double cota_inf) {
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
 * Función para resolver el problema del viajante de comercio utilizando el algoritmo de Branch and Bound.
 * La idea es la siguiente:
 *  - Se crea un nodo con el punto inicial y se agrega a la cola de prioridad.
 *  - Mientras la cola no esté vacía:
 *     - Se extrae el nodo con menor costo actual (a partir de la cota inferior y haciendo uso del comparador
 *      definido anteriormente).
 *    - Si el camino actual tiene todos los puntos menos unos, sabemos de forma determinada cual queda
 *      mediante la función faltantes de antes, por lo que se calcula la distancia a dicho punto y al inicial
 *     y se agrega a la solución si es mejor que la actual.
 *   - Si no, se generan los nodos hijos con los puntos faltantes y se agregan a la cola de prioridad.
 * Destacar que esta idea es un poco diferente a la presentada en las diapositivas, pero la eficiencia
 * es la misma.
 * 
 * @param points vector con los puntos a visitar
 * @param distancias matriz de distancias entre los puntos
 * @param inicial punto inicial
 * 
 * @return vector con el camino que minimiza la distancia total
*/
vector<int> Branch_and_Bound (vector<int>& points, vector< vector<double>> &distancias, int inicial){
    priority_queue<Nodo, vector<Nodo>, Comparador> no_visitados;
    vector<int> mejor_camino= {inicial};
    Nodo actual( mejor_camino, 0, minimo(distancias));
    no_visitados.push(actual);

    double costo_minimo = numeric_limits<double>::infinity();
    mejor_camino.clear();

    while (!no_visitados.empty()) {
        actual = no_visitados.top();
        no_visitados.pop();

        if (actual.path.size() == points.size()-1) {
            vector<int> faltantes= numeros_faltantes(actual.path, points.size()-1);
            actual.distancia_recorrida += distancias[actual.path.back()][faltantes[0]];
            actual.distancia_recorrida += distancias[faltantes[0]][inicial];
            actual.path.push_back(faltantes[0]);
            actual.path.push_back(inicial);
            if (actual.distancia_recorrida < costo_minimo) {
                costo_minimo = actual.distancia_recorrida;
                mejor_camino = actual.path;
            }
        } 
        else { 
            if(actual.cota_inferior < costo_minimo ){
                vector<int> faltantes = numeros_faltantes(actual.path, points.size()-1);
                for (int i = 0; i < faltantes.size(); ++i) {
                    Nodo nuevo= actual;
                    nuevo.path.push_back(faltantes[i]);
                    nuevo.distancia_recorrida= nuevo.distancia_recorrida+ distancias[actual.path.back()][faltantes[i]];
                    nuevo.cota_inferior = nuevo.distancia_recorrida + minimo(distancias, nuevo.path);
                    no_visitados.push(nuevo);
                }
            }
        }
    }

    return mejor_camino;

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
vector<int> Branch_and_Bound2 (vector<int>& points, vector< vector<double>> &distancias, int inicial){
    priority_queue<Nodo, vector<Nodo>, Comparador> no_visitados;
    vector<int> mejor_camino= {inicial};
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

/**
 * @brief Función para calcular la distancia total de un camino dado
 * 
 * @param distancias matriz de distancias entre los puntos
 * @param camino vector con el orden de los nodos a visitar
 * 
 * @return distancia total del camino
*/
double calcularDistanciaTotal(const vector<vector<double>>& distancias, const vector<int>& camino) {
    double total = 0.0;
    for (int i = 0; i < camino.size() - 1; ++i) {
        total += distancias[camino[i]][camino[i + 1]];
    }
    // Asegúrate de volver al punto inicial si tu problema lo requiere (como en el problema del viajante)
    total += distancias[camino.back()][camino.front()];
    return total;
}


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
 * @brief Función para leer una matriz de adyacencia desde un archivo de texto.
 * 
 * @param nombreArchivo nombre del archivo a leer
 * 
 * @return matriz de adyacencia leída desde el archivo
*/
vector<vector<double>> leerMatrizDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<vector<double>> matriz;

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return matriz;
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream ss(linea);
        vector<double> fila;
        double valor;
        while (ss >> valor) {
            fila.push_back(valor);
        }
        matriz.push_back(fila);
    }

    archivo.close();

    return matriz;
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <archivo_matriz> <valor_inicial>" << endl;
        return 1;
    }

    string nombreArchivo = argv[1];
    int inicial=atoi(argv[2]);

    // Lectura de la matriz desde el archivo
    vector<vector<double>> matriz = leerMatrizDesdeArchivo(nombreArchivo);
    if (matriz.empty()) {
        cerr << "No se pudo leer la matriz desde el archivo." << endl;
        return 1;
    }
    
    // if (argc < 3) {
    //     std::cerr << "Usage: " << argv[0] << " <size or filename> <mode>" << std::endl;
    //     return 1;
    // }

    vector<int> solucion;
    vector<int> puntos;

    for (int i = 0; i < matriz.size(); ++i) {
        puntos.push_back(i);
    }
    solucion= Branch_and_Bound(puntos, matriz, inicial);

    for (int i = 0; i < solucion.size(); ++i) {
        cout << solucion[i] << " ";
    }
    cout << endl;

    // Calcular la distancia total
    cout << "Distancia total: " << calcularDistanciaTotal(matriz, solucion) << endl;

    vector<int> solucion_fuerza_bruta = bruteForceTSP(matriz, inicial);
    for (int i = 0; i < solucion_fuerza_bruta.size(); ++i) {
        cout << solucion_fuerza_bruta[i] << " ";
    }
    cout << endl;

    // Calcular distancia total
    cout << "Distancia total: " << calcularDistanciaTotal(matriz, solucion_fuerza_bruta) << endl;

    // if (strcmp(argv[2], "1") == 0) { // Random or Graph Results
    //     const int VEC_SIZE = atoi(argv[1]);
    //     std::vector<Point> approximatePath; 
    //     std::vector<Point> path;
    //     approximatePath.reserve(VEC_SIZE);
    //     path.reserve(VEC_SIZE);
        
    //     srand(time(NULL));

    //     for (int i = 0; i < VEC_SIZE; ++i) {
    //         int x = rand() % 100 - 50;
    //         int y = rand() % 100 - 50;
    //         approximatePath.emplace_back(Point(x, y));
    //         path.emplace_back(Point(x, y));
    //     }

    //     /*------------------------|Para graficar los grafos|------------------*/
    //     std::ofstream outputFile("tsp_results.csv");
    //     BranchBound solver(approximatePath);
    //     solver.getSolution({path[0]}, 0);
    //     path = solver.getBestPath();

    //     outputFile << std::endl;
    //     for (const Point& point : path) {
    //         outputFile << point.getX() << "," << point.getY() << std::endl;
    //     }

    //     //-----------------------|Fin graficar resultados|---------------------*/
    // } 
    // else if (strcmp(argv[2], "2") == 0) { // Get the distance of Cities
    //     std::string file = argv[1];
    //     std::ifstream input(file);
    //     std::vector<Point> points;
    //     double x, y;
    //     int size;
    //     int pos;
    //     input >> size;
    //     points.reserve(size);
    //     for (int i = 0; i < size; ++i) {
    //         input >> pos >> x >> y;
    //         points.emplace_back(Point(x, y));
    //     }
    //     input.close();
    //     std::cout << std::fixed;
    //     std::cout.precision(2);
    //     BranchBound solver(points);
    //     solver.getSolution({points[0]}, 0);
    //     std::cout << size << " " << solver.getBestSolution() << std::endl;
    // }

    return 0;
}
