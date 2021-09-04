#include <cstdint>
#include <algorithm>

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

struct Segment
{
    Point a;
    Point b;

    Segment(const Point& a, const Point& b)
        :a(a), b(b)
    {}

    Segment(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
    {
        a = Point(x1, y1);
        b = Point(x2, y2);
    }
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

/* Check if projection of points on either OX or OY axis intersect. */
bool do_projections_intersect(int32_t a, int32_t b, int32_t c, int32_t d)
{
    if (a > b)
        std::swap(a, b);
    if (c > d)
        std::swap(c, d);

    return std::max(a, c) <= std::min(b, d);
}


/*
 * Check if two segments intersect.
 *
 * Parameters
 * ----------
 * a - first segment
 * b - second segment
 * 
 * Examples
 * --------
 * Segment a(0, 0, 1, 1);
 * Segment b(0, 1, 1, 0);
 * std::cout << do_intersect(a, b) << '\n';
 */
bool do_intersect(const Segment& a, const Segment& b)
{
    if(cross_product(a.a, a.b, b.a) == 0 && cross_product(a.a, a.b, b.b) == 0)
        return (do_projections_intersect(a.a.x, a.b.x, b.a.x, b.b.x) 
            && do_projections_intersect(a.a.y, a.b.y, b.a.y, b.b.y));

    return (sign(cross_product(a.a, a.b, b.a)) != sign(cross_product(a.a, a.b, b.b))
        && sign(cross_product(b.a, b.b, a.a)) != sign(cross_product(b.a, b.b, a.b)));
}