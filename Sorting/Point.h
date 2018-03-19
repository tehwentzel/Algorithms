#ifndef POINT_H
#define POINT_H
#include <math.h>
#include <vector>
#include <tuple>


class Point
{
    public:
        double X;
        double Y;

        Point(double x, double y){
            X = x;
            Y = y;
        };

        bool operator()(Point &one, const Point &two){
            double slope1 = slopeTo(one);
            double slope2 = slopeTo(two);
            bool result = (slope1 < slope2);
            return(result);
        }

        bool operator()(Point &one, Point &two){
            double slope1 = slopeTo(one);
            double slope2 = slopeTo(two);
            bool result = (slope1 < slope2);
            return(result);
        }

        bool operator()(const Point &one, Point &two){
            double slope1 = slopeTo(one);
            double slope2 = slopeTo(two);
            bool result = (slope1 < slope2);
            return(result);
        }

        bool operator<(Point p2) const{
            //returns true if this point is less than p2
            if(Y < p2.Y || (Y==p2.Y && X < p2.X)){
                return(true);
            }
            return false;
        }

        friend std::ostream &operator<<( std::ostream &output, const Point &p){
            output << "(" << p.X << "," << p.Y << ")";
            return(output);
        }

        double slopeTo(Point p2){
            double slope = ((Y - p2.Y)/(X - p2.X));
            return slope;
        }

        virtual ~Point(){};

    protected:

    private:
};



class BruteForce
{
    std::vector<std::tuple<Point, Point, Point, Point> > lines;
public:
    int numlines= 0;
    BruteForce(std::vector<Point> points){
        std::vector<std::tuple<Point, Point> > segments;

        for(int k0 = 0; k0 != points.size(); k0++){
            Point p0 = points[k0];

            for(int k1 = k0+1; k1 != points.size(); k1++){
                Point p1 = points[k1];
                auto slope1 = p0.slopeTo(p1);

                for(int k2 = k1+1; k2 != points.size(); k2++){
                    Point p2 = points[k2];
                    auto slope2 = p0.slopeTo(p2);
                    if(slope2 != slope1){ continue; }

                    for(int k3 = k2+1; k3 != points.size(); k3++){
                        Point p3 = points[k3];
                        auto slope3 = p0.slopeTo(p3);
                        if( slope3 != slope1){ continue; }
                        auto seg = std::make_tuple(p0, p1, p2, p3);
                        numlines++;
                        lines.push_back(seg);
                    }
                }
            }
        }

        for(auto tuppy: lines){
            std::cout << std::get<0>(tuppy) << " " << std::get<1>(tuppy) << " " << std::get<2>(tuppy) << " " << std::get<3>(tuppy) << std::endl;
        }
        std::cout << numlines << std::endl;
    }
};

#endif // POINT_H
