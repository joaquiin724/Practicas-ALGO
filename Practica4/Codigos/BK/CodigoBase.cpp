#include <cmath>
#include <iostream>

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
