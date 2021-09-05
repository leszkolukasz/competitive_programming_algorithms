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

int64_t calculate_distance(const Point& a, const Point& b)
{
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

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

/*
 * Algorithm that sort points by angle created by given point, root point and OX axis.
 *
 * Parameters
 * ----------
 * points - array of points. Can be both Point[] and vector<Point>
 * 
 * Examples
 * --------
 * vector<Point> v = {{-1, -1}, {0, 20}, {0, 0}, {1, 0}, {2 , 0}};
 * angle_sort(v);
 */
template<class T>
void angle_sort(T& points, int32_t number_of_points)
{
    if(number_of_points == 1)  
        return;

    //root point is the one most to the left. If there are a few of the same x coordinate then
    //the one with the smallest y coordinate is root.
    Point root = points[0];
    int32_t root_id = 0;

    for(int32_t i = 1; i < number_of_points; i++)
    {
        if(points[i].x < root.x || (points[i].x == root.x && points[i].y < root.y))
        {
            root = points[i];
            root_id = i;
        }
    }

    std::swap(points[0], points[root_id]);

    std::sort(std::begin(points)+1, std::end(points), [root](const Point& a, const Point& b){
        int32_t orientation = sign(cross_product(root, a, b));

        if(orientation == -1)
            return true;
        else if(orientation == 1)
            return false;
        else
            return calculate_distance(root, a) < calculate_distance(root, b);
    });
}