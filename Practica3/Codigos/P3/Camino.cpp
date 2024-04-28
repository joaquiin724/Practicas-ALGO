#include <cmath>
#include <vector>
#include <iostream>
#include <chrono>
#include <limits>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <list>



using namespace std;

class Point {
public:
    Point(int x, int y) : x(x), y(y) {}

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
        os << "" << point.x << "," << point.y << "";
        return os;
    }

private:
    int x, y;
};


class Grafo {
    private:
    list<list<Point>> grafo;

    Grafo(const vector<Point> &puntos){
        list<Point> aux;
        srand(time(NULL));
        int randomElement = rand() % puntos.size();

        for (int i = 0; i < puntos.size(); i++){
            aux.push_back(puntos[i]);
            if (i==randomElement){
                for (int j = 0; j<puntos.size(); ++j){
                    if (j != randomElement ){
                        aux.push_back(puntos[j]);
                    }
                }
            }
            grafo.push_back(aux);
            aux.clear();
        }
        


        for(list<list<Point>>::iterator it= grafo.begin(); it!=grafo.end(); ++it){

        }


        
    }


}

int main (int argc, char * argv[]){


    return 0;
}