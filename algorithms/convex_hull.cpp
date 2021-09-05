#include <cstdint>
#include <algorithm>
#include <vector>

struct Point
{
    int32_t x;
    int32_t y;

    Point()
    {}

    Point(int32_t x, int32_t y)
        :x(x), y(y)
    {}
};

/* Cross product for angle abc. */
int32_t cross_product(const Point& a, const Point& b, const Point& c)
{
    std::pair<int32_t, int32_t> vector1 = {a.x-b.x, a.y-b.y};
    std::pair<int32_t, int32_t> vector2 = {c.x-b.x, c.y-b.y};

    return vector1.first*vector2.second - vector1.second*vector2.first;
}

int32_t sign(int64_t a)
{
    if(a > 0)
        return 1;
    else if(a < 0)
        return -1;
    else
        return 0;
}

bool cmp(const Point& a, const Point& b)
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

/*
 * Convex hull finder.
 *
 * Parameters
 * ----------
 * points - array of points. Can be both Point[] and vector<Point>
 * number_of_points - number of points in array
 * 
 * Returns
 * -------
 * vector with points creating convex hull
 * 
 * Examples
 * --------
 * 
 * vector<Point> p = {{0, 1}, {0, 0}, {0, 3}, {1, 3}};
 * auto res = convex_hull(p, p.size());
 * for(auto u: res)
 *      cout << u.x << " " << u.y << "\n";
 * 
 * Warning
 * -------
 * This version ensure that there are no 3 colinear points in the hull. If you want to keep those points,
 * you need to change the algorithm.
 */
template<class T>
std::vector<Point> convex_hull(T& points, int32_t number_of_points)
{
    if(number_of_points == 1)
        return points;

    sort(begin(points), end(points), cmp);
    auto first = points[0];
    auto last = points[number_of_points-1];

    std::vector<Point> up, down;
    up.push_back(first);
    down.push_back(first);

    for(int32_t i = 1; i < number_of_points; i++)
    {
        if(i == number_of_points-1 || sign(cross_product(first, last, points[i])) == -1)
        {
            while(up.size() >= 2 && sign(cross_product(up[up.size()-2], up.back(), points[i])) != 1)
                up.pop_back();
            up.push_back(points[i]);
        }

        if(i == number_of_points-1 || sign(cross_product(first, last, points[i])) == 1)
        {
            while(down.size() >= 2 && sign(cross_product(down[down.size()-2], down.back(), points[i])) != -1)
                down.pop_back();
            down.push_back(points[i]);
        }
    }

    std::vector<Point> hull;
    for (int32_t i = 0; i < up.size(); i++)
        hull.push_back(up[i]);
    for (int32_t i = (int32_t)down.size() - 2; i > 0; i--)
        hull.push_back(down[i]);

    return hull;
}