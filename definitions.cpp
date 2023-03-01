#include "./headers/definitions.h"
using namespace std;
// Path: headers/definitions.h
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/**
 * @brief Default constructor for the Edge class
 */
Edge::Edge()
{
    origin = NULL ;
    twin = NULL ;
    left = NULL ;
    next = NULL ;
    prev = NULL ;
}

/**
 * @brief Parameterized constructor for the Edge class
 * @param v The pointer to the origin vertex of the edge
 * @param next The pointer to the next edge in the face, counter-clockwise order
 */
Edge::Edge(Vertex *v,Edge *next)
{
    origin = v ;
    twin = NULL ;
    left = NULL ;
    this->next = next ;
    prev = NULL ;
}

/**
 * @brief Parameterized constructor for the Edge class
 * @param start The pointer to the origin vertex of the edge
 * @param end The pointer to the destination vertex of the edge
 */
Edge::Edge(Vertex *start, Vertex *end)
{
    Edge *e = new Edge ;
    Edge *f = new Edge ;
    e->origin = start ;
    e->twin = f ;
    e->twin->prev = e->next ;
    e->twin->next = e->prev ;
    e->twin->origin = end ;
}

/**
 * @brief This function splits an edge into two edges
 * @param e The pointer to the edge to be split
 */
void split(Edge *e)
{
    Vertex *v = new Vertex; // create a new vertex in the middle of the edge
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
    Edge *temp = new Edge(v,u) ;
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

/**
 * @brief This function builds the DCEL from a set of points
 * @param points The vector of points in counter-clockwise order
 */
void BuildDCEL(vector<pair<double, double>> points)
{
    int n = points.size();
    pair<double, double> start = points[0];
    Vertex *v = new Vertex;
    v->coordinates = start;
    v->identity = 0;
    Vertex *u = new Vertex;
    u->coordinates = points[1];
    u->identity = 1;
    Edge *e = new Edge(v, u);

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

#endif // DEFINITIONS_H
