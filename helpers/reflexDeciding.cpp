//#include "definitions.h"
#include <bits/stdc++.h>
using namespace std;
class Edge ;
class Face ;
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
        Face *left = NULL;
        Edge *next = NULL;
        Edge *prev = NULL;
};

Edge* addEdge(Vertex *start1, Vertex *end1, Face* face_id_int, Face* face_id_ext) {
    Edge* e = new Edge();
    Edge *f = new Edge();
    
    e->origin = start1;
    //cout<<e->origin->coordinates.first<<" "<<e->origin->coordinates.second<<endl;
    e->twin = f ;
    e->twin->origin = end1;
    e->twin->prev = e->next ;
    e->twin->next = e->prev ;
    start1->inc_edge = e;
    e->left = face_id_int;
    e->twin->left = face_id_ext;
    return e;
}

class Face {
    public:
        Edge *incident_edge = NULL; 
        int id = 0;
};


class DCEL {
    public:
        //vector<Vertex> vertices;
        vector<Edge*> edges;
        //vector<Face> faces;

        void makeDCEL(vector<Vertex*> v, int interior, int exterior) {
            if(v.size()<2) {
                return;
            }
            Face *f_int = new Face();
            Face *f_ext = new Face();
            f_int->id = interior;
            f_ext->id = exterior;
            Edge* e = addEdge(v[0], v[1], f_int, f_ext);
            f_ext->incident_edge = e->twin;
            f_int->incident_edge = e;
            edges.push_back(e);
            for(int i = 1; i<v.size()-1; i++) {
                Edge* e2 = addEdge(v[i],v[i+1],f_int,f_ext);
                edges.push_back(e2);
            }
            Edge* closing = addEdge(v[v.size()-1],v[0],f_int, f_ext);
            edges.push_back(closing);
        }

        void PrintDCEL() {
            
            for(int i = 0; i<edges.size(); i++) {
                cout<<"Edge "<<(i+1)<<" Starts  from ("<<edges[i]->origin->coordinates.first<<","<<edges[i]->origin->coordinates.second<<")\n";
                cout<<"Edge "<<(i+1)<<" ends  from ("<<edges[i]->twin->origin->coordinates.first<<","<<edges[i]->twin->origin->coordinates.second<<")\n";
            }
        }
};

/*
To check whether the angle made between the two edges formed from the three vertices is reflex or not, we take the cross product of the two 
vectors formed by the three vertices. If the cross product is positive, then the angle is reflex, else it is convex.

The cross product between the two vectors will always get the angle on the left side plane if it is positive, hence we continue our code to
keep finding the first angle that doesn't give positive cross product, and that is the last concave vertex. We return this vertex to our main 
function from the lastConcaveVertex function.
*/
bool reflexOrNot(Vertex* a, Vertex* b, Vertex* c) {
    // checks if the cross product is on the left-plane or on the other side
    double x1 = b->coordinates.first - a->coordinates.first;
    double y1 = b->coordinates.second - a->coordinates.second;
    double x2 = c->coordinates.first - b->coordinates.first;
    double y2 = c->coordinates.second - b->coordinates.second;
    double crossProduct = x1*y2 - x2*y1;
    //cout << crossProduct << endl;
    if(crossProduct > 0) {
        return true;
    }
    return false;
}

//Do something agar origin is reflex
Vertex* lastConcaveVertex(DCEL* d) {
    Vertex* ans = d->edges[0]->origin;
    for(int i = 0; i<d->edges.size()-1; i++) {
        //cout<<"Inside For Loop "<<i<<endl;
        //cout<<d->edges[i]->origin->coordinates.first<<" "<<d->edges[i]->origin->coordinates.second<<endl;
        if(!reflexOrNot(d->edges[i]->origin, d->edges[i]->twin->origin, d->edges[i+1]->twin->origin)) {
            ans = d->edges[i]->origin;
            break;
        }
    }
    cout << ans->coordinates.first << " " << ans->coordinates.second << endl;
    return ans;
}

int main()  {
    /*Vertex* a = new Vertex(1, 2);
    Vertex* b = new Vertex(0, 3);
    Vertex* c = new Vertex(0, 0);
    Vertex* x = new Vertex(3, 3);
    vector<Vertex*> v;
    v.push_back(b);
    v.push_back(c);
    v.push_back(x);
    v.push_back(a);*/
    //cout << reflexOrNot(c,x,a) << endl;
    Vertex* a = new Vertex(0,0);
    Vertex* b = new Vertex(1,0);
    Vertex* c = new Vertex(1,1);
    Vertex* x = new Vertex(0,1);
    Vertex* b1 = new Vertex(-1,2);
    Vertex* c1 = new Vertex(-1,1);
    Vertex* x1 = new Vertex(-1,0);
    vector<Vertex*> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    v.push_back(x);
    v.push_back(b1);
    v.push_back(c1);
    v.push_back(x1);
    
    DCEL *d = new DCEL();
    d->makeDCEL(v, 1, 2);
    //d->PrintDCEL();
    lastConcaveVertex(d);
    return 0;           
}