#include "../headers/definitions.h"
#include <bits/stdc++.h>
using namespace std;

/*
To check whether the angle made between the two edges formed from the three vertices is reflex or not, we take the cross product of the two 
vectors formed by the three vertices. If the cross product is positive, then the angle is reflex, else it is convex.

The cross product between the two vectors will always get the angle on the left side plane if it is positive, hence we continue our code to
keep finding the first angle that doesn't give positive cross product, and that is the last concave vertex. We return this vertex to our main 
function from the lastConcaveVertex function.
*/

//Do something if origin is reflex
// Vertex* lastConcaveVertex(DCEL* d);

int main()  {
    /*Vertex* a = new Vertex(1, 2);
    Vertex* b = new Vertex(0, 3);
    Vertex* c = new Vertex(0, 0);
    Vertex* x = new Vertex(3, 3);
    vector<Vertex*> v;
    v.push_back(b);
    v.push_back(c);
    v.push_back(x);
    v.push_back(a);*/
    //cout << reflexOrNot(c,x,a) << endl;
    Vertex* a = new Vertex(0,0);
    Vertex* b = new Vertex(1,0);
    Vertex* c = new Vertex(1,1);
    Vertex* x = new Vertex(0,1);
    Vertex* b1 = new Vertex(-1,2);
    Vertex* c1 = new Vertex(-1,1);
    Vertex* x1 = new Vertex(-1,0);
    vector<Vertex*> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    v.push_back(x);
    v.push_back(b1);
    v.push_back(c1);
    v.push_back(x1);
    
    DCEL *d = new DCEL();
    d->makeDCEL(v, 1, 2);
    //d->PrintDCEL();
    Vertex* ans = lastConcaveVertex(d);
    return 0;           
}