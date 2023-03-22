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

//1 if to the left 
bool direction(Vertex* a, Vertex* b, Vertex* c)
{
    int val = (c->coordinates.second-a->coordinates.second)*(b->coordinates.first-a->coordinates.first) - (c->coordinates.first-a->coordinates.first)*(b->coordinates.second-a->coordinates.second);
    if (val > 0)
        return true;
 
    return false;
}

//1 if inside
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
            //cout<<"False because of edge at index:"<<i<<"\n";
            return false;
        }
    } 
    
    return true;
}

//1 if not reflex 
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
 
//Create a global vector which will store every polygon in the form of a DCEL
vector<DCEL*> finVector;

//Global Variables for merging process
    //List to store all the diagonals
vector<Edge*> listofDiagonals;
    
    //LP[vj] = (k,vr) where k is polygon number and vr is the other vertex of diagonal
unordered_map<Vertex*, pair<int, Vertex*>> LP;

    //A boolean list LDP such that LDP[i] = true means ith polygon is definitive
vector<bool> LDP;

    //LUP[i] = j means a polygon with index i is a part of polygon with index j
vector<int> LUP;


//Rotate a vector(To change the starting point)
vector<Vertex*> rotateVector(vector<Vertex*> v) {
    vector<Vertex*> newVector;
    for(int i = 1; i<v.size(); i++) {
        newVector.push_back(v[i]);
    }
    newVector.push_back(v[0]);
    return newVector;
}

void DecomposeDCEL(vector<Vertex*> &v, int interior, int exterior) {
    cout<<"Running started with x as: "<<v[0]->coordinates.first<<" and y as: "<<v[0]->coordinates.second<<" having size"<<v.size()<<"\n";
    if(v.size()<3) {
        return;
    }
    if(v.size()==3) {
        DCEL* d = new DCEL();
        d->makeDCEL(v,interior,exterior);
        finVector.push_back(d);
        return;
    }

    //longest current path
    vector<Vertex*> path; 

    //Total vertices - Vertices in Path
    vector<Vertex*> remaining; 
    
    //Notches in path which have been popped cause inside the created polygon
    vector<Vertex*> popped;
    
    //Coordinates of the rectangle
    double min_x = INT_MAX;
    double max_y = INT_MIN;
    double min_y = INT_MAX;
    double max_x = INT_MIN;

    path.push_back(v[0]);
    min_x = min(min_x, v[0]->coordinates.first);
    max_x = max(max_x, v[0]->coordinates.first);
    min_y = min(min_y, v[0]->coordinates.second);
    max_y = max(max_y, v[0]->coordinates.second);
    
    path.push_back(v[1]);
    min_x = min(min_x, v[1]->coordinates.first);
    max_x = max(max_x, v[1]->coordinates.first);
    min_y = min(min_y, v[1]->coordinates.second);
    max_y = max(max_y, v[1]->coordinates.second);

    int i = 2;
    //looping while ignoring relfex angles, this loop completely fills path vector
    while(i<(v.size()-1) and isNotReflex(path[path.size()-2], path[path.size()-1], v[i]) and isNotReflex(path[path.size()-1], v[i], path[0]) and isNotReflex(v[i],path[0],path[1])) {
        path.push_back(v[i]);
        //update the rectangle accordingly
        min_x = min(min_x, v[i]->coordinates.first);
        max_x = max(max_x, v[i]->coordinates.first);
        min_y = min(min_y, v[i]->coordinates.second);
        max_y = max(max_y, v[i]->coordinates.second);
        //print the the vertex that got pushed and rectangle, go to next vertex 
        cout<<"Current Coordinate Pushed in Path:"<<v[i]->coordinates.first<<" "<<v[i]->coordinates.second<<endl;
        cout<<"Value of min and max x-coordinates are:"<<min_x<<" "<<max_x<<endl;
        cout<<"Value of min and max y-cooridinates are:"<<min_y<<" "<<max_y<<endl;
        i++;
    }
    //final iteration:
    //The loop gives a bug at last vertex(since loop cannot form a cycle) and thus has to be dealt separately
    if(i==v.size()-1) {
        if(isNotReflex(v[i-1],v[i],v[0]) and isNotReflex(v[i],v[0],v[1])) {
            path.push_back(v[i]);
            min_x = min(min_x, v[i]->coordinates.first);
            max_x = max(max_x, v[i]->coordinates.first);
            min_y = min(min_y, v[i]->coordinates.second);
            max_y = max(max_y, v[i]->coordinates.second);
            cout<<"Current Coordinate Pushed in Path:"<<v[i]->coordinates.first<<" "<<v[i]->coordinates.second<<endl;
            cout<<"Value of min and max x-coordinates are:"<<min_x<<" "<<max_x<<endl;
            cout<<"Value of min and max y-cooridinates are:"<<min_y<<" "<<max_y<<endl;
            i++;
        }
    }
    cout<<"Path found of size: "<<path.size()<<"\n";    
    //If path.size()=2, change starting point
    if(path.size()==2) {
        //cyclically increase index and new initial vertex is the next vertex of original vector
        remaining = rotateVector(v); 
        //recall decompose on new vector
        DecomposeDCEL(remaining,interior,exterior);
    }
    //Else proceed with algo (since path got created the way it was intended to be)
    else {
        cout<<"Loop entered successfully\n";
        while(i<v.size()) {
            remaining.push_back(v[i]);
            i++;
        }

        cout<<"Remaining path created\n";
        //make one DCEL with current path vector,interior and exterior face values
        DCEL* tempDCEL = new DCEL();
        tempDCEL->makeDCEL(path, interior, exterior);
        
        cout<<"DCEL Created\n";
        //if path doesnt contain all elements of v
        if(path.size()!=v.size()) {
            //Draw lsvp(the vector storing notches) for remaining vector
            vector<Vertex*> lpvs;
            //Base case : reflex angle at V0 => push it to lpvs
            if(v.size()>1 and !isNotReflex(v[v.size()-1], v[0], v[1])) {
                lpvs.push_back(v[0]);
            }
            //Do the same for next vertices and keep pushing
            for(int i = 1; i<v.size()-1; i++) {
                if(!isNotReflex(v[i-1], v[i], v[i+1])) {
                    lpvs.push_back(v[i]);
                }
            }
            //Checking for final vertex
            if(v.size()>1 and !isNotReflex(v[v.size()-2], v[v.size()-1], v[0])) {
                lpvs.push_back(v[v.size()-1]);
            }    
            cout<<"LPVS Created\n";
            
            //Create a temporary vector notch which will initially contain entire lpvs
            vector<Vertex*> notch = lpvs;
            //If that point is not inside, remove it from notch
            //The loop iterates through notch vector and removes elements that are outside the decomposed polygon, then remove it 
            while(notch.size()!=0) {
                //Else, backtrack and restrore notch to lpvs
                cout<<"Loop 1\n";
                vector<Vertex*> notch = lpvs; //reset notch vector
                int current_notch_size = notch.size()-1;
                bool back = false;
                while(current_notch_size>=0 and !back and !path.empty()) {
                    cout<<"Loop 2\n";
                    cout<<"Size: "<<notch.size()<<endl;
                    auto temp = notch[current_notch_size];
                    cout<<"Value of Coordinates being checked:"<<temp->coordinates.first<<" "<<temp->coordinates.second<<"\n";
                    cout<<"Value of min and max x-coordinates are:"<<min_x<<" "<<max_x<<endl;
                    cout<<"Value of min and max y-cooridinates are:"<<min_y<<" "<<max_y<<endl;
                    if((temp->coordinates.first>=min_x && temp->coordinates.first<=max_x) && (temp->coordinates.second>=min_y && temp->coordinates.second<=max_y)) {
                        //If inside, backtrack and pop the last vertex
                        if(checkInside(tempDCEL, temp)) {
                            popped.push_back(path[path.size()-1]);
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
                            cout<<"Popped inside loop 3\n";
                            notch.pop_back();
                        }
                        
                    }
                    else {
                        cout<<"Popped inside loop 2\n";
                        notch.pop_back();
                    }
                    
                    current_notch_size--;
                }
                cout<<"Size outside: "<<notch.size()<<" "<<path.size()<<" Cur: "<<current_notch_size<<endl;
                if(notch.size()==0) {
                    break;
                }
                
            } 
            if(tempDCEL->edges.size()>2) {
                Edge* tedge = tempDCEL->edges[tempDCEL->edges.size()-1];
                listofDiagonals.push_back(tedge);
            }
            
        }

        if(tempDCEL->edges.size()>2) {
            finVector.push_back(tempDCEL);
            interior++;
        }
        

        remaining.push_back(path[0]);
        remaining.push_back(path[path.size()-1]);
        
        for(int i = popped.size()-1; i>=0; i--) {
            remaining.push_back(popped[i]);
        }
        DecomposeDCEL(remaining,interior,exterior);

    }

    
}

//Function to initialise LP
void InitLP() {
    for(int i = 0; i<listofDiagonals.size(); i++) {
        LP[listofDiagonals[i]->origin] = {listofDiagonals[i]->left->id, listofDiagonals[i]->twin->origin};
    }
}

//Function to initialise LDP
void InitLDP() {
    LDP.push_back(false);
    for(int i = 1; i<=finVector.size(); i++) {
        LDP.push_back(true);
    }
}

//Function to initialise LUP
void InitLUP() {
    LUP.push_back(0);
    for(int i = 1; i<=finVector.size(); i++) {
        LUP.push_back(i);
    }
}

//Not working for hand_nodes.txt, i18.txt
//star.txt giving weird output

//To Reverse: bird.txt, flower.txt, input3.txt, input5.txt, rangoli.txt, input4.txt, indonesia.txt, malaysia.txt, india.txt, china.txt
int main() {
    ifstream fin;
    fin.open("bird.txt");
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
    
    //Reverse Only When Input in clockwise Order
    reverse(v.begin(),v.end());

    DecomposeDCEL(v,1,0);
    
    //Print List of Diagonals
    cout<<"No. of Diagonals: "<<listofDiagonals.size()<<endl;
    for(int i = 0; i<listofDiagonals.size(); i++) {
        cout<<listofDiagonals[i]->origin->coordinates.first<<" "<<listofDiagonals[i]->origin->coordinates.second<<" Connected to "<<listofDiagonals[i]->twin->origin->coordinates.first<<" "<<listofDiagonals[i]->twin->origin->coordinates.second<<endl;
        cout<<"This edge is on face: "<<listofDiagonals[i]->left->id<<endl;
    }

    ofstream fout;
    fout.open("plotData.txt");
    for(auto temp:finVector) {
        //temp->PrintDCEL();
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

        fout<<x<<endl;
        fout<<y<<endl;
    }

    InitLDP();
    InitLP();
    InitLUP();

    cout<<"The size of LDP is: "<<LDP.size()<<endl;
    cout<<"The size of LUP is: "<<LUP.size()<<endl;
    
    fout.close();
    return 0;
}