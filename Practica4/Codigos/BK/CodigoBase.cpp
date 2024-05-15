#include <cmath>
#include <iostream>
#include <ostream>
#include<vector>
#include <algorithm>
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
  [[nodiscard]] constexpr auto
  distanceTo(const Point &p) const noexcept -> double {
    return std::sqrt(std::pow(p.x - x, 2) + std::pow(p.y - y, 2));
  }

  [[nodiscard]] constexpr auto getX() const noexcept -> int { return x; }
  [[nodiscard]] constexpr auto getY() const noexcept -> int { return y; }

  friend auto operator<<(std::ostream &os,
                         const Point &point) -> std::ostream & {
    os << point.x << ',' << point.y;
    return os;
  }

private:
  int x, y;
};
void printv(const vector<int> & v){
  cout <<"["<< v[0];
  for(int i = 1 ; i< v.size(); i++){
    cout <<","<< v[i];
  }
  cout << "]"<<endl;
}

int next(int k , vector<int> & asigned,const vector<vector<double>> & graph){
  do {
    asigned[k]++;
    if(graph[asigned[k-1]][asigned[k]] && (asigned.end()==find(asigned.begin(),asigned.end(),asigned[k])) && 
    (asigned[k] < graph.size() || (k == graph.size() && graph[asigned[k]][asigned[1]])) ){
      return asigned[k];
    }
  }while (asigned[k]<graph.size());
  asigned[k]=0;
  return 0;

}

void tsp (int k , vector<int> &asigned,const vector<vector<double>> &graph){
  if(k == graph.size()){
    printv(asigned);
  }
  else{
    do{
      asigned[k] = next(k,asigned,graph);
      if(asigned[k] != 0){
        tsp(k+1, asigned, graph);

      }
    }while(asigned[k] !=0);
  }
}

