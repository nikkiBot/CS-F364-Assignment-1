/**
 * @file test.cpp
 * @brief Used as a preprocessor to convert the input file into a format that can be read by file:plotGraph.py
 * @author Nishith Kumar (2020A7PS0157H)
 * @author Anshul Kanodia (2020A7PS0174H)
 * @author Suvigya Sharma (2020A7PS0140H)
 * @author Vartika Gupta (2019A7PS0729H)
 * @version 3.0.1
 * 
 * 
 * @bug No known bugs
 */

#include <bits/stdc++.h>
using namespace std ;

int main() {
    ifstream fin;
    fin.open("./testcases/input4.txt");
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
        // cout << x << " " << y << endl;
        
        xstring+= to_string(x);
        xstring+=" ";
        ystring+= to_string(y);
        ystring+=" ";
    }

    double x,y;
    fin >> x >> y;
    // cout << x << " " << y << endl;
    
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