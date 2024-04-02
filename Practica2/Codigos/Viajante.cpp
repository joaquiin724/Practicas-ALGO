#include <cmath>
#include <vector>
#include <iostream>
#include <limits>

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
    double calculateDistance(const Point &p) const {
        return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    friend ostream &operator<<(ostream &os, const Point &point) {
        os << "[" << point.x << "," << point.y << "]";
        return os;
    }

private:
    int x, y;
};


vector<Point> calculatePath(const vector<Point> &points) {
    vector<Point> path;

    if (points.size() <= 4) {
        double minDistance;
        double currentDistance;
        vector<Point> currentPath;
        vector<Point> bestPath;

        for (int i = 0; i < points.size(); ++i){
            currentPath.clear();
            currentDistance = 0;

            for (int j = i; j < points.size() + i; ++j){
                int index = j % points.size();
                currentPath.emplace_back(points[index]);
                currentDistance += points[index].calculateDistance(points[index+1]);
            }

            if (currentDistance < minDistance ){
                minDistance = currentDistance;
                bestPath = currentPath;
            }
        }

        return bestPath;
    }
    else {
        vector<Point> left;
        vector<Point> right;

        for (int i = 0; i < points.size() / 2; ++i) {
            left.emplace_back(points[i]);
        }

        for (int i = points.size() / 2; i < points.size(); ++i) {
            right.emplace_back(points[i]);
        }

        vector<Point> leftPath = calculatePath(left);
        vector<Point> rightPath = calculatePath(right);

        path.insert(path.end(), leftPath.begin(), leftPath.end());
        path.insert(path.end(), rightPath.begin(), rightPath.end());

        return path;
    }
}

vector<Point> bruteForce(const vector<Point>& points) {
    double minDistance = numeric_limits<double>::max();
    double currentDistance = 0;
    vector<Point> currentPath;
    vector<Point> bestPath;

    for (int i = 0; i < points.size(); ++i) {    
        currentDistance = 0;
        currentPath.clear();
        for (int j = i; j < points.size() + i; ++j) {
           currentDistance += points[j].calculateDistance(points[j+1]);
           currentPath.emplace_back(points[j]);
        }
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            bestPath = currentPath;
        }

    }
    return bestPath;
}


double calculateTotalPathDistance(const vector<Point> &path) {
    double totalDistance = 0;

    for (int i = 0; i < path.size(); ++i) {
        totalDistance += path[i].calculateDistance(path[i+1]);
    }

    return totalDistance;
}


int main(int argc, char* argv[]) {
    const int VEC_SIZE = atoi(argv[1]);
    vector<Point> toPath;
    vector<Point> finalPath; 
    vector<Point> approximatePath; 
    srand(time(NULL));

    for (int i = 0; i < VEC_SIZE; ++i) {
        int x = rand() % 100 - 50;
        int y = rand() % 100 - 50;
        toPath.emplace_back(Point(x, y));
        approximatePath.emplace_back(Point(x, y));
    }

    std::cout << "Points: \n" << std::endl;
    for (int i = 0; i < VEC_SIZE; ++i) {
        std::cout << toPath[i] << std::endl;
    }
    
    finalPath = bruteForce(toPath);
    approximatePath = calculatePath(toPath);
   
    std::cout << "Brute-Force: " << calculateTotalPathDistance(finalPath) << std::endl;
    std::cout << "Our Algorithm: " << calculateTotalPathDistance(approximatePath) << std::endl;

    return 0;
}

















