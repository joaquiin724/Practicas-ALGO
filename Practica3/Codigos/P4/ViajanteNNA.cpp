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


void improve2Opt(std::vector<Point>& path) {
    bool improvement = true;
    while (improvement) {
        improvement = false;
        int n = path.size();
        for (int i = 0; i <= n - 2; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double oldDistance = path[i].distanceTo(path[(i + 1) % n]) + path[j].distanceTo(path[(j + 1) % n]);
                double newDistance = path[i].distanceTo(path[j]) + path[(i + 1) % n].distanceTo(path[(j + 1) % n]);
                if (newDistance < oldDistance) {
                    std::reverse(path.begin() + i + 1, path.begin() + j + 1);
                    improvement = true;
                }
            }
        }
    }
}
/**
 * @brief Greedy algorithm that approximates the shortest path to visit all the 
 * points in a given tour. The metodology is to start at the beginning and 
 * in each step, visit the nearest neighbor that hasn't been visited yet.
 * 
 * @param points 
 * @return std::vector<Point> 
 */
std::vector<Point> nearestNeighborTSP(const std::vector<Point>& points) {
    std::vector<Point> path;
    std::vector<bool> visited(points.size(), false);
    path.reserve(points.size());
    path.emplace_back(points[0]);
    visited[0] = true;

    for (int i = 0; i < points.size() - 1; ++i) {
        double minDistance = std::numeric_limits<double>::max();
        int nearestNeighbor = -1;
        for (int j = 0; j < points.size(); ++j) {
            if (!visited[j]) {
                double distance = path[i].distanceTo(points[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestNeighbor = j;
                }
            }
        }
        path.emplace_back(points[nearestNeighbor]);
        visited[nearestNeighbor] = true;
    }

    improve2Opt(path);
    return path;
}

/**
 * @brief This function calculates the distance of a given closed path.
 * 
 * @param points to visit
 * @return total distance to visit all the points
 */
double totalDistance(const std::vector<Point>& points) {
    double distance = 0;
    for (int i = 0; i < points.size() - 1; ++i) {
        distance += points[i].distanceTo(points[i + 1]);
    }
    distance += points.back().distanceTo(points.front());
    return distance;
}



int main(int argc, char* argv[]) {
    if (strcmp(argv[2],"1") == 0) { // Random or Graph Results
        const int VEC_SIZE = atoi(argv[1]);
        std::vector<Point> approximatePath; 
        std::vector<Point> path;
        approximatePath.reserve(VEC_SIZE);
        path.reserve(VEC_SIZE);
        
        srand(time(NULL));

        for (int i = 0; i < VEC_SIZE; ++i) {
            int x = rand() % 100 - 50;
            int y = rand() % 100 - 50;
            approximatePath.emplace_back(Point(x, y));
            path.emplace_back(Point(x, y));
        }

        /*------------------------|Para graficar los grafos|------------------*/
        std::ofstream outputFile("tsp_results.csv");
        path = nearestNeighborTSP(approximatePath);

        outputFile << std::endl;
        for (const Point& point : path) {
            outputFile << point.getX() << "," << point.getY() << std::endl;
        }

        //-----------------------|Fin graficar resultados|---------------------*/
    } 
    else if (strcmp(argv[2],"2") == 0){ // Get the distance of Cities
        std::string file = argv[1];
        std::ifstream input(file);
        std::vector<Point> points;
        double x, y;
        int size;
        int pos;
        input >> size;
        points.reserve(size);
        for (int i = 0; i < size; ++i) {
            input >> pos >> x >> y;
            points.emplace_back(Point(x, y));
        }
        input.close();
        std::cout << std::fixed;
        std::cout.precision(2);
        std::cout << size << " " << totalDistance(nearestNeighborTSP(points)) << std::endl;
    }



    return 0;
}