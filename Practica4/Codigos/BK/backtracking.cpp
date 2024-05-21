#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <vector>
#include <chrono>
#include <set>
#include <ranges>


using namespace std;

void printv(const vector<int> &v) {
  cout << "[" << v[0];
  for (int i = 1; i < v.size(); i++) {
    cout << "," << v[i];
  }
  cout << "]" << endl;
}
double calcularDistanciaTotal(const vector<vector<double>>& distancias, const vector<int>& camino) {
    double total = 0.0;
    //vector<int> usados(camino.begin(),find(camino.begin(),camino.end(),-1));
    for (int i = 0; i < camino.size() - 1; ++i) {
        total += distancias[camino[i]][camino[i + 1]];
    }
    // Asegúrate de volver al punto inicial si tu problema lo requiere (como en el problema del viajante)
    total += distancias[camino.back()][camino.front()];
    return total;
}

double cota1(const vector<vector<double>> & graph, const vector<int> & camino ,double c_actual ,double arco_menorpeso){
  return arco_menorpeso*(graph.size()-camino.size()) + c_actual;
}


/**
 * @brief Funcion para resolver el tsp con backtracking .
 * @param solucion vector de ciudades , la posicion de la ciudad indica el orden
 * en el que es visitada
 * @param graph matriz de adyacencia
 * @param nciudad numero del nodo de la ciudad que se va a visitar
 * @param c_mejor mejor coste encontrado
 * @param s_mejor mejor solucion encontrada
 * @param c_actual coste actual
 */
void tsp_backtracking(vector<int> &solucion,const vector<vector<double>> &graph, int nciudad,double &c_mejor, vector<int> &s_mejor, double c_actual) {
  c_actual += solucion.size()<=1 ?0 : graph[solucion.back()][solucion[solucion.size()-2]];
  if (solucion.size() == graph.size()) {
    printv(solucion);
    c_actual += graph[solucion.back()][solucion[0]];
    if (c_actual < c_mejor) {
      c_mejor = c_actual;
      s_mejor = solucion;
    }
  } else {
    for(int i = 0; i< graph.size();i++){
      if(find(solucion.begin(),solucion.end(),i)==solucion.end()){
        solucion.emplace_back(i);
        //c_actual = calcularDistanciaTotal(graph, solucion);
        
        tsp_backtracking(solucion,graph, nciudad+1, c_mejor, s_mejor, c_actual);
        solucion.pop_back();
        
      }
    }
    
  }
}
/**
 * @brief Función para leer una matriz de adyacencia desde un archivo de texto.
 *
 * @param nombreArchivo nombre del archivo a leer
 *
 * @return matriz de adyacencia leída desde el archivo
 */
vector<vector<double>> leerMatrizDesdeArchivo(const string &nombreArchivo) {
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

int main(int argc, char *argv[]) {

  if (argc != 3) {
    cerr << "Uso: " << argv[0] << " <archivo> <tipoejecucion>"  << endl;
    return 1;
  }

  string nombreArchivo = argv[1];
  vector<vector<double>> graph = leerMatrizDesdeArchivo(nombreArchivo);
  int comienzo = 0;
  int tam = graph.size();
  vector<int> solucion;   //Vector de soluciones 
  solucion.emplace_back(0); //comienzo

  double c_actual=0,c_mejor = numeric_limits<double>::max(); //coste del mejor camino encontrado
  vector<int> s_mejor; //Vector de la mejor solucion
  if (atoi(argv[2])==1){

    tsp_backtracking(solucion, graph, 1, c_mejor, s_mejor, c_actual);
    cout << "Solucion : ";
    printv(s_mejor);
    cout << "Coste: " << c_mejor << endl;  
  }
  else{
    auto start = chrono::high_resolution_clock::now();
    tsp_backtracking(solucion, graph,1 , c_mejor, s_mejor, c_actual);
    auto end = chrono::high_resolution_clock::now();
    cout << graph.size() << " " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    
  }
  

  return 0;
}