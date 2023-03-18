#include <bits/stdc++.h>
using namespace std ;

int main() {
    ifstream fin;
    fin.open("snake.txt");
    //vector<Vertex*> v;
    int n;
    fin >> n;

    ofstream fout;
    fout.open("plotData.txt");
    
    string xstring="";
    string ystring="";
    double start, end;
    for(int i = 0; i<(n-1); i++) {
        double x,y;
        fin >> x >> y;
        if(i==0) {
            start = x;
            end = y;
        }
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
    xstring+=" ";
    ystring+= to_string(y);        
    ystring+=" ";

    xstring+= to_string(start);
    ystring+= to_string(end);

    fout<<xstring<<endl;
    fout<<ystring<<endl;    
    
    fout.close();
    return 0;
}