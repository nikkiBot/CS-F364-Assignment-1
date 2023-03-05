#include <bits/stdc++.h>
#include "./headers/definitions.h"
using namespace std;
// Path: headers/definitions.h
#ifndef DEFINITIONS_H
#define DEFINITIONS_H


/**
 * @brief Adds an edge to the DCEL between two given vertices
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
 * @brief This function splits an edge into two edges
 * @param e The pointer to the edge to be split
 */
void split(Edge *e)
{
    Vertex *v = new Vertex(); // create a new vertex in the middle of the edge
    pair<float,float> midpoint ;
    midpoint.first = (e->origin->coordinates.first + e->twin->origin->coordinates.first) / 2 ;
    midpoint.second = (e->origin->coordinates.second + e->twin->origin->coordinates.second) / 2 ;
    v->coordinates = midpoint ;
    v->identity = e->origin->identity ;
    v->inc_edge = e->next ;
    return ;
}

/**
 * @brief This function splits two edges into two edges, e1 is broken into e1 and e2, e2 being returned
 * @param e1 The pointer to the first edge to be split
 * @param e2 The pointer to the second edge to be split
 */
Edge* split(Edge *e1, Edge *e2)
{
   Vertex *v = e2->origin ;
   Vertex *u = e1->twin->origin ;
   Edge *temp = addEdge(v, u, e1->left, e1->twin->left) ;
   e2 = temp ;
   e2->next = e1->next ;
   e1->next->prev = e2 ;
   e1->next = e2 ;
   e2->prev = e1 ;
   //Managing the twins ;
   e1 = e1->twin ;
   e2 = e2->twin ;
   e2->prev = e1->prev ;
   e1->prev->next = e2 ;
   e1->prev = e2 ;
   e2->next = e1 ;
   return e2 ;
}

double get_clockwise_angle(const Vertex& p)
{   
    double angle = 0.0;
    angle = -atan2(p.coordinates.first,-p.coordinates.second);
    return angle;
}
bool compare_points(const Vertex& a, const Vertex& b)
{
    return (get_clockwise_angle(a) > get_clockwise_angle(b));
}

void sortCounterClockwise(vector<pair<double, double>> &inputPointString) {
    sort(inputPointString.begin(), inputPointString.end(), compare_points);
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
        cout<<"Edge "<<(i+1)<<" ends  from ("<<edges[i]->twin->origin->coordinates.first<<","<<edges[i]->twin->origin->coordinates.second<<")\n";
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
 * @brief Returns true if angle made between the two edges formed by 3 vertices is reflex or not. Check Documentation to see how cross product is used to check if angle is reflex or not
 * 
 * @param a - first vertex
 * @param b - second vertex, the common vertex between the two edges
 * @param c - third vertex
 * @return true 
 * @return false 
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

/**
 * @brief returns point in interation where we have to backtrack
 * 
 * @param d - pointer to the DCEL object
 * @return Vertex* point where we have to backtrack
 */
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

#endif // DEFINITIONS_H


