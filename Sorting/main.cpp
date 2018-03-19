#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include "Point.h"
#include "Line.h"

namespace std{
    template<>
    struct hash<Point>
    {
        std::size_t operator()(const Point& p) const
        {
            using std::size_t;
            using std::hash;
            return(hash<double>()(p.X)^hash<double>()(p.Y));
        }
    };
}

namespace std{
    template<>
    struct hash<Line>
    {
        std::size_t operator()(const Line& l) const
        {
            using std::size_t;
            using std::hash;
            return(hash<double>()(l.slope)^hash<double>()(l.intercept));
        }
    };
}

using namespace std;

int main()
{
    fstream file;
    vector<Point> points;
    file.open("test.txt");
    int numpoints;
    file >> numpoints;
    double p1;
    double p2;
    for(int k = 0; k != numpoints; k++){
        file >> p1;
        file >> p2;
        Point thepoint(p1,p2);
        points.push_back(thepoint);
    }
    BruteForce test(points);
    unordered_set<Line > lines;
    int numlines = 0;
    sort(points.begin(),points.end());
    for(int k = 0; k != points.size(); k++){
        auto p = points[k];
        stable_sort(points.begin()+k,points.end(),p);
        for(auto it = points.begin()+k; it != points.end(); ++it){
            if(p.slopeTo(*it) == p.slopeTo(*(it+2))){
                Line l(p, (*it));
                while(p.slopeTo(*it) == p.slopeTo(*(it+1))){
                    l.addpoint(*(it+1));
                    it++;
                }
                lines.insert(l);
            }
        }
    }
    cout << "Sorted point sets (minimal): " << std::endl;
    for(auto seg: lines){
            cout << seg << endl;
        }
}
