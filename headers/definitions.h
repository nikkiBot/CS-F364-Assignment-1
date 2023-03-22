/**
 * @file definitions.h
 * @brief Contains the declarations of all the functions and classes used in the program
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
using namespace std;
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

class Vertex ;
class Edge;
class Face;
class DCEL;

//Global variables

//Variables for the decomposition process
vector<DCEL*> finVector; //vector to store every polygon in the decomposition

//Variables for the merging process
vector<Edge*> listofDiagonals; //list to store all the diagonals
unordered_map<Vertex*, vector<pair<int, Vertex*>>> LP; //LP[vj] = (k,vr) where k is polygon number and vr is the other vertex of diagonal
vector<bool> LDP; //A boolean list LDP such that LDP[i] = true means ith polygon is definitive
vector<int> LUP; //LUP[i] = j means a polygon with index i is a part of polygon with index j
vector<DCEL*> mergedDCELs ; //vector to store every polygon in the decomposition after merging

//Function declarations for making the DCEL
Edge* addEdge(Vertex *start1, Vertex *end1, Face* face_id_int, Face* face_id_ext);
bool direction(Vertex* a, Vertex* b, Vertex* c) ;
bool checkInside(DCEL* d,Vertex* p) ;

//Function declarations for the decomposition process
bool isNotReflex(Vertex* a, Vertex* b, Vertex* c);
vector<Vertex*> rotateVector(vector<Vertex*> v) ;
void DecomposeDCEL(vector<Vertex*> &v, int interior, int exterior);



//Function declarations for the merging process
void InitLP() ;
void InitLDP() ;
void InitLUP() ;
void MergePolygons(int i, int j,int k, Edge* e) ;
void Merging() ;
void StoreMergedDCELs() ;
bool isConvex(Vertex* a); //@TODO: Implement this function
Vertex *Next(DCEL* d, Vertex* v); //@TODO: Implement this function
Vertex *Previous(DCEL* d, Vertex* v); //@TODO: Implement this function
int ang(Vertex* a, Vertex* b, Vertex* c, Vertex* d, Vertex* e, Vertex* f); //@TODO: Implement this function




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
        vector<Edge*> edges;

        void makeDCEL(vector<Vertex*> v, int interior, int exterior);
        void PrintDCEL();
        void decomposeEdge(int start, int end, int f) ;
};

#endif // DEFINITIONS_H


