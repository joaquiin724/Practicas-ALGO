#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

/**
 * @brief Class which represents a point in a 2D plane.
 * @note [[nodiscard]] is an attribute that tells the compiler to issue a warning if the return value of a function is ignored.
 * @note constexpr is an attribute that tells the compiler that a function can be evaluated at compile time.
 * @note noexcept is an attribute that tells the compiler that a function does not throw exceptions.
 * @note -> is a new syntax that allows the compiler to deduce the return type of a function.
 * 
 * 
 */
class Point {
public:
    constexpr Point(int x, int y) noexcept : x(x), y(y) {}

    [[nodiscard]] constexpr auto distanceTo(const Point &p) const noexcept -> double {
        return std::sqrt(std::pow(p.x - x, 2) + std::pow(p.y - y, 2));
    }

    [[nodiscard]] constexpr auto getX() const noexcept -> int { return x; }
    [[nodiscard]] constexpr auto getY() const noexcept -> int { return y; }

    bool operator==(const Point &p) const {
        return x == p.x && y == p.y;
    }

    friend auto operator<<(std::ostream &os, const Point &point) -> std::ostream & {
        os << point.x << ',' << point.y;
        return os;
    }

private:
    int x, y;
};

class Matrix {
public:
    Matrix(int size) noexcept : matrix(size, std::vector<double>(size, 0)) {}
    
    [[nodiscard]] auto getDistance(int i, int j) const noexcept -> double {
        return matrix[i][j];
    }

    void initializeMatrix(const std::vector<Point>& points) {
        for (int i = 0; i < points.size(); ++i) {
            for (int j = 0; j < points.size(); ++j) {
                if (i == j) {
                    matrix[i][j] = std::numeric_limits<double>::infinity();
                    continue;
                }
                matrix[i][j] = points[i].distanceTo(points[j]);
            }
        }
    }
private:
    std::vector<std::vector<double>> matrix;
};




double totalDistance(const std::vector<Point>& points) {
    double distance = 0;
    for (int i = 0; i < points.size() - 1; ++i) {
        distance += points[i].distanceTo(points[i + 1]);
    }
    distance += points.back().distanceTo(points.front());
    return distance;
}

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

    return path;
}

class BranchBound {
private:
    double bestSolution;
    std::vector<Point> bestPath;
    std::vector<Point> path;
public:
    BranchBound(const std::vector<Point>& points) {
        path = points;
        bestPath = path;
        bestSolution = totalDistance(bestPath);
    }

    double getBestSolution() {
        return bestSolution;
    }

    std::vector<Point> getBestPath() {
        return bestPath;
    }

    void getSolution(const std::vector<Point>& currentPath, const double pathDistance) {
        if (currentPath.size() == path.size()) {
            double totalDist = pathDistance + currentPath.back().distanceTo(currentPath[0]);
            if (totalDist < bestSolution) {
                bestSolution = totalDist;
                bestPath = currentPath;
            }
            return;
        }

        for (const Point& point : path) {
            if (std::find(currentPath.begin(), currentPath.end(), point) == currentPath.end()) {
                double newDistance = pathDistance + currentPath.back().distanceTo(point);

                if (newDistance < bestSolution * currentPath.size() / bestPath.size()) {
                    if (newDistance < bestSolution * currentPath.size() / bestPath.size()) {
                        std::cout << "projectedDistance: " << newDistance << std::endl;
                        std::cout << "bestSolution: " << bestSolution * currentPath.size() / bestPath.size() << std::endl;
                    }
                    std::vector<Point> newPath = currentPath;
                    newPath.emplace_back(point);
                    getSolution(newPath, newDistance);
                }
            }
        }
    }
};

class Solucion {
private:
    vector<int> path;
    int pos_e;
    double distancia_recorrida;
    double cota_inferior;
public:
    Solucion() {
        pos_e = path.size();
        distancia_recorrida = 0;
        cota_inferior = 0;
    }

    bool Factible(int cota_global){
        return cota_inferior < cota_global;
    }

    int Comp(){
        return pos_e;
    }

    bool operator<(const Solucion& s) const {
        return cota_inferior > s.cota_inferior;
    }

    vector<int> getPath() const {
        return path;
    }

    int getPos_e() const {
        return pos_e;
    }

    double getDistancia_recorrida() const {
        return distancia_recorrida;
    }

    double getCota_inferior() const {
        return cota_inferior;
    }
};

Solucion Branch_and_Bound ()


int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <size or filename> <mode>" << std::endl;
        return 1;
    }

    if (strcmp(argv[2], "1") == 0) { // Random or Graph Results
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
        BranchBound solver(approximatePath);
        solver.getSolution({path[0]}, 0);
        path = solver.getBestPath();

        outputFile << std::endl;
        for (const Point& point : path) {
            outputFile << point.getX() << "," << point.getY() << std::endl;
        }

        //-----------------------|Fin graficar resultados|---------------------*/
    } 
    else if (strcmp(argv[2], "2") == 0) { // Get the distance of Cities
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
        BranchBound solver(points);
        solver.getSolution({points[0]}, 0);
        std::cout << size << " " << solver.getBestSolution() << std::endl;
    }

    return 0;
}
