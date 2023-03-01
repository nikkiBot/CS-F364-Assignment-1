#include <bits/stdc++.h>
using namespace std ;
class Edge;


class Vertex {
    public:
        pair<double, double> coordinates;
        int identity ;
        Edge *inc_edge; 

        Vertex();
        Vertex(double x, double y) {
            coordinates.first = x;
            coordinates.second = y;
        }
};

class Edge {
    public:
        Vertex *origin = NULL;
        Edge *twin = NULL;
        //Face *left = NULL;
        Edge *next = NULL;
        Edge *prev = NULL;
};

Edge* addEdge(Vertex *start1, Vertex *end1) {
    Edge* e = new Edge();
    Edge *f = new Edge();
    
    e->origin = start1;
    //cout<<e->origin->coordinates.first<<" "<<e->origin->coordinates.second<<endl;
    e->twin = f ;
    e->twin->origin = end1;
    e->twin->prev = e->next ;
    e->twin->next = e->prev ;
    start1->inc_edge = e;
    return e;
}

int main() {
    Vertex *v1 = new Vertex(1,1);
    //cout<<v->coordinates.first<<" "<<v->coordinates.second<<endl;
    Vertex *v2 = new Vertex(2,2);
    Vertex *v3 = new Vertex(3,3);
    Edge *e1 = new Edge();
    Edge *e2 = new Edge();
    e1=addEdge(v1,v2);
    e2=addEdge(v2,v3);
    
    Vertex* temp = v1;
    //print edges for debugging:
    while(temp!=NULL) {
        cout << temp->coordinates.first << " " << temp->coordinates.second << endl;
        if(temp->inc_edge->twin->origin) {
            temp = temp->inc_edge->twin->origin;
        }
        else {
            break;
        }
    }
    return 0;
}