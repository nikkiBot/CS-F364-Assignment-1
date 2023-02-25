#include "./definitions.h"
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
    origin = start ;
    twin->origin = end ;
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


#endif // DEFINITIONS_H
