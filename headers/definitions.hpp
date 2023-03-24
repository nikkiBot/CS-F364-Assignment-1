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

#pragma once

#include <bits/stdc++.h>
using namespace std;
// #ifndef DEFINITIONS_H
// #define DEFINITIONS_H

class Vertex ;
class Edge;
class Face;
class DCEL;

//Global variables

// //Variables for the decomposition process
// extern vector<DCEL*> finVector; //vector to store every polygon in the decomposition

// //Variables for the merging process
// extern vector<Edge*> listofDiagonals; //list to store all the diagonals
// extern unordered_map<Vertex*, vector<pair<int, Vertex*>>> LP; //LP[vj] = (k,vr) where k is polygon number and vr is the other vertex of diagonal
// extern vector<bool> LDP; //A boolean list LDP such that LDP[i] = true means ith polygon is definitive
// extern vector<int> LUP; //LUP[i] = j means a polygon with index i is a part of polygon with index j
// extern vector<DCEL*> mergedDCELs ; //vector to store every polygon in the decomposition after merging
vector<DCEL*> finVector; 
vector<Edge*> listofDiagonals; 
unordered_map<Vertex*, vector<pair<int, Vertex*>>> LP; 
vector<bool> LDP;
vector<int> LUP;
vector<DCEL*> mergedDCELs ;


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
bool isConvex(Vertex* a); 
Vertex *Next(DCEL* d, Vertex* v); 
Vertex *Previous(DCEL* d, Vertex* v); 
int ang(Vertex* a, Vertex* b, Vertex* c, Vertex* d, Vertex* e, Vertex* f); 




/**
 * @brief This class represents a vertex in the DCEL
 */
class Vertex {
    public:
        pair<double, double> coordinates;   //The coordinates of the vertex
        int identity ;                      //The identity of the vertex
        Edge *inc_edge;                     //The pointer to an incident edge which has this vertex as its origin

        Vertex();
        Vertex(double x, double y) {
            coordinates.first = x;
            coordinates.second = y;
        }
};

/**
 * @brief This class represents an edge in the DCEL 
 */
class Edge {
    public:
        Vertex *origin = NULL; //The pointer to the origin vertex of the edge
        Edge *twin = NULL;     //The pointer to the twin edge, opposing direction
        Face *left = NULL;     //The pointer to the incident face, which is the face to the left of the edge
        Edge *next = NULL;     //The pointer to the next edge in the face, counter-clockwise order
        Edge *prev = NULL;     //The pointer to the previous edge in the face, counter-clockwise order
};


/**
 * @brief This class represents a face in the DCEL
 */
class Face {
    public:
        Edge *incident_edge = NULL; //pointer to a single edge for which this face is the incident face
        int id = 0; //keeps track of the identity of the face
};

/**
 * @brief This class represents a doubly connected edge list
 */
class DCEL {
    public:
        vector<Edge*> edges; //The vector of edges

        /**
        * @brief The function takes in a vector of vertices and creates a DCEL
        * @param v the set of vertices in ccw order
        * @param interior the face id for the interior face
        * @param exterior the face id for the exterior face
        */
        void makeDCEL(vector<Vertex*> v, int interior, int exterior);

        void PrintDCEL();

        /**
        * @brief The function takes in a start and end edge adds a 'virtual' edge between them, creating new faces
        * @param start - index of first vertex
        * @param end - index of last vertex
        * @param f - total number of faces in dcel
        */
        void decomposeEdge(int start, int end, int f) ;
};

// #endif // DEFINITIONS_H


