#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <queue>

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
    BranchBound(const std::vector<Point>& points) : path(points) {
        bestPath = nearestNeighborTSP(path);
        bestSolution = totalDistance(bestPath);
    };

    double getBestSolution() {
        return bestSolution;
    }

    std::vector<Point> getBestPath() {
        return bestPath;
    }

    void getSolution(const std::vector<Point>& path, const Point& toAdd, const double pathDistance) {
        std::vector<Point> currentPath(path);
        double distance = pathDistance + currentPath.back().distanceTo(toAdd);
        currentPath.emplace_back(toAdd);

        if (currentPath.size() == bestPath.size()) {
            if (distance < bestSolution) {
                bestPath = currentPath;
                bestSolution = distance;
            }
        }
        else{
            double equivalentDist = (bestSolution * currentPath.size() )/ bestPath.size();
            if (distance <= equivalentDist) {
                for (const Point& point : path) {
                    if (std::find(currentPath.begin(), currentPath.end(), point) == currentPath.end()) {
                        getSolution(currentPath, point, distance);
                    }
                }
            }
        }
    }
};


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
        BranchBound solver(approximatePath);
        path = solver.getBestPath();

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
        BranchBound solver(points);
        solver.getSolution(points, points[0], 0);
        std::cout << size << " " << solver.getBestSolution() << std::endl;
    }



    return 0;
}
