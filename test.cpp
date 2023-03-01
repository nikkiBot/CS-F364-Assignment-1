#include "./headers/definitions.h"
using namespace std ;
// Path: headers/definitions.h

int main()
{
    pair<double, double> p1 = make_pair(1, 1);
    pair<double, double> p2 = make_pair(2, 2);
    pair<double, double> p3 = make_pair(3, 3);
    Vertex *v1 , *v2 , *v3 ;
    v1->coordinates = p1 ;
    v2->coordinates = p2 ;
    v3->coordinates = p3 ;
    Edge *e1 = new Edge(v1, v2);
    Edge *e2 = new Edge(v2, v3);

    Vertex* temp = v1;
    //print edges for debugging:
    while(temp->inc_edge!=NULL) {
        cout << temp->inc_edge->origin->coordinates.first << " " << temp->inc_edge->origin->coordinates.second << endl;
        temp = temp->inc_edge->twin->origin;
    }
    return 0;
}