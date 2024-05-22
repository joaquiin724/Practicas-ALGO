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

int main() {
  vector<vector<double>> graph = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
  };
  vector<int> solucion = {0, 1};
  double c_actual = 0;
  std::cout<< cota2(graph, solucion, 5) << endl;
  return 0;
}