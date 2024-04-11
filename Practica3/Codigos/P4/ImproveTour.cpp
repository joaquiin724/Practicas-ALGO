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