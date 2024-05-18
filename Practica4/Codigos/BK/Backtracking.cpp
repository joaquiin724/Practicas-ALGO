#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
class Point {
public:
  constexpr Point(int x, int y) noexcept : x(x), y(y) {}

  /**
   * @brief Calculates the distance between two points using the
   * Euclidean distance formula.
   *
   * @param p other point
   * @return Distance between the two points
   */
  [[nodiscard]] constexpr auto distanceTo(const Point &p) const noexcept
      -> double {
    return std::sqrt(std::pow(p.x - x, 2) + std::pow(p.y - y, 2));
  }

  [[nodiscard]] constexpr auto getX() const noexcept -> int { return x; }
  [[nodiscard]] constexpr auto getY() const noexcept -> int { return y; }

  friend auto operator<<(std::ostream &os, const Point &point)
      -> std::ostream & {
    os << point.x << ',' << point.y;
    return os;
  }

private:
  int x, y;
};

double bound1(const vector<int> &path, const vector<vector<double>> &graph) {
  double bound = 0.0;
  for (int i = 0; i < graph.size(); i++) {
    if (find(path.begin(), path.end(), i) == path.end()) {
      double minDistance = numeric_limits<double>::max();
      for (int j = 0; j < graph.size(); j++) {
        if (i != j && graph[i][j] < minDistance) {
          minDistance = graph[i][j];
        }
      }
      bound += minDistance;
    }
  }
  return bound;
}

double bound2(const vector<int> &path, const vector<vector<double>> &graph) {
  double bound = 0.0;
  for (int i = 0; i < graph.size(); i++) {
    if (find(path.begin(), path.end(), i) == path.end()) {
      double minDistance = numeric_limits<double>::max();
      for (int j : path) {
        if (graph[i][j] < minDistance) {
          minDistance = graph[i][j];
        }
      }
      bound += minDistance;
    }
  }
  return bound;
}

double bound3(const vector<int> &path, const vector<vector<double>> &graph) {
  double bound = 0.0;
  int lastVisited = path.back();
  for (int i = 0; i < graph.size(); i++) {
    if (find(path.begin(), path.end(), i) == path.end()) {
      bound += graph[lastVisited][i];
    }
  }
  return bound;
}

double bound4(const vector<int> &path, const vector<vector<double>> &graph) {
  double bound = 0.0;
  int firstVisited = path.front();
  for (int i = 0; i < graph.size(); i++) {
    if (find(path.begin(), path.end(), i) == path.end()) {
      bound += graph[firstVisited][i];
    }
  }
  return bound;
}

bool promising(int node, const vector<int> &path,
               const vector<vector<double>> &graph,
               double (*bound)(const vector<int> &,
                               const vector<vector<double>> &)) {
  if (find(path.begin(), path.end(), node) != path.end()) {
    return false;
  }
  double boundValue = bound(path, graph);
  // Implementa la lógica para decidir si el nodo es prometedor en base a la
  // cota
  return true;
}

void tsp(int node, vector<int> &path, const vector<vector<double>> &graph,
         double (*bound)(const vector<int> &, const vector<vector<double>> &)) {
  path.push_back(node);
  if (path.size() == graph.size()) {
    // Imprime la solución si todos los nodos han sido visitados
    for (int node : path) {
      cout << node << " ";
    }
    cout << endl;
  } else {
    for (int i = 0; i < graph.size(); i++) {
      if (promising(i, path, graph, bound)) {
        tsp(i, path, graph, bound);
      }
    }
  }
  path.pop_back();
}
void printv(const vector<int> &v) {
  cout << "[" << v[0];
  for (int i = 1; i < v.size(); i++) {
    cout << "," << v[i];
  }
  cout << "]" << endl;
}
/**
 *
 *devuelve 0 si no queda ningun vertice seleccionable para la posicion
 *
 */
int next(int k, vector<int> &asigned, const vector<vector<double>> &graph) {
  do {
    asigned[k]++;
    if (graph[asigned[k - 1]][asigned[k]] &&
        (asigned.end() == find(asigned.begin(), asigned.end(), asigned[k])) &&
        (asigned[k] < graph.size() ||
         (k == graph.size() && graph[asigned[k]][asigned[1]]))) {
      return asigned[k];
    }
  } while (asigned[k] < graph.size());
  asigned[k] = 0;
  return 0;
}

void tsp1(int k, vector<int> &asigned, const vector<vector<double>> &graph) {
  if (k == graph.size()) {
    printv(asigned);
  } else {
    do {
      asigned[k] = next(k, asigned, graph);
      if (asigned[k] != 0) {
        tsp1(k + 1, asigned, graph);
      }
    } while (asigned[k] != 0);
  }
}
// Función para leer la matriz desde un archivo
void lecturaMatriz(ifstream &leer, vector<vector<double>> &matrix) {
  string line;
  while (getline(leer, line)) {
    vector<double> row;
    stringstream ss(line);
    string val_str;
    while (ss >> val_str) {
      if (val_str == "INF") {
        row.push_back(numeric_limits<double>::max());
      } else {
        row.push_back(stod(val_str));
      }
    }
    matrix.push_back(row);
  }
}
int main(int argc, char *argv[]) {
  ifstream lectura(argv[1]);

  int inicio = atoi(argv[2]);
  if (!lectura.is_open()) {
    cout << "Error al abrir el archivo" << endl;
    return 1;
  }
  vector<vector<double>> graph;
  
  lecturaMatriz(lectura, graph);
  if (graph.empty()) {
    cerr << "No se pudo leer la matriz desde el archivo." << endl;
    return 1;
  }
  vector<int> sol(graph.size() +1,0);
  sol[0]=inicio;
  tsp1(inicio, sol, graph);
  return 0;
}
