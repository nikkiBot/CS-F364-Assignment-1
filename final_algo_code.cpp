// #include <bits/stdc++.h>
// using namespace std ;
// class Edge;
// class Face;

// class Vertex {
//     public:
//         pair<double, double> coordinates;
//         int identity ;
//         Edge *inc_edge; 

//         Vertex();
//         Vertex(double x, double y) {
//             coordinates.first = x;
//             coordinates.second = y;
//             inc_edge = NULL;
//         }
// };

// class Edge {
//     public:
//         Vertex *origin = NULL;
//         Edge *twin = NULL;
//         Face *left = NULL;
//         Edge *next = NULL;
//         Edge *prev = NULL;
// };

// Edge* addEdge(Vertex *start1, Vertex *end1, Face* face_id_int, Face* face_id_ext) {
//     Edge* e = new Edge();
//     Edge *f = new Edge();
    
//     e->origin = start1;
//     //cout<<e->origin->coordinates.first<<" "<<e->origin->coordinates.second<<endl;
//     e->twin = f ;
//     e->twin->origin = end1;
//     e->twin->prev = e->next ;
//     e->twin->next = e->prev ;
//     start1->inc_edge = e;
//     e->left = face_id_int;
//     e->twin->left = face_id_ext;
//     return e;
// }

// class Face {
//     public:
//         Edge *incident_edge = NULL; 
//         int id = 0;
// };

// class DCEL {
//     public:
//         //vector<Vertex> vertices;
//         vector<Edge*> edges;
//         //vector<Face> faces;

//         void makeDCEL(vector<Vertex*> v, int interior, int exterior) {
//             if(v.size()<2) {
//                 return;
//             }
//             Face *f_int = new Face();
//             Face *f_ext = new Face();
//             f_int->id = interior;
//             f_ext->id = exterior;
//             Edge* e = addEdge(v[0], v[1], f_int, f_ext);
//             f_ext->incident_edge = e->twin;
//             f_int->incident_edge = e;
//             edges.push_back(e);
//             for(int i = 1; i<v.size()-1; i++) {
//                 Edge* e2 = addEdge(v[i],v[i+1],f_int,f_ext);
//                 edges.push_back(e2);
//             }
//             Edge* closing = addEdge(v[v.size()-1],v[0],f_int, f_ext);
//             edges.push_back(closing);
//         }

//         void PrintDCEL() {
            
//             for(int i = 0; i<edges.size(); i++) {
//                 cout<<"Edge "<<(i+1)<<" Starts  from ("<<edges[i]->origin->coordinates.first<<","<<edges[i]->origin->coordinates.second<<")\n";
//                 cout<<"Edge "<<(i+1)<<" ends  from ("<<edges[i]->twin->origin->coordinates.first<<","<<edges[i]->twin->origin->coordinates.second<<")\n";
//                 cout<<"Current Edge is on Face:"<<edges[i]->left->id<<endl;
//             }
//         }

//         //f is total number of faces in dcel
//         //For decomposing, add a new face
//         void decomposeEdge(int start, int end, int f) {
//                 //Edge* e = edges[start];
//                 //Edge* f = edges[end];
//                 Face* face_new = new Face();
//                 face_new->id = f+1;
//                 for(int i = start; i<=end; i++) {
//                     edges[i]->left = face_new;
                    
//                 }
//         }
// };

// bool direction(Vertex* a, Vertex* b, Vertex* c)
// {
//     int val = (c->coordinates.second-a->coordinates.second)*(b->coordinates.first-a->coordinates.first) - (c->coordinates.first-a->coordinates.first)*(b->coordinates.second-a->coordinates.second);
//     if (val >= 0)
 
//         // Colinear
//         return true;
 
//     return false;
// }
 
// bool checkInside(DCEL* d,Vertex* p)
// {
//     int start = 0 ;
//     int end = d->edges.size()-1;
//     // When polygon has less than 3 edge, it is not polygon
//     if ((end-start+1) < 3)
//         return false;
 
//     for(int i = start; i<=end; i++) {
//         bool temp = direction(d->edges[i]->origin, d->edges[i]->twin->origin, p);
//         if (!temp) {
//             return false;
//         }
//     } 
//     bool temp = direction(d->edges[start]->origin, d->edges[end]->origin, p);
//     if (!temp) {
//         return false;
//     }
    
//     return true;
// }

// bool isNotReflex(Vertex* a, Vertex* b, Vertex* c) {
//     // checks if the cross product is on the left-plane or on the other side
//     double x1 = b->coordinates.first - a->coordinates.first;
//     double y1 = b->coordinates.second - a->coordinates.second;
//     double x2 = c->coordinates.first - b->coordinates.first;
//     double y2 = c->coordinates.second - b->coordinates.second;
//     double crossProduct = x1*y2 - x2*y1;
//     //cout << crossProduct << endl;
//     if(crossProduct > 0) {
//         return true;
//     }
//     return false;
// }

// void decomposeDCEL(vector<Vertex*> &v, int interior, int exterior) ;

// //Create a global variable with total face count
// //Create a global DCEL which will store face of all the edges
// vector<DCEL*> finVector;

// void DecomposeDCEL(vector<Vertex*> &v, int interior, int exterior) {
//     cout<<"Running started\n";
//     if(v.size()<=3) {
//         return;
//     }

//     vector<Vertex*> path;
//     vector<Vertex*> remaining;
//     path.push_back(v[0]);
//     path.push_back(v[1]);

//     double min_x = INT_MAX;
//     double max_y = INT_MIN;
//     double min_y = INT_MAX;
//     double max_x = INT_MIN;

//     int i = 2;
//     while(i<v.size() and isNotReflex(path[path.size()-2], path[path.size()-1], v[i]) and isNotReflex(path[path.size()-1], v[i], path[0]) and isNotReflex(v[i],path[0],path[1])) {
//         path.push_back(v[i]);
//         min_x = min(min_x, v[i]->coordinates.first);
//         max_x = max(max_x, v[i]->coordinates.first);
//         min_y = min(min_y, v[i]->coordinates.second);
//         max_y = max(max_y, v[i]->coordinates.second);
//         i++;
//     }

//     if(i==v.size()-1) {
//         if(isNotReflex(v[i-1], v[i], v[0]) && isNotReflex(v[i], v[0], v[1])) {
//             path.push_back(v[i]);
//             min_x = min(min_x, v[i]->coordinates.first);
//             max_x = max(max_x, v[i]->coordinates.first);
//             min_y = min(min_y, v[i]->coordinates.second);
//             max_y = max(max_y, v[i]->coordinates.second);
//             i++;
//         }
//     }
//     cout<<"Path found of size: "<<path.size()<<"\n";    
//     //If path.size()=2, change starting point
//     if(path.size()==2) {
//         // cout<<"New Starting Coordinates"<<v[1]->coordinates.first<<","<<v[1]->coordinates.second<<"\n";
//         // for(int i = 1; i<v.size(); i++) {
//         //     remaining.push_back(v[i]);
//         // }
//         // remaining.push_back(v[0]);
//         //remaining.push_back(v[1]);
//         //remaining.push_back(v[2]);
//         for(int j=path.size(); j<v.size(); j++) {
//             remaining.push_back(v[j]);
//         }
//         for(int j = 0; j<path.size(); j++) {
//             remaining.push_back(v[j]);
//         }
//         DecomposeDCEL(remaining,interior,exterior);
//     }
//     //Else
//     //Proceed with algo
//     else {
//         cout<<"Loop entered successfully\n";
//         while(i<v.size()) {
//             remaining.push_back(v[i]);
//             i++;
//         }

//         cout<<"Remaining path created\n";
//         DCEL* tempDCEL = new DCEL();
//         tempDCEL->makeDCEL(path, interior, exterior);
        
//         cout<<"DCEL Created\n";
//         if(path.size()!=v.size()) {
//             //Draw lsvp for remaining
//             vector<Vertex*> lpvs;
//             if(remaining.size()>1 and !isNotReflex(remaining[remaining.size()-1], remaining[0], remaining[1])) {
//                 lpvs.push_back(remaining[0]);
//             }
//             for(int i = 1; i<remaining.size()-1; i++) {
//                 if(!isNotReflex(remaining[i-1], remaining[i], remaining[i+1])) {
//                     lpvs.push_back(remaining[i]);
//                 }
//             }
//             if(remaining.size()>1 and !isNotReflex(remaining[remaining.size()-2], remaining[remaining.size()-1], remaining[0])) {
//                 lpvs.push_back(remaining[remaining.size()-1]);
//             }    
//             cout<<"LPVS Created\n";
//             //Create a temporary vector notch which will initially contain entire lpvs
            
//             vector<Vertex*> notch = lpvs;
//             //If that point is not inside, remove it from notch
//             while(notch.size()!=0) {
//                 //Else, backtrack and restrore notch to lpvs
//                 cout<<"Loop 1\n";
//                 vector<Vertex*> notch = lpvs;
//                 int cur = notch.size()-1;
//                 bool back = false;
//                 while(cur>=0 and !back and !path.empty()) {
//                     cout<<"Loop 2\n";
//                     cout<<"Size: "<<notch.size()<<endl;
//                     auto temp = notch[cur];
//                     if((temp->coordinates.first>=min_x && temp->coordinates.first<=max_x) && (temp->coordinates.second>=min_y && temp->coordinates.second<=max_y)) {
//                         if(!checkInside(tempDCEL, temp)) {
//                             path.pop_back();
//                             tempDCEL->edges.pop_back();
//                             tempDCEL->edges.pop_back();
//                             if(!path.empty()) {
//                                 tempDCEL->edges.push_back(addEdge(path[path.size()-1], path[0], path[0]->inc_edge->left, path[0]->inc_edge->twin->left));
//                             }
//                             back = true;
//                             cout<<"Exit because of back\n";
//                         }
//                         else {
//                             notch.pop_back();
//                         }
                        
//                     }
//                     else {
//                         notch.pop_back();
//                     }
//                     //notch.erase(notch.begin()+cur);
//                     cur--;
//                 }
//                 cout<<"Size outside: "<<notch.size()<<" "<<path.size()<<" Cur: "<<cur<<endl;
//                 if(notch.size()==0) {
//                     break;
//                 }
                
//             } 
            
//         }
//         if(tempDCEL->edges.size()<2) {
//             for(int i = 0; i<tempDCEL->edges.size(); i++) {
//                 remaining.push_back(tempDCEL->edges[i]->origin);
//             }
//             DecomposeDCEL(remaining,interior,exterior);
//         }
//         else {
//             finVector.push_back(tempDCEL);
//             interior++;

//             vector<Vertex*> newSet;
//             newSet.push_back(path[0]);
//             newSet.push_back(path[path.size()-1]);
//             for(int i = 0; i<remaining.size(); i++) {
//                 newSet.push_back(remaining[i]);
//             }
//             DecomposeDCEL(newSet,interior,exterior);
//         }
        

//     }   
// }

#include <bits/stdc++.h>
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
            inc_edge = NULL;
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
                cout<<"Edge "<<(i+1)<<" ends  at ("<<edges[i]->twin->origin->coordinates.first<<","<<edges[i]->twin->origin->coordinates.second<<")\n";
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
 
//Create a global variable with total face count
//Create a global DCEL which will store face of all the edges
vector<DCEL*> finVector;
 
void DecomposeDCEL(vector<Vertex*> &v, int interior, int exterior) {
    cout<<"Running started with x as: "<<v[0]->coordinates.first<<" and y as: "<<v[0]->coordinates.second<<" having size"<<v.size()<<"\n";
    if(v.size()<=3) {
        return;
    }
 
    vector<Vertex*> path;
    vector<Vertex*> remaining;
    path.push_back(v[0]);
    path.push_back(v[1]);
 
    double min_x = INT_MAX;
    double max_y = INT_MIN;
    double min_y = INT_MAX;
    double max_x = INT_MIN;
 
    int i = 2;
    while(i<v.size() and isNotReflex(path[path.size()-2], path[path.size()-1], v[i]) and isNotReflex(path[path.size()-1], v[i], path[0]) and isNotReflex(v[i],path[0],path[1])) {
        path.push_back(v[i]);
        min_x = min(min_x, v[i]->coordinates.first);
        max_x = max(max_x, v[i]->coordinates.first);
        min_y = min(min_y, v[i]->coordinates.second);
        max_y = max(max_y, v[i]->coordinates.second);
        i++;
    }
    if(i==v.size()-1) {
        if(isNotReflex(v[i-1],v[i],v[0]) and isNotReflex(v[i],v[0],v[1])) {
            path.push_back(v[i]);
            min_x = min(min_x, v[i]->coordinates.first);
            max_x = max(max_x, v[i]->coordinates.first);
            min_y = min(min_y, v[i]->coordinates.second);
            max_y = max(max_y, v[i]->coordinates.second);
            i++;
        }
    }
    cout<<"Path found of size: "<<path.size()<<"\n";    
    //If path.size()=2, change starting point
    if(path.size()==2) {
        for(int j =path.size(); j<v.size(); j++) {
            remaining.push_back(v[j]);
        }
        for(int j = 0; j<path.size(); j++) {
            remaining.push_back(v[j]);
        }
        DecomposeDCEL(remaining,interior,exterior);
    }
    //Else
    //Proceed with algo
    else {
        cout<<"Loop entered successfully\n";
        while(i<v.size()) {
            remaining.push_back(v[i]);
            i++;
        }
 
        cout<<"Remaining path created\n";
        DCEL* tempDCEL = new DCEL();
        tempDCEL->makeDCEL(path, interior, exterior);
        
        cout<<"DCEL Created\n";
        if(path.size()!=v.size()) {
            //Draw lsvp for remaining
            vector<Vertex*> lpvs;
            if(remaining.size()>1 and !isNotReflex(remaining[remaining.size()-1], remaining[0], remaining[1])) {
                lpvs.push_back(remaining[0]);
            }
            for(int i = 1; i<remaining.size()-1; i++) {
                if(!isNotReflex(remaining[i-1], remaining[i], remaining[i+1])) {
                    lpvs.push_back(remaining[i]);
                }
            }
            if(remaining.size()>1 and !isNotReflex(remaining[remaining.size()-2], remaining[remaining.size()-1], remaining[0])) {
                lpvs.push_back(remaining[remaining.size()-1]);
            }    
            cout<<"LPVS Created\n";
            //Create a temporary vector notch which will initially contain entire lpvs
            
            vector<Vertex*> notch = lpvs;
            //If that point is not inside, remove it from notch
            while(notch.size()!=0) {
                //Else, backtrack and restrore notch to lpvs
                cout<<"Loop 1\n";
                vector<Vertex*> notch = lpvs;
                int cur = notch.size()-1;
                bool back = false;
                while(cur>=0 and !back and !path.empty()) {
                    cout<<"Loop 2\n";
                    cout<<"Size: "<<notch.size()<<endl;
                    auto temp = notch[cur];
                    if((temp->coordinates.first>=min_x && temp->coordinates.first<=max_x) && (temp->coordinates.second>=min_y && temp->coordinates.second<=max_y)) {
                        if(!checkInside(tempDCEL, temp)) {
                            path.pop_back();
                            tempDCEL->edges.pop_back();
                            tempDCEL->edges.pop_back();
                            if(!path.empty()) {
                                tempDCEL->edges.push_back(addEdge(path[path.size()-1], path[0], path[0]->inc_edge->left, path[0]->inc_edge->twin->left));
                            }
                            back = true;
                            cout<<"Exit because of back\n";
                        }
                        else {
                            notch.pop_back();
                        }
                        
                    }
                    else {
                        notch.pop_back();
                    }
                    //notch.erase(notch.begin()+cur);
                    cur--;
                }
                cout<<"Size outside: "<<notch.size()<<" "<<path.size()<<" Cur: "<<cur<<endl;
                if(notch.size()==0) {
                    break;
                }
                
            } 
            
        }
        finVector.push_back(tempDCEL);
        interior++;
 
        vector<Vertex*> newSet;
        newSet.push_back(path[0]);
        newSet.push_back(path[path.size()-1]);
        for(int i = 0; i<remaining.size(); i++) {
            newSet.push_back(remaining[i]);
        }
        DecomposeDCEL(newSet,interior,exterior);
 
    }
}

int main() {
    ifstream fin;
    fin.open("input.txt");
    vector<Vertex*> v;
    int n;
    fin >> n;

    for(int i = 0; i<n; i++) {
        double x,y;
        fin >> x >> y;
        cout << x << " " << y << endl;
        Vertex* temp = new Vertex(x,y);
        v.push_back(temp);
    }
    for(int i = 0; i<v.size(); i++) {
        cout<<v[i]->coordinates.first<<" "<<v[i]->coordinates.second<<endl;
    }
    
    // Vertex* v1 = new Vertex(0,0);
    // Vertex* v2 = new Vertex(1,0);
    // Vertex* v3 = new Vertex(1,1);
    // Vertex* v4 = new Vertex(0,1);
    // Vertex* v5 = new Vertex(-1,2);
    // Vertex* v6 = new Vertex(-1,1);
    // Vertex* v7 = new Vertex(-1,0);
    // Vertex* v8 = new Vertex(-0.5,-5);
    // //cout<<"Bool"<<InLine(v7,v1,v2)<<endl;
    // v.push_back(v1);
    // v.push_back(v2);
    // v.push_back(v3);
    // v.push_back(v4);
    // v.push_back(v5);
    // v.push_back(v6);
    // v.push_back(v7);
    reverse(v.begin(),v.end());
    DCEL* d = new DCEL();
    d->makeDCEL(v,1,0);
    finVector.push_back(d);
    DecomposeDCEL(v,2,0);

    ofstream fout;
    fout.open("plotData.txt");
    for(auto temp:finVector) {
        // temp->PrintDCEL();
        string x="";
        string y="";
        for(auto tempedge:temp->edges) {
            x+= to_string(tempedge->origin->coordinates.first);
            x+=" ";
            y+= to_string(tempedge->origin->coordinates.second);
            y+=" ";
           //cout<<"("<<x<<","<<y<<")"<<" ";
        }
        x += to_string(temp->edges[0]->origin->coordinates.first);
        y += to_string(temp->edges[0]->origin->coordinates.second);
        // x.pop_back();
        // y.pop_back();
        // cout << x << endl;
        // cout << y << endl;
        fout<<x<<endl;
        fout<<y<<endl;
    }
    fout.close();
    return 0;
}