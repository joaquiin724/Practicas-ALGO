#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>

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
void creacionGrafos(const vector<Point>&vec, vector<vector<int>> &matriz){
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

// Función para mostrar una matriz en la consola
void mostrarMatriz(const std::vector<std::vector<int>>& matriz) {
    // Iterar sobre cada fila de la matriz
    for (const auto& fila : matriz) {
        // Iterar sobre cada elemento de la fila y mostrarlo
        for (int elemento : fila) {
            std::cout << elemento << "\t"; // Separador de columnas
        }
        std::cout << std::endl; // Nueva línea para la siguiente fila
    }
}


int main (int argc, char *argv[]) {

    if (argc != 2){
        cout << "Error en los argumentos" << endl;
        return 1;
    }
    
    ifstream archivo((string)argv[1]);

    if (!archivo.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    string linea;
    Point point;
    vector<Point> puntos;

    while(archivo >> point){
        puntos.push_back(point);
    }

    archivo.close();
    mostrarVector(puntos);
    int dimension=puntos.size();
    vector<vector<int>> matriz(dimension, vector<int>(dimension, 0));
    creacionGrafos(puntos, matriz);
    mostrarMatriz(matriz);




    return 0;
}