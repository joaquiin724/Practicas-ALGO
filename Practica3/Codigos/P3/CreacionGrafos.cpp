#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include <iomanip> // Para std::setw
#include <limits>

using namespace std;

class Point {
private:
    int x, y;

public:
    Point(int x, int y) : x(x), y(y) {}
    Point (){
        x = 0;
        y = 0;
    }

    /**
     * @brief Calculates the distance between two points using the 
     * Euclidean distance formula.
     * 
     * @param p other point
     * @return Distance between the two points
     */
    double distanceTo(const Point &p) const {
        return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    friend std::ostream &operator<<(std::ostream &os, const Point &point) {
        os << "(" << point.x << "," << point.y << ")";
        return os;
    }

    friend istream &operator>>(istream &is, Point &point) {
        is >> point.x >> point.y;
        return is;
    }
};

// Debe estar la matriz inicializada a 0
void creacionGrafos(const vector<Point>&vec, vector<vector<double>> &matriz){
    int size=vec.size();

    srand(time(NULL));

    for (int i=0; i<size; i++){
        // Num nodos que conectaremos con el nodo i
        int conexiones=rand()%(size-1)+1;
        for(int j=0; j<conexiones; j++){
            // Nodo a conectar con el nodo i
            int nodo_conectar;
            do{
                nodo_conectar=rand()%size;
            } while(nodo_conectar==i);
            // Añadimos su distancia a la matriz
            matriz[i][nodo_conectar]=vec[i].distanceTo(vec[nodo_conectar]);
        }
    }
    
    int p_inicio=rand()%size;

    for(int i=0; i<size; i++){
        matriz[p_inicio][i]=vec[p_inicio].distanceTo(vec[i]);
        matriz[i][i]=0;
    }

}

void mostrarVector(const std::vector<Point>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

// Función para mostrar una matriz en un archivo
void mostrarMatriz(std::ofstream &salida, const std::vector<std::vector<double>>& matriz) {
    // Configurar la salida para mostrar números con tres decimales
    salida << std::fixed << std::setprecision(3);

    // Iterar sobre cada fila de la matriz
    for (const auto& fila : matriz) {
        // Iterar sobre cada elemento de la fila y mostrarlo
        for (double elemento : fila) {
            if(elemento==numeric_limits<double>::max())
                salida << std::setw(5) << "INF" << "\t";
            else
                // Asegurar que todos los números se alineen correctamente usando setw
                salida << std::setw(5) << elemento << "\t"; // Separador de columnas
        }
        salida << std::endl; // Nueva línea para la siguiente fila
    }
}


int main (int argc, char *argv[]) {

    if (argc != 3){
        cout << "Uso: " << argv[0] << " <nombreArchivoEntrada> <nombreArchivoSalida>" << endl;
        return 1;
    }
    
    ifstream lectura((string)argv[1]);

    if (!lectura.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    string linea;
    Point point;
    vector<Point> puntos;

    while(lectura >> point){
        puntos.emplace_back(point);
    }

    lectura.close();

    ofstream escritura((string)argv[2]);

    if (!escritura.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    int dimension=puntos.size();
    vector<vector<double>> matriz(dimension, vector<double>(dimension, numeric_limits<double>::max()));
    
    creacionGrafos(puntos, matriz);
    mostrarMatriz(escritura, matriz);

    escritura.close();

    return 0;
}