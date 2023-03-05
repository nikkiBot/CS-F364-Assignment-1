#pragma once 
#include <bits/stdc++.h>
using namespace std;

class Vertex ;
class Edge;
class Face;


//Function declarations
void split(Edge *e);
Edge* split(Edge *e1, Edge *e2);
Edge* addEdge(Vertex *start1, Vertex *end1, Face* face_id_int, Face* face_id_ext);
double get_clockwise_angle(const Vertex& p) ;
bool compare_points(const Vertex& a, const Vertex& b);
void sortCounterClockwise(vector<pair<double, double>> &inputPointString);
bool reflexOrNot(Vertex* a, Vertex* b, Vertex* c);
Vertex* lastConcaveVertex(DCEL* d);



/**
 * @brief This class represents a vertex in the DCEL
 * @param coordinates The coordinates of the vertex
 * @param identity The identity of the vertex
 * @param inc_edge The pointer to an incident edge which has this vertex as its origin
 */
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
        Vertex *origin = NULL;
        Edge *twin = NULL;
        Face *left = NULL;
        Edge *next = NULL;
        Edge *prev = NULL;
};


/**
 * @brief This class represents a face in the DCEL
 * @param incident_edge pointer to a single edge for which this face is the incident face
 * @param id keeps track of the identity of the face
 */
class Face {
    public:
        Edge *incident_edge = NULL; 
        int id = 0;
};

/**
 * @brief This class represents a doubly connected edge list
 * @param vertices The vector of vertices
 * @param edges The vector of edges
 * @param faces The vector of faces
 */
class DCEL {
    public:
        //vector<Vertex> vertices;
        vector<Edge*> edges;
        //vector<Face> faces;
        void makeDCEL(vector<Vertex*> v, int interior, int exterior);
        void PrintDCEL() ;
        void decomposeEdge(int start, int end, int f) ;
};

