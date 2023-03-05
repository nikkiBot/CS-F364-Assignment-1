#include "./headers/definitions.h"
#include <bits/stdc++.h>
using namespace std ;
// Path: headers/definitions.h
void decomposeDCEL(vector<Vertex*> &v, int interior, int exterior) ;

//Create a global variable with total face count
//Create a global DCEL which will store face of all the edges
vector<DCEL*> finVector;
void decomposeDCEL(vector<Vertex*> &v, int interior, int exterior) {
    if(v.size()<=3) {
        return;
    }
    DCEL* d = new DCEL();
    int n = v.size();
    //d->makeDCEL(v, interior, exterior);    
    //Find the largest path
    vector<Vertex*> remaining;
    vector<Vertex*> path;
    double min_x = INT_MAX;
    double max_y = INT_MIN;
    double min_y = INT_MAX;
    double max_x = INT_MIN;
    if(v.size()>3) {
        path.push_back(v[0]);
        path.push_back(v[1]);
        for(int i = 3; i < v.size(); i++) {
            if(isNotReflex(path[path.size()-2], path[path.size()-1], v[i])) {
                if(isNotReflex(path[path.size()-1],v[i], path[0])) {
                    if(isNotReflex(v[i], path[0], path[1])) {
                        path.push_back(v[i]);
                        v.erase(v.begin()+i-1);
                        min_x = min(min_x, v[i]->coordinates.first);
                        max_x = max(max_x, v[i]->coordinates.first);
                        min_y = min(min_y, v[i]->coordinates.second);
                        max_y = max(max_y, v[i]->coordinates.second);
                        
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            else {
                break;
            }
        }
        //Construct LPVS for the largest path
        vector<Vertex*> lpvs;
        if(path.size()==2) {
            for(int i = 1; i<v.size(); i++) {
                remaining.push_back(v[i]);
            }
            remaining.push_back(v[0]);
        }
        else if(path.size()!=n){
            
            //base case 1
            if(isNotReflex(v[v.size()-1], v[0], v[1])) {
                lpvs.push_back(v[0]);
            }
            for(int i = 1; i < v.size()-1; i++) {
                if(isNotReflex(v[i-1], v[i], v[i+1])) {
                    lpvs.push_back(v[i]);
                }            
            }
            //base case 2
            if(isNotReflex(v[v.size()-2], v[v.size()-1], v[0])) {
                lpvs.push_back(v[v.size()-1]);
            }
            //Check if any point inside LPVS is inside the polygon or not, if yes backtrack
            DCEL* tempDCEL = new DCEL();
            // bool back = false;
            tempDCEL->makeDCEL(path, interior, exterior);
            // int cur = 0;

            //Create a temporary vector notch which will initially contain entire lpvs
            
            vector<Vertex*> notch = lpvs;
            //If that point is not inside, remove it from notch
            while(!notch.empty()) {
                //Else, backtrack and restrore notch to lpvs
                notch = lpvs;
                int cur = 0;
                bool back = false;
                while(cur<lpvs.size() and !back) {
                    auto temp = lpvs[cur];
                    if(temp->coordinates.first>min_x && temp->coordinates.first<max_x && temp->coordinates.second>min_y && temp->coordinates.second<max_y) {
                        if(!checkInside(tempDCEL, temp)) {
                            path.pop_back();
                            tempDCEL->edges.pop_back();
                            tempDCEL->edges.pop_back();
                            tempDCEL->edges.push_back(addEdge(path[path.size()-1], path[0], path[0]->inc_edge->left, path[0]->inc_edge->twin->left));
                            back = true;
                        }
                        else {
                            notch.erase(notch.begin()+cur);
                        }
                    }
                    cur++;
                }
            } 
            finVector.push_back(tempDCEL);
            interior++;
            //Construct vector of points for remaining polygon
            int i = 0;
            // int k = 0;
            while(v[i]!=path[0]) {
                remaining.push_back(v[i]);
                i++;
            }
            remaining.push_back(path[0]);
            remaining.push_back(path[path.size()-1]);
            i++;
            while(i<v.size()) {
                remaining.push_back(v[i]);
                i++;
            }
        }
        
    }
    
    
    decomposeDCEL(remaining, interior, exterior); 
}
int main() {
    // freopen("input.txt", "r", stdin) ;
    // int n ; cin >> n ;
    // vector<Vertex*> v;
    // for(int i = 0 ; i < n ; i++)
    // {
    //     std::pair<double,double> p ;
    //     cin >> p ;
    //     int x , y ;
    //     x = p.first ; y = p.second ;
    //     Vertex *temp = new Vertex()
    // }

    vector<Vertex*> v;
    Vertex* v1 = new Vertex(0,0);
    Vertex* v2 = new Vertex(1,0);
    Vertex* v3 = new Vertex(1,1);
    Vertex* v4 = new Vertex(0,1);
    Vertex* v5 = new Vertex(-1,2);
    Vertex* v6 = new Vertex(-1,1);
    Vertex* v7 = new Vertex(-1,0);
    // Vertex* v8 = new Vertex(-0.5,-5);
    //cout<<"Bool"<<InLine(v7,v1,v2)<<endl;
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    v.push_back(v5);
    v.push_back(v6);
    v.push_back(v7);
    decomposeDCEL(v,1,0);
    for(auto temp:finVector) {
        temp->PrintDCEL();
    }

}