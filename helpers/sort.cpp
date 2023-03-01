#include "definitions.h"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

// class Point
// {
//     public:
//         double x;
//         double y;
//         Point(double xx, double yy) : x(xx), y(yy) {}
//         ~Point();   
//         inline friend ostream& operator<<(ostream& output, const Point& point)
//         {
//             output << "[" << point.x << ", " << point.y <<"]";
//             return output;
//         }
// };


// Point::~Point() {;}


/* get quadrant from 12 o'clock*/
// int get_quadrant (const Point& p)
// {
//     int result = 4; //origin

//     if (p.x > 0 && p.y > 0)
//         return 1;
//     else if(p.x < 0 && p.y > 0)
//         return 2;
//     else if(p.x < 0 && p.y < 0)
//         return 3;
//     //else 4th quadrant
//     return result;
// }

double get_clockwise_angle(const Vertex& p)
{   
    double angle = 0.0;

    //int quadrant = get_quadrant(p);
    /*making sure the quadrants are correct*/
    // cout << "Point: " << p << " is on the " << quadrant << " quadrant" << endl;

    /*calculate angle and return it*/
    angle = -atan2(p.coordinates.first,-p.coordinates.second);
    return angle;
}
bool compare_points(const Vertex& a, const Vertex& b)
{
    return (get_clockwise_angle(a) > get_clockwise_angle(b));
}
int main(int argc, char const *argv[])
{
    std::vector <Vertex> points;
    points.push_back(Vertex( 1, 3 ) );
    points.push_back(Vertex( -3, 1 ) );
    points.push_back(Vertex( 3, 4 ) );
    points.push_back(Vertex( 1, 4 ) );
    points.push_back(Vertex( 4, -1 ) );
    points.push_back(Vertex( -2, -1 ) );
    points.push_back(Vertex( -1, -1 ) );

    // cout << "\nBefore sorting" << endl;
    // for (int i = 0; i < points.size(); ++i)
    // {
    //     cout << points.at(i) << endl;
    // }

    sort(points.begin(), points.end(), compare_points);

    cout << "\nAfter sorting" << endl;
    for (int i = 0; i < points.size(); ++i)
    {
        cout << points[i].coordinates.first << points[i].coordinates.second << endl;
    }
    return 0;
}