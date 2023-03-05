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

bool direction(Vertex* a, Vertex* b, Vertex* c)
{
    int val = (c->coordinates.second-a->coordinates.second)*(b->coordinates.first-a->coordinates.first) - (c->coordinates.first-a->coordinates.first)*(b->coordinates.second-a->coordinates.second);
    if (val >= 0)
 
        // Colinear
        return true;
 
    return false;
}
 
bool checkInside(DCEL* d,Vertex* p)
{
    int start = 0 ;
    int end = d->edges.size()-1;
    // When polygon has less than 3 edge, it is not polygon
    if ((end-start+1) < 3)
        return false;
 
    for(int i = start; i<=end; i++) {
        bool temp = direction(d->edges[i]->origin, d->edges[i]->twin->origin, p);
        if (!temp) {
            return false;
        }
    } 
    bool temp = direction(d->edges[start]->origin, d->edges[end]->origin, p);
    if (!temp) {
        return false;
    }
    
    return true;
}

bool isNotReflex(Vertex* a, Vertex* b, Vertex* c) {
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

void decomposeDCEL(vector<Vertex*> &v, int interior, int exterior) ;

//Create a global variable with total face count
//Create a global DCEL which will store face of all the edges
vector<DCEL*> finVector;
void decomposeDCEL(vector<Vertex*> &v, int interior, int exterior) {
    if(v.size()<=3) {
        return;
    }
    DCEL* d = new DCEL();
    int n = v.size();
    //d->makeDCEL(v, interior, exterior);    
    //Find the largest path
    vector<Vertex*> remaining;
    vector<Vertex*> path;
    double min_x = INT_MAX;
    double max_y = INT_MIN;
    double min_y = INT_MAX;
    double max_x = INT_MIN;
    if(v.size()>3) {
        path.push_back(v[0]);
        path.push_back(v[1]);
        for(int i = 3; i < v.size(); i++) {
            if(isNotReflex(path[path.size()-2], path[path.size()-1], v[i])) {
                if(isNotReflex(path[path.size()-1],v[i], path[0])) {
                    if(isNotReflex(v[i], path[0], path[1])) {
                        path.push_back(v[i]);
                        v.erase(v.begin()+i-1);
                        min_x = min(min_x, v[i]->coordinates.first);
                        max_x = max(max_x, v[i]->coordinates.first);
                        min_y = min(min_y, v[i]->coordinates.second);
                        max_y = max(max_y, v[i]->coordinates.second);
                        
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
        //Construct LPVS for the largest path
        vector<Vertex*> lpvs;
        if(path.size()==2) {
            for(int i = 1; i<v.size(); i++) {
                remaining.push_back(v[i]);
            }
            remaining.push_back(v[0]);
        }
        else if(path.size()!=n){
            
            //base case 1
            if(isNotReflex(v[v.size()-1], v[0], v[1])) {
                lpvs.push_back(v[0]);
            }
            for(int i = 1; i < v.size()-1; i++) {
                if(isNotReflex(v[i-1], v[i], v[i+1])) {
                    lpvs.push_back(v[i]);
                }            
            }
            //base case 2
            if(isNotReflex(v[v.size()-2], v[v.size()-1], v[0])) {
                lpvs.push_back(v[v.size()-1]);
            }
            //Check if any point inside LPVS is inside the polygon or not, if yes backtrack
            DCEL* tempDCEL = new DCEL();
            // bool back = false;
            tempDCEL->makeDCEL(path, interior, exterior);
            // int cur = 0;

            //Create a temporary vector notch which will initially contain entire lpvs
            
            vector<Vertex*> notch = lpvs;
            //If that point is not inside, remove it from notch
            while(!notch.empty()) {
                //Else, backtrack and restrore notch to lpvs
                notch = lpvs;
                int cur = 0;
                bool back = false;
                while(cur<lpvs.size() and !back) {
                    auto temp = lpvs[cur];
                    if(temp->coordinates.first>min_x && temp->coordinates.first<max_x && temp->coordinates.second>min_y && temp->coordinates.second<max_y) {
                        if(!checkInside(tempDCEL, temp)) {
                            path.pop_back();
                            tempDCEL->edges.pop_back();
                            tempDCEL->edges.pop_back();
                            tempDCEL->edges.push_back(addEdge(path[path.size()-1], path[0], path[0]->inc_edge->left, path[0]->inc_edge->twin->left));
                            back = true;
                        }
                        else {
                            notch.erase(notch.begin()+cur);
                        }
                    }
                    cur++;
                }
            } 
            finVector.push_back(tempDCEL);
            interior++;
            //Construct vector of points for remaining polygon
            int i = 0;
            // int k = 0;
            while(v[i]!=path[0]) {
                remaining.push_back(v[i]);
                i++;
            }
            remaining.push_back(path[0]);
            remaining.push_back(path[path.size()-1]);
            i++;
            while(i<v.size()) {
                remaining.push_back(v[i]);
                i++;
            }
        }
        
    }
    decomposeDCEL(remaining, interior, exterior); 
}


int main() {
    vector<Vertex*> v;
    Vertex* v1 = new Vertex(0,0);
    Vertex* v2 = new Vertex(1,0);
    Vertex* v3 = new Vertex(1,1);
    Vertex* v4 = new Vertex(0,1);
    Vertex* v5 = new Vertex(-1,2);
    Vertex* v6 = new Vertex(-1,1);
    Vertex* v7 = new Vertex(-1,0);
    Vertex* v8 = new Vertex(-0.5,-5);
    //cout<<"Bool"<<InLine(v7,v1,v2)<<endl;
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    v.push_back(v5);
    v.push_back(v6);
    v.push_back(v7);
    decomposeDCEL(v,1,0);
    for(auto temp:finVector) {
        temp->PrintDCEL();
    }
    return 0;
}