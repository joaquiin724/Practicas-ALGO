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
/**
 * @brief Calcula la cota segun el arco de menor peso , multiplica el arco de menor peso de 
  * la matriz de adyacencia por el numero de nodos no visitados y le suma el coste actual
 * 
 * @param graph matriz de adyacencia
 * @param solucion vector de puntos visitados
 * @param c_actual coste del camino actual
 * @return double cota
 */
double cota1(const vector<vector<double>> & graph, const vector<int> & solucion ,double c_actual ,double arco_menorpeso){
  return arco_menorpeso*(graph.size()-solucion.size() +1) + c_actual;
}
/**
 * @brief Calcula el menor coste de salir de cada nodo visitado  y le suma el coste actual
 * 
 * @param graph matriz de adyacencia
 * @param solucion vector de puntos visitados
 * @param c_actual coste del camino actual
 * @return double cota
 */
double cota2(const vector<vector<double>> & graph, const vector<int> & solucion ,double c_actual ){
  double cota = 0;
  vector<double>v;
  double min = numeric_limits<double>::max();
      for (int i = 0; i < graph.size(); ++i) {
        if ((find(solucion.begin(),solucion.end(),i)==solucion.end())){
          v =graph[i];
          sort(v.begin(),v.end());
          cota+=v[1];
        }
    }
  return cota+c_actual;
}
/**
 * @brief Calcula la media del menor coste de salir y entrar a un nodo no visitado y le suma el coste actual
 * 
 * @param graph matriz de adyacencia
 * @param solucion vector de puntos visitados
 * @param c_actual coste del camino actual
 * @return double cota
 */
double cota3(const vector<vector<double>> & graph, const vector<int> & solucion ,double c_actual ){
  double cota = 0;
  vector<double>v;
  double min = numeric_limits<double>::max();
      for (int i = 0; i < graph.size(); ++i) {
        if ((find(solucion.begin(),solucion.end(),i)==solucion.end())){
          v =graph[i];
          sort(v.begin(),v.end());
          cota+=(v[1] + v[2])/2;
        }
    }
  return cota+c_actual;
}

/**
 * @brief Funcion para resolver el tsp con backtracking .
 * @param solucion vector de ciudades , la posicion de la ciudad indica el orden
 * en el que es visitada
 * @param graph graph de adyacencia
 * @param c_mejor mejor coste encontrado
 * @param s_mejor mejor solucion encontrada
 * @param c_actual coste actual
  * @param arco_menorpeso arco de menor peso del grafo (para no tener que calcularlo siempre)
 *@param cota cota a utilizar 
 */
void tsp_backtracking(vector<int> &solucion,const vector<vector<double>> &graph,double &c_mejor, vector<int> &s_mejor, double c_actual,int arco_menorpeso,int cota=0) {
  c_actual += solucion.size()<=1 ?0 : graph[solucion.back()][solucion[solucion.size()-2]];
  if (solucion.size() == graph.size()) {
    c_actual += graph[solucion.back()][solucion[0]];
    if (c_actual < c_mejor) {
      c_mejor = c_actual;
      s_mejor = solucion;
    }
  } else {
    for(int i = 1; i< graph.size();i++){
      if(find(solucion.begin(),solucion.end(),i)==solucion.end()){
        double acotacion;
        if(cota==1){
          acotacion = cota1(graph, solucion, c_actual,arco_menorpeso);
        }else if (cota==2) {
          acotacion = cota2(graph, solucion, c_actual);
        }else if(cota==3){
          acotacion = cota3(graph, solucion, c_actual);
        }
        else{
          acotacion = 0;
        }
        if (acotacion<c_mejor){
          solucion.emplace_back(i);
          tsp_backtracking(solucion,graph,  c_mejor, s_mejor, c_actual,arco_menorpeso,cota);
          solucion.pop_back();
       } 
        
      }
    }
    
  }
}

/**
 * @brief Función para leer una graph de adyacencia desde un archivo de texto.
 *
 * @param nombreArchivo nombre del archivo a leer
 *
 * @return graph de adyacencia leída desde el archivo
 */
vector<vector<double>> leergraphDesdeArchivo(const string &nombreArchivo) {
  ifstream archivo(nombreArchivo);
  vector<vector<double>> graph;

  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo." << endl;
    return graph;
  }

  string linea;
  while (getline(archivo, linea)) {
    istringstream ss(linea);
    vector<double> fila;
    double valor;
    while (ss >> valor) {
      fila.push_back(valor);
    }
    graph.push_back(fila);
  }

  archivo.close();

  return graph;
}
double encontrarArcoMenorPeso(const vector<vector<double>>& graph) {
    double minPeso = numeric_limits<double>::max();

    for (int i = 0; i < graph.size(); ++i) {
        for (int j = i + 1; j < graph[i].size(); ++j) { 
            if (graph[i][j] < minPeso) {
                minPeso = graph[i][j];
            }
        }
    }

    return minPeso;
}

int main(int argc, char *argv[]) {

  if (argc != 4) {
    cerr << "Uso: " << argv[0] << " <archivo> <tipoejecucion> <tipocota>"  << endl;
    return 1;
  }

  string nombreArchivo = argv[1];
  vector<vector<double>> graph = leergraphDesdeArchivo(nombreArchivo);
  int comienzo = 0;
  int tam = graph.size();
  vector<int> solucion;   //Vector de soluciones 
  solucion.emplace_back(0); //comienzo

  double c_actual=0,c_mejor = numeric_limits<double>::max(); //coste del mejor camino encontrado
  vector<int> s_mejor; //Vector de la mejor solucion
  double arco_menorpeso = encontrarArcoMenorPeso(graph);
  int cota = atoi(argv[3]);
  if (atoi(argv[2])==1){

    tsp_backtracking(solucion, graph, c_mejor, s_mejor, c_actual,arco_menorpeso,cota);
    cout << "Solucion : ";
    printv(s_mejor);
    cout << "Coste: " << c_mejor << endl;  
  }
  else{
    auto start = chrono::high_resolution_clock::now();
    tsp_backtracking(solucion, graph, c_mejor, s_mejor, c_actual,arco_menorpeso);
    auto end = chrono::high_resolution_clock::now();
    cout << graph.size() << " " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;
    
  }
  return 0;
}