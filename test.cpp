#include "./headers/definitions.h"
#include <bits/stdc++.h>
using namespace std ;
// Path: headers/definitions.h

int main() {
    vector<Vertex*> v;
    Vertex* v1 = new Vertex(0,0);
    Vertex* v2 = new Vertex(1,0);
    Vertex* v3 = new Vertex(1,1);
    Vertex* v4 = new Vertex(0,1);
    Vertex* v5 = new Vertex(-1,2);
    Vertex* v6 = new Vertex(-1,1);
    Vertex* v7 = new Vertex(-1,0);
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    v.push_back(v5);
    v.push_back(v6);
    v.push_back(v7);

    DCEL* d  = new DCEL();
    d->makeDCEL(v, 1,2);
    //d->PrintDCEL();
    d->decomposeEdge(3,4,2);
    d->PrintDCEL();
    return 0;
}