#include <cmath>
#include <vector>
#include <iostream>
#include <limits>
#include <numeric>
#include <algorithm>

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

    friend ostream &operator<<(ostream &os, const Point &point) {
        os << "" << point.x << "," << point.y << "";
        return os;
    }

private:
    int x, y;
};


/**
 * @brief This function calculates the distance of a given closed path.
 * 
 * @param points to visit
 * @return total distance to visit all the points
 */
double totalDistance(const vector<Point>& points) {
  double distance = 0;
  for (int i = 0; i < points.size() - 1; ++i) {
    distance += points[i].distanceTo(points[i + 1]);
  }
  distance += points.back().distanceTo(points.front()); // Return to starting point
  return distance;
}

std::vector<Point> divideAndConquerTSP(const std::vector<Point>& points) {
    if (points.size() <= 3) {
        std::vector<int> permutation(points.size());
        std::iota(permutation.begin(), permutation.end(), 0);
        std::vector<int> bestPermutation = permutation;

        double minDistance = std::numeric_limits<double>::max();
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

        std::vector<Point> bestTour;
        for (int i = 0; i < bestPermutation.size(); ++i) {
            bestTour.emplace_back(points[bestPermutation[i]]);
        }

        return bestTour;
    }

    int mid = points.size() / 2;
    std::vector<Point> left(points.begin(), points.begin() + mid);
    std::vector<Point> right(points.begin() + mid, points.end());

    std::vector<Point> leftTour = divideAndConquerTSP(left);
    std::vector<Point> rightTour = divideAndConquerTSP(right);

    //TODO: Combinar esto

    return leftTour; // Replace with combined and optimized tour
}


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
double bruteForceTSP(const std::vector<Point>& points) {
    std::vector<int> permutation(points.size());
    std::iota(permutation.begin(), permutation.end(), 0);

    double minDistance = std::numeric_limits<double>::max();
    do {
        double distance = 0;
        for (int i = 0; i < permutation.size() - 1; ++i) {
            distance += points[permutation[i]].distanceTo(points[permutation[i + 1]]);
        }

        distance += points[permutation.back()].distanceTo(points[permutation.front()]);
        minDistance = std::min(minDistance, distance);

    } while (std::next_permutation(permutation.begin(), permutation.end()));

    return minDistance;
}



int main(int argc, char* argv[]) {
    const int VEC_SIZE = atoi(argv[1]);
    vector<Point> randomPoints;
    vector<Point> approximatePath; 
    srand(time(NULL));

    for (int i = 0; i < VEC_SIZE; ++i) {
        int x = rand() % 100 - 50;
        int y = rand() % 100 - 50;
        randomPoints.emplace_back(Point(x, y));
        approximatePath.emplace_back(Point(x, y));
    }

    std::cout << "Points: \n" << std::endl;
    for (int i = 0; i < VEC_SIZE; ++i) {
        std::cout << randomPoints[i] << std::endl;
    }
    
    std::cout << "Brute Force: " << bruteForceTSP(randomPoints) << std::endl;
    //std::cout << "Our Algorithm: " << totalDistance(divideAndConquerTSP(approximatePath)) << std::endl;

    return 0;
}

















