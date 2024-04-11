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


/**
 * @brief This function calculates the minimum distance required to visit
 * all the points in the vector once, to do so, it generates all the possible
 * permutations of the vector and calculates the distance needed to visit all
 * the points in the order of the permutation.
 * 
 * @note Distance from first to last point has to be calculated to make a closed path.
 * @note iota generates a sequence of numbers from 0 to n.
 * @note If needed, it can return the permutation that generates the minimum distance.
 * 
 * @param points which will be used to calculate the minimum distance
 * @return minimum distance to visit all the points
 */
std::vector<Point> bruteForceTSP(const std::vector<Point>& points) {
    std::vector<int> permutation(points.size());
    std::iota(permutation.begin(), permutation.end(), 0);

    double minDistance = std::numeric_limits<double>::max();
    std::vector<int> bestPermutation;
    do {
        double distance = 0;
        for (int i = 0; i < permutation.size() - 1; ++i) {
            distance += points[permutation[i]].distanceTo(points[permutation[i + 1]]);
        }

        distance += points[permutation.back()].distanceTo(points[permutation.front()]);
        if (distance < minDistance) {
            minDistance = distance;
            bestPermutation = permutation;
        }
    } while (std::next_permutation(permutation.begin(), permutation.end()));

    std::vector<Point> bestPath;
    for (int index : bestPermutation) {
        bestPath.emplace_back(points[index]);
    }

    return bestPath;
}

/**
 * @brief This function optimizes a given tour by swwapping pairs of points
 * until the tour can't be improved anymore by swapping points.
 * 
 * @param tour  to optimize
 * @return optimized tour
 */
std::vector<Point> optimizeTour(const std::vector<Point>& tour) {
    std::vector<Point> currentTour = tour;
    bool improvement = true;

    while (improvement) {
        improvement = false;

        for (int i = 1; i < currentTour.size() - 2; ++i) {
            for (int j = i + 2; j < currentTour.size(); ++j) {

                double originalDistance = currentTour[i - 1].distanceTo(currentTour[i]) +
                                          currentTour[j - 1].distanceTo(currentTour[j]);
                double swappedDistance = currentTour[i - 1].distanceTo(currentTour[j - 1]) +
                                         currentTour[i].distanceTo(currentTour[j]);

                if (swappedDistance < originalDistance) {
                    std::reverse(currentTour.begin() + i, currentTour.begin() + j);
                    improvement = true;
                }
            }
        }
    }

    return currentTour;
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

    return optimizeTour(path);
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
        std::vector<Point> randomPoints;
        randomPoints.reserve(VEC_SIZE);

        srand(time(NULL));

        for (int i = 0; i < VEC_SIZE; ++i) {
            int x = rand() % 100 - 50;
            int y = rand() % 100 - 50;
            randomPoints.emplace_back(Point(x, y));
        }

        std::cout << VEC_SIZE << " " << totalDistance(nearestNeighborTSP(randomPoints)) << std::endl;
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