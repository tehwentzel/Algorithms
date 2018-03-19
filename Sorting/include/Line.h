#ifndef LINE_H
#define LINE_H
#include <vector>
#include "Point.h"
#include <iostream>

class Line{
    public:
        double slope;
        double intercept;
        int numpoints = 0;
        std::vector<Point> points;
        Line(){};

        Line( Point p ){
            numpoints = 1;
            points.push_back(p);
        };

        Line( Point p1, Point p2){
            slope = p1.slopeTo(p2);
            intercept = p1.Y - (slope * p1.X);
            numpoints = 2;
            points.push_back(p1);
            points.push_back(p2);
        };

        virtual ~Line(){};

        double setLine(){
            if(points.size() < 2){ throw("you need two points to define a line"); }
            auto p1 = points[0];
            auto p2 = points[1];
            slope = p1.slopeTo(p2);
            intercept = p1.Y - (slope * p1.X);
        }

        void addpoint(Point p){
            points.push_back(p);
        }

        bool operator==( const Line l2) const{
            return( slope == l2.slope && intercept == l2.intercept);
        }

        bool operator<(Line l)const{
            return( slope < l.slope);
        }

        friend std::ostream &operator<<( std::ostream &output, const Line &l){
            for(auto p: l.points)
            {
                output << p << " ";
            }
            return(output);
        }
};

#endif // LINE_H
