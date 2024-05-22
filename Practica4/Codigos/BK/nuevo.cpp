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
  double min ,j=0;
      for (int i = 0; i < graph.size(); ++i) {
        min = graph[i][j]==0?numeric_limits<double>::max() : graph[i][j];
        for (j = i; j < graph[i].size(); ++j) { 
            if (graph[i][j] > 0 &&(find(solucion.begin(),solucion.end(),i)==solucion.end() 
            &&find(solucion.begin(),solucion.end(),j)==solucion.end())) {
                cout <<graph[i][j]<<endl;                if(graph[i][j]<min){
                  min = graph[i][j];
                  cota +=graph[i][j];
                }
            }
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