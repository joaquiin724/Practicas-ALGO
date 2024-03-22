#include <cmath>
#include <vector>

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


