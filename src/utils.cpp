#include "utils.hpp"
#include <cmath>
#include <vector>
#include <tuple>
#include <iostream>
#include <math.h>

double Utils::distance(const Point2D& a, const Point2D& b){
    double dd = 0.0;
    dd += (b.x - a.x)*(b.x - a.x);
    dd += (b.y - a.y)*(b.y - a.y);
    return std::sqrt(dd);
}

std::tuple<double,double> Utils::substract(const Point2D& a, const Point2D& b){
    double x = (b.x - a.x);
    double y = (b.y - a.y);
    std::tuple<double,double> result(x,y);
    return result;
}

double Utils::norm(const std::tuple<double,double>& v){
    return std::hypot(std::get<0>(v),std::get<1>(v));
}

double Utils::dotProduct(const std::tuple<double,double>& a, const std::tuple<double,double>& b){
    double x = std::get<0>(a) * std::get<0>(b);
    double y = std::get<1>(a) * std::get<1>(b);
    return x+y;
}

/**
 * Maybe use this function idk 
 */
double Utils::crossProduct(const std::tuple<double,double>& a, const std::tuple<double,double>& b){
    double ax = std::get<0>(a);
    double ay = std::get<1>(a);
    double bx = std::get<0>(b);
    double by = std::get<1>(b);
    return ax * by - ay * bx;
}

inline double isLeft(const Point2D& P1, const Point2D& P2, const Point2D& P) {
    return (P2.x - P1.x) * (P.y - P1.y) - (P.x - P1.x) * (P2.y - P1.y);
}
/**
 * Still need to test it
 */
bool Utils::winding(const Point2D& p, const std::vector<Point2D>& poly) {
    int wn = 0;
    size_t n = poly.size();
    for (size_t i = 0; i < n; ++i) {
        const Point2D& p1 = poly[i];
        const Point2D& p2 = poly[(i + 1) % n];
        if (p1.y <= p.y) {          
            if (p2.y > p.y) {      
                if (isLeft(p1, p2, p) > 0) {
                    wn++;
                    std::cout << "CASE 1 : P1.y <= P.y and P2.y > P.y and isLeft" << std::endl;
                }
                else {
                    std::cout << "CASE 2 : P1.y <= P.y and P2.y > P.y and NOT isLeft" << std::endl;
                }
            }
            else {
                std::cout << "CASE 3 : P1.y <= P.y and P2.y <= P.y" << std::endl;
            }
        }
        else {                        
            if (p2.y <= p.y) {     
                if (isLeft(p1, p2, p) < 0) {
                    wn--;
                    std::cout << "CASE 4 : P2.y <= P.y and isLeft" << std::endl;
                }
                else {
                    std::cout << "CASE 5 : P2.y <= P.y and NOT isLeft" << std::endl;
                }
            }
            else {
                std::cout << "CASE 6 : P1.y > P.y and P2.y > P.y " << std::endl;
            }
        }
        
    }
    (wn != 0) ? (std::cout << "inside" << std::endl):(std::cout << "outside" << std::endl);
    return wn != 0;
}


bool inside(const Point2D& p1, const Point2D& p2, const Point2D& p){
    return ((p2.x - p1.x)*(p.y - p1.y) - (p2.y - p1.y) * (p.x - p1.x))>=Utils::THRESHOLD;
}

/**
 *  Original function (I just adapted the parameters) : https://www.geeksforgeeks.org/dsa/polygon-clipping-sutherland-hodgman-algorithm/
 */
Point2D computeIntersection(const Point2D& p1, const Point2D& p2, const Point2D& p3, const Point2D& p4){
    double x1 = p1.x, y1 = p1.y;
    double x2 = p2.x, y2 = p2.y;
    double x3 = p3.x, y3 = p3.y;
    double x4 = p4.x, y4 = p4.y;

    double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    
    if (std::abs(den) < Utils::THRESHOLD) return Point2D(x3, y3, -1);

    double num_x = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4);
    double num_y = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4);

    return Point2D(num_x / den, num_y / den, -1);
}

/**
 * TODO : Debugging
 * Wikipedia code : https://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm
 * I also used the variables names of the geeks4geeks implementation to make it easier to read (my variable names were bad translations from french)
 * List outputList = subjectPolygon;  

for (Edge clipEdge in clipPolygon) do
    List inputList = outputList;
    outputList.clear();

    for (int i = 0; i < inputList.count; i += 1) do
        Point current_point = inputList[i];
        Point prev_point = inputList[(i − 1) % inputList.count];

        Point Intersecting_point = ComputeIntersection(prev_point, current_point, clipEdge)

        if (current_point inside clipEdge) then
            if (prev_point not inside clipEdge) then
                outputList.add(Intersecting_point);
            end if
            outputList.add(current_point);

        else if (prev_point inside clipEdge) then
            outputList.add(Intersecting_point);
        end if

    done
done
 */
std::vector<Point2D> getPolygonIntersection(const std::vector<Point2D>& poly1, const std::vector<Point2D>& poly2){
    std::vector<Point2D> result = poly1;

    for (size_t i = 0; i < poly2.size(); i++) {
        size_t k_clip = (i + 1) % poly2.size();
        Point2D p1 = poly2[i];
        Point2D p2 = poly2[k_clip];

        std::vector<Point2D> inputlist = result;
        result.clear();

        for (size_t j = 0; j < inputlist.size(); j++) {
            size_t k_poly = (j + 1) % inputlist.size();
            Point2D starting_point = inputlist[j]; // ix, iy
            Point2D ending_point = inputlist[k_poly]; // kx, ky

            //(x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1)
            double i_pos = (p2.x - p1.x) * (starting_point.y - p1.y) - (p2.y - p1.y) * (starting_point.x - p1.x);
            double k_pos = (p2.x - p1.x) * (ending_point.y - p1.y) - (p2.y - p1.y) * (ending_point.x - p1.x);

            if (i_pos > 0 && k_pos > 0) {
                result.push_back(ending_point);
            }

            else if (i_pos <= 0 && k_pos > 0) {
                result.push_back(computeIntersection(p1, p2, starting_point, ending_point));
                result.push_back(ending_point);
            }

            else if (i_pos > 0 && k_pos <= 0) {
                result.push_back(computeIntersection(p1, p2, starting_point, ending_point));
            }
        }
        if (result.empty()) break;
    }

    return result;
}