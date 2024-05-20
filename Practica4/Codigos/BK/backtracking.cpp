#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;

void printv(const vector<int> &v) {
  cout << "[" << v[0];
  for (int i = 1; i < v.size(); i++) {
    cout << "," << v[i];
  }
  cout << "]" << endl;
}
double cota2(const vector<int>&solucion,const vector<vector<double>>&graph, int actual){
    double cota=0;
    for(int i =0; i<graph.size();i++){
         if(find(solucion.begin(), solucion.end(),i) ==solucion.end()){
            cota = cota + graph[actual][i];
         }
    }
   

    return cota;
}
/**
 * @brief Busca si es posible la siguiente ciudad a visitar que cumpla que no ha
 * sido visitada y que existe una arista entre la ciudad actual y la siguiente
 * ciudad que las unen.
 *
 * @param nciudad numero del nodo de la ciudad que se va a visitar
 * @param solucion vector de la posible solucion
 * @param graph matriz de adyacencia
 * @return  devuelve el numero de la siguiente ciudad a visitar o -1 si no se
 * cumplen las condiciones
 */
int siguiente(int nciudad, vector<int> &solucion,const vector<vector<double>> &graph) {
  do {
    solucion[nciudad]++;
    if (solucion[nciudad] < graph.size() &&
        (find(solucion.begin(), solucion.begin() + nciudad, solucion[nciudad]) ==
            solucion.begin() + nciudad) && (nciudad <= graph.size() - 1 && graph[solucion[nciudad]][solucion[0]] > 0)) {
      
      return solucion[nciudad];
    }
  } while (solucion[nciudad] < graph.size());
  solucion[nciudad] = -1; 
  return -1;
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
  if (nciudad == graph.size()) {
    c_actual += graph[solucion[nciudad - 1]][solucion[0]];
    if (c_actual < c_mejor) {
      c_mejor = c_actual;
      s_mejor = solucion;
    }
  } else {
    do {
      solucion[nciudad] = siguiente(nciudad, solucion, graph);
      if (solucion[nciudad] != -1) {
        tsp_backtracking(solucion, graph, nciudad + 1, c_mejor, s_mejor,c_actual +graph[solucion[nciudad - 1]][solucion[nciudad]]);
      }
    } while (solucion[nciudad] != -1);
    
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
  vector<int> solucion(tam, -1);   //Vector de soluciones 
  solucion[0] = comienzo; //comienzo

  double c_mejor = numeric_limits<double>::max(); //coste del mejor camino encontrado
  vector<int> s_mejor; //Vector de la mejor solucion
  if (atoi(argv[2])==1){
    tsp_backtracking(solucion, graph, 1, c_mejor, s_mejor, 0);

  
    cout << "Solucion : ";
    printv(s_mejor);
    cout << "Coste: " << c_mejor << endl;

  
  }
  else{
    auto start = chrono::high_resolution_clock::now();
    tsp_backtracking(solucion, graph,1 , c_mejor, s_mejor, 0);
    auto end = chrono::high_resolution_clock::now();
    cout << graph.size() << " " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    
  }
  

  return 0;
}