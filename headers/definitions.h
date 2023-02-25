#pragma once 
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief This class represents a vertex in the DCEL
 * @param coordinates The coordinates of the vertex
 * @param identity The identity of the vertex
 * @param inc_edge The pointer to an incident edge which has this vertex as its origin
 */
class Vertex {
    public:
        pair<float, float> coordinates;
        int identity ;
        Edge *inc_edge; 
};

/**
 * @brief This class represents an edge in the DCEL
 * @param origin The pointer to the origin vertex of the edge
 * @param twin The pointer to the twin edge, opposing direction
 * @brief destination for the edge is origin of e.twin
 * @param left The pointer to the incident face, which is the face to the left of the edge
 * @param next The pointer to the next edge in the face, counter-clockwise order
 * @param prev The pointer to the previous edge in the face, counter-clockwise order
 */
class Edge {
    public:
        Vertex *origin;
        Edge *twin;
        Face *left;
        Edge *next ;
        Edge *prev ;
};

/**
 * @brief This class represents a face in the DCEL
 * @param incident_edge pointer to a single edge for which this face is the incident face
 * @param id keeps track of the identity of the face
 */
class Face {
    public:
        Edge *incident_edge; 
        int id;
};
