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

Point2D computeIntersection(const Point2D& p1, const Point2D& p2, const Point2D& p3, const Point2D& p4){
    // Direction du segment du sujet : p4 - p3
    double dx43 = p4.x - p3.x;
    double dy43 = p4.y - p3.y;
    
    // Direction de l'arête de découpe : p2 - p1
    double dx21 = p2.x - p1.x;
    double dy21 = p2.y - p1.y;

    // Dénominateur : produit vectoriel des directions
    double den = (dx43 * dy21) - (dy43 * dx21);

    if (std::abs(den) < 1e-9) return Point2D(p3.x, p3.y, -1);

    // Numérateur : (p1 - p3) x direction_découpe
    double num = ((p1.x - p3.x) * dy21) - ((p1.y - p3.y) * dx21);
    
    double t = num / den;

    Point2D result(
        p3.x + t * dx43,
        p3.y + t * dy43,
        -1
    );
    return result;
}

/**
 * TODO : Debugging
 * Wikipedia code : https://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm
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
    std::vector<Point2D> inputlist = result;

    for(int i=0; i < poly2.size(); i++)
    {   
        std::cout << "MAIN FOR LOOP : " << i << std::endl;
        Point2D p1 = poly2[i];
        Point2D p2 = poly2[(i+1)%poly2.size()];
        std::cout << "P1 = " << p1.x << "," << p1.y <<std::endl;
        std::cout << "P2 = " << p2.x << "," << p2.y <<std::endl;
        
        result.clear();

        if(inputlist.empty()){
            std::cout << "inputlist is empty, BREAK"  << std::endl;
            break;
        }

        for(int i=0; i < inputlist.size(); i++){
            Point2D starting_point = inputlist[i];
            Point2D ending_point = inputlist[(i+1)%inputlist.size()];
            
            bool is_inside_start = inside(p1,p2,starting_point);
            bool is_inside_end = inside(p1,p2,ending_point);

            if(is_inside_start && is_inside_end){
                result.push_back(ending_point);
                std::cout << "CASE 1: Entirely inside" << std::endl;
            }
            else if(is_inside_start && (!is_inside_end) ){
                Point2D intersecting_point = computeIntersection(p1,p2,starting_point,ending_point);
                result.push_back(intersecting_point);
                std::cout << "CASE 2 : Intersection (Exit)" << std::endl;
            }
            else if((!is_inside_start) && is_inside_end){
                Point2D intersecting_point = computeIntersection(p1,p2,starting_point,ending_point);
                result.push_back(intersecting_point);
                result.push_back(ending_point);
                std::cout << "CASE 3 : Intersection (Entry)"  << std::endl;
            }
            else
            {
                std::cout << "CASE 4: Entirely outside" << std::endl;
            }
        }
        inputlist = result;
    }
    return result;
}