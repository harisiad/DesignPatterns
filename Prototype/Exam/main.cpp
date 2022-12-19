#include <iostream>

struct Point
{
    int x{0}, y{0};

    Point() {}

    Point(const int x, const int y) : x{x},
                                      y{y} {}

    Point(const Point &rhs) : x(rhs.x),
                              y(rhs.y)
    {
    }
};

struct Line
{
    Point *start, *end;

    Line(Point *const start, Point *const end) : start(start),
                                                 end(end)
    {
    }

    ~Line()
    {
        delete start;
        delete end;
    }

    Line deep_copy() const
    {
        return {new Point(*start), new Point(*end)};
    }
};

int main()
{
    return 0;
}


