#include <bits/stdc++.h>
using namespace std ;

int main() {
    ifstream fin;
    fin.open("india.txt");
    //vector<Vertex*> v;
    int n;
    fin >> n;

    ofstream fout;
    fout.open("plotData.txt");
    
    string xstring="";
    string ystring="";

    for(int i = 0; i<(n-1); i++) {
        double x,y;
        fin >> x >> y;
        cout << x << " " << y << endl;
        
        xstring+= to_string(x);
        xstring+=" ";
        ystring+= to_string(y);
        ystring+=" ";
    }

    double x,y;
    fin >> x >> y;
    cout << x << " " << y << endl;
    
    xstring+= to_string(x);
    ystring+= to_string(y);        
    
    fout<<xstring<<endl;
    fout<<ystring<<endl;    
    
    fout.close();
    return 0;
}