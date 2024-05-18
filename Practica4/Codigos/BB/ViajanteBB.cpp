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
 * @brief Class which represents a point in a 2D plane.
 * @note [[nodiscard]] is an attribute that tells the compiler to issue a warning if the return value of a function is ignored.
 * @note constexpr is an attribute that tells the compiler that a function can be evaluated at compile time.
 * @note noexcept is an attribute that tells the compiler that a function does not throw exceptions.
 * @note -> is a new syntax that allows the compiler to deduce the return type of a function.
 * 
 * 
 */
class Point {
public:
    constexpr Point(int x, int y) noexcept : x(x), y(y) {}

    [[nodiscard]] constexpr auto distanceTo(const Point &p) const noexcept -> double {
        return std::sqrt(std::pow(p.x - x, 2) + std::pow(p.y - y, 2));
    }

    [[nodiscard]] constexpr auto getX() const noexcept -> int { return x; }
    [[nodiscard]] constexpr auto getY() const noexcept -> int { return y; }

    bool operator==(const Point &p) const {
        return x == p.x && y == p.y;
    }

    friend auto operator<<(std::ostream &os, const Point &point) -> std::ostream & {
        os << point.x << ',' << point.y;
        return os;
    }

private:
    int x, y;
};

class Matrix {
public:
    Matrix(int size) noexcept : matrix(size, std::vector<double>(size, 0)) {}
    
    [[nodiscard]] auto getDistance(int i, int j) const noexcept -> double {
        return matrix[i][j];
    }

    void initializeMatrix(const std::vector<Point>& points) {
        for (int i = 0; i < points.size(); ++i) {
            for (int j = 0; j < points.size(); ++j) {
                if (i == j) {
                    matrix[i][j] = std::numeric_limits<double>::infinity();
                    continue;
                }
                matrix[i][j] = points[i].distanceTo(points[j]);
            }
        }
    }
private:
    std::vector<std::vector<double>> matrix;
};




double totalDistance(const std::vector<Point>& points) {
    double distance = 0;
    for (int i = 0; i < points.size() - 1; ++i) {
        distance += points[i].distanceTo(points[i + 1]);
    }
    distance += points.back().distanceTo(points.front());
    return distance;
}

std::vector<Point> nearestNeighborTSP(const std::vector<Point>& points) {
    std::vector<Point> path;
    std::vector<bool> visited(points.size(), false);
    path.reserve(points.size());
    path.emplace_back(points[0]);
    visited[0] = true;

    for (int i = 0; i < points.size() - 1; ++i) {
        double minDistance = std::numeric_limits<double>::max();
        int nearestNeighbor = -1;
        for (int j = 0; j < points.size(); ++j) {
            if (!visited[j]) {
                double distance = path[i].distanceTo(points[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestNeighbor = j;
                }
            }
        }
        path.emplace_back(points[nearestNeighbor]);
        visited[nearestNeighbor] = true;
    }

    return path;
}

class BranchBound {
private:
    double bestSolution;
    std::vector<Point> bestPath;
    std::vector<Point> path;
public:
    BranchBound(const std::vector<Point>& points) {
        path = points;
        bestPath = path;
        bestSolution = totalDistance(bestPath);
    }

    double getBestSolution() {
        return bestSolution;
    }

    std::vector<Point> getBestPath() {
        return bestPath;
    }

    void getSolution(const std::vector<Point>& currentPath, const double pathDistance) {
        if (currentPath.size() == path.size()) {
            double totalDist = pathDistance + currentPath.back().distanceTo(currentPath[0]);
            if (totalDist < bestSolution) {
                bestSolution = totalDist;
                bestPath = currentPath;
            }
            return;
        }

        for (const Point& point : path) {
            if (std::find(currentPath.begin(), currentPath.end(), point) == currentPath.end()) {
                double newDistance = pathDistance + currentPath.back().distanceTo(point);

                if (newDistance < bestSolution * currentPath.size() / bestPath.size()) {
                    if (newDistance < bestSolution * currentPath.size() / bestPath.size()) {
                        std::cout << "projectedDistance: " << newDistance << std::endl;
                        std::cout << "bestSolution: " << bestSolution * currentPath.size() / bestPath.size() << std::endl;
                    }
                    std::vector<Point> newPath = currentPath;
                    newPath.emplace_back(point);
                    getSolution(newPath, newDistance);
                }
            }
        }
    }
};



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


struct Nodo {
    vector<int> path;
    double distancia_recorrida;
    double cota_inferior;

    // Constructor para inicializar los miembros del struct
    Nodo(vector<int>&inicial, double dist_rec, double cota_inf) {
        path = inicial;
        distancia_recorrida = dist_rec;
        cota_inferior = cota_inf;
    }
};

// Comparador personalizado
struct Comparador {
    bool operator()(const Nodo& a, const Nodo& b) {
        return a.distancia_recorrida > b.distancia_recorrida; // Min-Heap basado en el costo actual
    }
};

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

        // // Mostrar el camino actual
        // for (int i = 0; i < actual.path.size(); ++i) {
        //     cout << actual.path[i] << " ";
        // }
        // cout << endl;

        // // Mostrar cota inferior
        // cout << "Cota inferior: " << actual.cota_inferior << endl;

        if (actual.path.size() == points.size()-1) {
            vector<int> faltantes= numeros_faltantes(actual.path, points.size()-1);
            actual.distancia_recorrida += distancias[actual.path.back()][faltantes[0]];
            actual.distancia_recorrida += distancias[faltantes[0]][inicial];
            actual.path.push_back(faltantes[0]);
            actual.path.push_back(inicial);
            if (actual.distancia_recorrida < costo_minimo) {
                // // Mostrar el camino actual
                // cout << "------------------------------------\n"<< endl;
                // for (int i = 0; i < actual.path.size(); ++i) {
                //     cout << actual.path[i] << " ";
                // }
                // cout << endl;
                // cout << "------------------------------------\n"<< endl;
                costo_minimo = actual.distancia_recorrida;
                mejor_camino = actual.path;
            }
        } 
        else { 
            if(actual.cota_inferior < costo_minimo){
                vector<int> faltantes = numeros_faltantes(actual.path, points.size()-1);
                for (int i = 0; i < faltantes.size(); ++i) {
                    Nodo nuevo= actual;
                    nuevo.path.push_back(faltantes[i]);
                    nuevo.distancia_recorrida= nuevo.distancia_recorrida+ distancias[actual.path.back()][faltantes[i]];
                    nuevo.cota_inferior = nuevo.distancia_recorrida + minimo(distancias, nuevo.path);
                    // // MOstrar el path de nuevo
                    // for (int i = 0; i < nuevo.path.size(); ++i) {
                    //     cout << nuevo.path[i] << " ";
                    // }
                    // cout << endl;
                    // // Mostrar la suma para cota_inferior
                    // cout << "Cota inferior: " << nuevo.cota_inferior << "=" << nuevo.distancia_recorrida << "(" << actual.distancia_recorrida<<"+"<<distancias[actual.path.back()][faltantes[i]]<<")+" << minimo(distancias,nuevo.path) << endl;
                    no_visitados.push(nuevo);
                }
            }
        }
    }

    return mejor_camino;

}

// Función para calcular la distancia total del camino
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
 * @param points which will be used to calculate the minimum distance
 * @return minimum distance to visit all the points
 */
vector<int> encontrarMejorCamino(const vector<vector<double>>& distancias, int nodoInicial) {
    int n = distancias.size();
    vector<int> permutation(n);
    iota(permutation.begin(), permutation.end(), 0);

    double minDistance = numeric_limits<double>::max();
    vector<int> bestPermutation;
    do {
        // Asegurar que la permutación comience desde el nodo inicial
        if (permutation.front() != nodoInicial) continue;

        double distance = calcularDistanciaTotal(distancias, permutation);

        // Añadir punto inicial al final de la permutación
        distance += distancias[permutation.back()][permutation.front()];

        if (distance < minDistance) {
            minDistance = distance;
            bestPermutation = permutation;
        }
    } while (next_permutation(permutation.begin(), permutation.end()));

    // Añadir nodo inicial al final de la mejor permutación
    bestPermutation.push_back(bestPermutation.front());

    return bestPermutation;
}

// Función para leer una matriz desde un archivo
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

    // Definir una matriz 5x5
    // vector<vector<double>> matriz = {
    //     {0, 14, 4, 11, 18},
    //     {14, 0, 5, 7, 7},
    //     {4, 5, 0, 9, 17},
    //     {11, 7, 9, 0, 4},
    //     {18, 7, 17, 4, 0}
    // };

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

    vector<int> solucion_fuerza_bruta = encontrarMejorCamino(matriz, inicial);
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
