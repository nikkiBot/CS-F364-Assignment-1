#include "../headers/definitions.h"

using namespace std;

double getAngle(Vertex* v) {
    //return atan2(v.coordinates.second, v.coordinates.first);
    double mod = sqrt(v->coordinates.first*v->coordinates.first + v->coordinates.second*v->coordinates.second);
    return v->coordinates.second / mod;
}

static bool compare_points(Vertex* a, Vertex* b) {
    if(getAngle(a)==getAngle(b)) {
        return a->coordinates.first > b->coordinates.first;
    }
    else return getAngle(a) < getAngle(b);
}

void originShifting(vector<Vertex*> &points) {
    int x = points[0]->coordinates.first;
    int y = points[0]->coordinates.second;
    for(int i = 0; i<points.size(); i++) {
        points[i]->coordinates.first -= x;
        points[i]->coordinates.second -= y;
    }

    for(int i = 0; i<points.size(); i++) {
        cout<<points[i]->coordinates.first<<" "<<points[i]->coordinates.second<<" "<<getAngle(points[i])<<endl;
    }
    sort(points.begin(), points.end(), compare_points);

    for(int i = 0; i<points.size(); i++) {
        points[i]->coordinates.first += x;
        points[i]->coordinates.second += y;
    }
}

int main(int argc, char const *argv[])
{
    std::vector <Vertex*> points;
    // points.push_back(Vertex( 1, 3 ) );
    // points.push_back(Vertex( 1, 1 ) );
    // points.push_back(Vertex( 3, 3 ) );
    // points.push_back(Vertex( -3, 1 ) );
    // points.push_back(Vertex( 3, 4 ) );
    // points.push_back(Vertex( 1, 4 ) );
    // points.push_back(Vertex( 4, -1 ) );
    // points.push_back(Vertex( -2, -1 ) );
    // points.push_back(Vertex( -1, -1 ) );
    points.push_back(new Vertex( 1, 1 ) );
    points.push_back(new Vertex( 2, 1 ) );
    points.push_back(new Vertex( 2, 2 ) );
    points.push_back(new Vertex( 1, 2 ) );

    Vertex* firstPoint = points[0];
    originShifting(points);

    cout << "\nAfter sorting" << endl;
    for (int i = 0; i < points.size(); ++i)

    {
        cout << points[i]->coordinates.first << points[i]->coordinates.second << endl;
    }
    return 0;
}