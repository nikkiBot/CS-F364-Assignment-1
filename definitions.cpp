/**
 * @file definitions.cpp
 * @brief Contains the definitions of all the functions used in the program
 * @author Nishith Kumar (2020A7PS0157H)
 * @author Anshul Kanodia (2020A7PS0174H)
 * @author Suvigya Sharma (2020A7PS0140H)
 * @author Vartika Gupta (2019A7PS0729H)
 * @date 2023-03-23
 * 
 * @version 3.0.1
 * @bug No known bugs
 */

#include <bits/stdc++.h>
#include "./headers/definitions.h"
using namespace std;
// Path: headers/definitions.h


/**
 * @brief Adds an edge to the DCEL between two given vertices
 * 
 * @param start The pointer to the origin vertex of the edge
 * @param end The pointer to the destination vertex of the edge
 */
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

/**
 * @brief The function takes in a vector of vertices and creates a DCEL
 * @param v the set of vertices in ccw order
 * @param interior the face id for the interior face
 * @param exterior the face id for the exterior face
 */
void DCEL::makeDCEL(vector<Vertex*> v, int interior, int exterior) {
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
void DCEL::PrintDCEL() 
{
    for(int i = 0; i<edges.size(); i++) {
        cout<<"Edge "<<(i+1)<<" Starts  from ("<<edges[i]->origin->coordinates.first<<","<<edges[i]->origin->coordinates.second<<")\n";
        cout<<"Edge "<<(i+1)<<" ends  at ("<<edges[i]->twin->origin->coordinates.first<<","<<edges[i]->twin->origin->coordinates.second<<")\n";
        cout<<"Current Edge is on Face:"<<edges[i]->left->id<<endl;
    }
}
/**
 * @brief The function takes in a start and end edge adds a 'virtual' edge between them, creating new faces
 * @param start - index of first vertex
 * @param end - index of last vertex
 * @param f - total number of faces in dcel
 */
void DCEL::decomposeEdge(int start, int end, int f) {
        //Edge* e = edges[start];
        //Edge* f = edges[end];
        Face* face_new = new Face();
        face_new->id = f+1;
        for(int i = start; i<=end; i++) {
            edges[i]->left = face_new;
            
        }
}

/**
 * @brief The function checks if a point is to the left of the edge between two vertices
 * 
 * @param a first vertex forming the edge
 * @param b second vertex forming the edge
 * @param c vertex to be checked
 * @return true/1 if c is to the left
 * @return false otherwise
 */
bool direction(Vertex* a, Vertex* b, Vertex* c)
{
    int val = (c->coordinates.second-a->coordinates.second)*(b->coordinates.first-a->coordinates.first) - (c->coordinates.first-a->coordinates.first)*(b->coordinates.second-a->coordinates.second);
    if (val > 0)
        return true;
 
    return false;
}


/**
 * @brief The function checks if a point is inside the given polygon
 * 
 * @param d the DCEL of the polygon
 * @param p vertex to be checked
 * @return true/1 if inside
 * @return false/0 otherwise
 */
bool checkInside(DCEL* d,Vertex* p)
{
    int start = 0 ;
    int end = d->edges.size()-1;
    
    if ((end-start+1) < 3)
        return false; // When polygon has less than 3 edge, it is not polygon
 
    for(int i = start; i<=end; i++) {
        
        bool temp = direction(d->edges[i]->origin, d->edges[i]->twin->origin, p);
        if (!temp) {
            //cout<<"False because of edge at index:"<<i<<"\n";
            return false;
        }
    } 
    return true;
}

/**
 * @brief Returns true if angle made between the two edges formed by 3 vertices is reflex or not. Check Documentation to see how cross product is used to check if angle is reflex or not
 * 
 * @param a - first vertex
 * @param b - second vertex, the common vertex between the two edges
 * @param c - third vertex
 * @return true/1 if not reflex 
 * @return false/0 otherwise
 */
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

/**
 * @brief Change the starting index of the vector to the next index of previous starting index
 * 
 * @param v the vector to be rotated
 * @return vector<Vertex*> new vector with the starting index changed
 */
vector<Vertex*> rotateVector(vector<Vertex*> v) {
    vector<Vertex*> newVector;
    for(int i = 1; i<v.size(); i++) {
        newVector.push_back(v[i]);
    }
    newVector.push_back(v[0]);
    return newVector;
}

/*** ****** ********@Todo********* ********** ***/
bool isConvex(Vertex*a) {

   return;
}

Vertex* Next(DCEL* d, Vertex* v) {
    for(int i = 0; i<d->edges.size(); i++) {
        if(d->edges[i]->origin == v) {
            return d->edges[i]->twin->origin;
        }
    }
    return NULL;
}

Vertex* Previous(DCEL* d, Vertex* v) {
    for(int i = 0; i<d->edges.size(); i++) {
        if(d->edges[i]->twin->origin == v) {
            return d->edges[i]->origin;
        }
    }
    return NULL;
}
int ang(Vertex* a, Vertex* b, Vertex* c, Vertex* d, Vertex* e, Vertex* f) {
    return 0;
}

/*** ****** ********@Todo********* ********** ***/

/**
 * @brief The function takes in a vector of vertices(of the polygon) and implements the decompose algorithm 
 * 
 * @param v vector of vertices in ccw order
 * @param interior face id of the interior face
 * @param exterior face id of the exterior face
 */
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

    vector<Vertex*> path; //longest current path
    vector<Vertex*> remaining; //Total vertices - Vertices in Path
    vector<Vertex*> popped;//Notches in path which have been popped cause inside the created polygon
    
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
    
    //final iteration:The loop gives a bug at last vertex(since loop cannot form a cycle) and thus has to be dealt separately
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
        
        remaining = rotateVector(v); //cyclically increase index and new initial vertex is the next vertex of original vector
        DecomposeDCEL(remaining,interior,exterior); //recall decompose on new vector
    }
    //Else proceed with algo (since path got created the way it was intended to be)
    else {
        cout<<"Loop entered successfully\n";
        while(i<v.size()) {
            remaining.push_back(v[i]);
            i++;
        }

        cout<<"Remaining path created\n";
        
        DCEL* tempDCEL = new DCEL(); //make one DCEL with current path vector,interior and exterior face values
        tempDCEL->makeDCEL(path, interior, exterior);
        
        cout<<"DCEL Created\n";
        //if path doesnt contain all elements of v
        if(path.size()!=v.size()) {
            
            vector<Vertex*> lpvs; //Draw lsvp(the vector storing notches) for remaining vector
            
            if(v.size()>1 and !isNotReflex(v[v.size()-1], v[0], v[1])) {
                lpvs.push_back(v[0]); //Base case : reflex angle at V0 => push it to lpvs
            }
            for(int i = 1; i<v.size()-1; i++) {
                if(!isNotReflex(v[i-1], v[i], v[i+1])) {
                    lpvs.push_back(v[i]); //Do the same for next vertices and keep pushing
                }
            }
            if(v.size()>1 and !isNotReflex(v[v.size()-2], v[v.size()-1], v[0])) {
                lpvs.push_back(v[v.size()-1]); //Checking for final vertex
            }    
            cout<<"LPVS Created\n";
            
            
            vector<Vertex*> notch = lpvs;//Create a temporary vector notch which will initially contain entire lpvs
            //If that point is not inside, remove it from notch
            //The loop iterates through notch vector and removes elements that are outside the decomposed polygon, then remove it 
            //Else, backtrack and restrore notch to lpvs
            while(notch.size()!=0) {
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


/**
 * @brief Function to initialise LP
 * 
 * @return void
 */
void InitLP() {
    for(int i = 0; i<listofDiagonals.size(); i++) {
        LP[listofDiagonals[i]->origin].push_back({listofDiagonals[i]->left->id, listofDiagonals[i]->twin->origin});
    }
}

/**
 * @brief Function to initialise LDP
 * 
 * @return void
 */
void InitLDP() {
    LDP.push_back(false);
    for(int i = 1; i<=finVector.size(); i++) {
        LDP.push_back(true);
    }
}

/**
 * @brief Function to initialise LUP
 * 
 * @return void
 */
void InitLP() {
    LUP.push_back(0);
    for(int i = 1; i<=finVector.size(); i++) {
        LUP.push_back(i);
    }
}

//Function to merge 2 polygons connected by the edge e
/**
 * @brief Function to merge 2 polygons connected by the edge e
 * 
 * @param i index of first polygon
 * @param j index of second polygon
 * @param k index of new polygon
 * @param e the edge connecting the 2 polygons
 * @return void
 */
void MergePolygons(int i, int j, int k, Edge* e) {
    vector<Edge*> e1 = finVector[i-1]->edges;
    vector<Edge*> e2 = finVector[j-1]->edges;

    vector<Edge*> e3;
    for(auto temp: e1) {
        if((temp->origin!=e->origin and temp->twin->origin!=e->twin->origin) or (temp->origin!=e->twin->origin and temp->twin->origin!=e->origin)) {
            temp->left->id=k;
            e3.push_back(temp);
        }
    }
    for(auto temp: e2) {
        if((temp->origin!=e->origin and temp->twin->origin!=e->twin->origin) or (temp->origin!=e->twin->origin and temp->twin->origin!=e->origin)) {
            temp->left->id=k;
            e3.push_back(temp);
        }
    }
    DCEL* d = new DCEL();
    d->edges = e3;
    finVector.push_back(d);
}


/**
 * @brief Function to implement the merging algorithm
 * 
 * @return void
 */
void Merging() {
    //Initialise all the variables
    InitLDP();
    InitLP();
    InitLUP();

    int m = listofDiagonals.size();
    for(int i = 0 ; i<m; i++) {
        //For every diagonal, run the if condition
        Vertex* vs = listofDiagonals[i]->origin;
        Vertex* vt = listofDiagonals[i]->twin->origin;

        if((LP[vs].size()>2 and LP[vt].size()>2) or (LP[vs].size()>2 and isConvex(vt)) or (LP[vt].size()>2 and isConvex(vs)) or (isConvex(vs) and isConvex(vt))) {
            Vertex* j2 = vt;
            Vertex* i2 = vs;

            DCEL* Pi = finVector[i]; //Pi is the polygon at index i
            
            Vertex* j3 = Next(Pi,vt);

            Vertex* i1 = Previous(Pi,vs);
            vector<pair<int, Vertex*>> temp = LP[vt];
            int u;
            for(auto tempV: temp) {
                if(tempV.second==vs) {
                    u = tempV.first;
                    break;
                }
            }

            //Pu is the polygon with face value u or finVector[u-1]
            DCEL* Pu = finVector[u-1];
            Vertex* j1 = Previous(Pu,vt);
            Vertex* i3 = Next(Pu,vs);

            if(ang((i1,i2,i3),(j1,j2,j3))<=180) {
                //Merge the ith and jth polygon
                int newCount = LDP.size();
                Edge* e;
                for(auto temp:listofDiagonals) {
                    if(temp->origin==vt and temp->twin->origin==vs) {
                        e = temp;
                        break;
                    }
                }
                MergePolygons(i,u, newCount, e);
                LDP[i] = false;
                LDP[u] = false;

                LDP.push_back(true);
                LUP[i] = newCount;
                LUP[u] = newCount;
                for(int h = 1; h<newCount; h++) {
                    if(LUP[h]==i or LUP[h]==u) {
                        LUP[h]= newCount;
                    }
                }
                LUP.push_back(newCount);
            }
        }
    }
}

/**
 * @brief Function to capture the merging of DCELs, uses the global array mergedDCELs
 * 
 * @return void
 */
void StoreMergedDCELs() {
    vector<bool> marked(LDP.size(), false);
    for(int i = i; i<LDP.size(); i++) {
        int j = LUP[i];
        if(i==j) {
            mergedDCELs.push_back(finVector[i-1]);
        }
    }    
}