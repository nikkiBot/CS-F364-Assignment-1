#include <bits/stdc++.h>
// #include "./headers"
using namespace std ;
class Edge;
class Face;

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
                Edge* e2 = addEdge(v[1],v[2],f_int,f_ext);
                edges.push_back(e2);
            }
            Edge* closing = addEdge(v[v.size()-1],v[0],f_int, f_ext);
            edges.push_back(closing);
        }

        void PrintDCEL() {
            
            for(int i = 0; i<edges.size(); i++) {
                cout<<"Edge "<<(i+1)<<" Starts  from ("<<edges[i]->origin->coordinates.first<<","<<edges[i]->origin->coordinates.second<<")\n";
                cout<<"Edge "<<(i+1)<<" ends  from ("<<edges[i]->twin->origin->coordinates.first<<","<<edges[i]->twin->origin->coordinates.second<<")\n";
                cout<<"Current Edge is on Face:"<<edges[i]->left->id<<endl;
            }
        }

        //f is total number of faces in dcel
        //For decomposing, add a new face
        void decomposeEdge(int start, int end, int f) {
                //Edge* e = edges[start];
                //Edge* f = edges[end];
                Face* face_new = new Face();
                face_new->id = f+1;
                for(int i = start; i<=end; i++) {
                    edges[i]->left = face_new;
                    
                }
        }
};

int main() {
    vector<Vertex*> v;
    Vertex* v1 = new Vertex(0,0);
    Vertex* v2 = new Vertex(1,0);
    Vertex* v3 = new Vertex(1,1);
    Vertex* v4 = new Vertex(0,1);
    Vertex* v5 = new Vertex(-1,2);
    Vertex* v6 = new Vertex(-1,1);
    Vertex* v7 = new Vertex(-1,0);
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    v.push_back(v5);
    v.push_back(v6);
    v.push_back(v7);

    DCEL* d  = new DCEL();
    d->makeDCEL(v, 1,2);
    //d->PrintDCEL();
    d->decomposeEdge(3,4,2);
    d->PrintDCEL();
    return 0;
}