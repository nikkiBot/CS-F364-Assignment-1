#include "../headers/definitions.h"

using namespace std;


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

    sort(points.begin(), points.end(), compare_points);

    cout << "\nAfter sorting" << endl;
    for (int i = 0; i < points.size(); ++i)
    {
        cout << points[i].coordinates.first << points[i].coordinates.second << endl;
    }
    return 0;
}