/**
 * @file test.cpp
 * @brief Convex Polygon Decomposition Algorithm 
 * @author Nishith Kumar (2020A7PS0157H)
 * @author Anshul Kanodia (2020A7PS0174H)
 * @author Suvigya Sharma (2020A7PS0140H)
 * @author Vartika Gupta (2019A7PS0729H)
 * @version 3.0.1
 * 
 * 
 * @bug Not working for hand_nodes.txt, i18.txt
 * @bug star.txt giving weird output 
 */


#include "./headers/definitions.h"
#include <bits/stdc++.h>
// #include "./testcases/bird.txt" //uncomment and test if folder can be accessed
using namespace std ;
// Path: headers/definitions.h


//To Reverse: bird.txt, flower.txt, input3.txt, input5.txt, rangoli.txt, input4.txt, indonesia.txt, malaysia.txt, india.txt, china.txt
int main() {
    ifstream fin;
    fin.open("./testcases/bird.txt");
    vector<Vertex*> v;
    int n;
    fin >> n;

    for(int i = 0; i<n; i++) {
        double x,y;
        fin >> x >> y;
        cout << x << " " << y << endl;
        Vertex* temp = new Vertex(x,y);
        v.push_back(temp);
    }
    
    //Reverse Only When Input in clockwise Order
    reverse(v.begin(),v.end());

    DecomposeDCEL(v,1,0);
    
    //Print List of Diagonals
    cout<<"No. of Diagonals: "<<listofDiagonals.size()<<endl;
    for(int i = 0; i<listofDiagonals.size(); i++) {
        cout<<listofDiagonals[i]->origin->coordinates.first<<" "<<listofDiagonals[i]->origin->coordinates.second<<" Connected to "<<listofDiagonals[i]->twin->origin->coordinates.first<<" "<<listofDiagonals[i]->twin->origin->coordinates.second<<endl;
        cout<<"This edge is on face: "<<listofDiagonals[i]->left->id<<endl;
    }

    Merging();
    StoreMergedDCELs();

    ofstream fout;
    fout.open("plotData.txt");
    for(auto temp:mergedDCELs) {
        temp->PrintDCEL();
        string x="";
        string y="";
        for(auto tempedge:temp->edges) {
            x+= to_string(tempedge->origin->coordinates.first);
            x+=" ";
            y+= to_string(tempedge->origin->coordinates.second);
            y+=" ";
           //cout<<"("<<x<<","<<y<<")"<<" ";
        }
        x += to_string(temp->edges[0]->origin->coordinates.first);
        y += to_string(temp->edges[0]->origin->coordinates.second);

        fout<<x<<endl;
        fout<<y<<endl;
    }
    
    fout.close();
    return 0;
}