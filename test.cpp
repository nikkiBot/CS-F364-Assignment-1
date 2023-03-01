#include "./headers/definitions.h"
#include <bits/stdc++.h>
using namespace std ;
// Path: headers/definitions.h

int main()
{
    Vertex *v1 = new Vertex(1,1);
    Vertex *v2 = new Vertex(2,2);
    Vertex *v3 = new Vertex(3,3);
    cout << "V success" << endl ;
    Edge *e1 = new Edge();
    e1->addEdge(v1,v2);
    Edge *e2 = new Edge();
    e2->addEdge(v2,v3);

    Vertex* temp = v1;
    //print edges for debugging:
    cout << "sdfklsdfl" << endl ;
    while(temp->inc_edge!=NULL and temp->inc_edge->twin->origin!=NULL) {
        cout << temp->inc_edge->origin->coordinates.first << " " << temp->inc_edge->origin->coordinates.second << endl;
        temp = temp->inc_edge->twin->origin;
    }
    return 0;
}