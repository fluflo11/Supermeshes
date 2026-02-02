#include "utils.hpp"
#include <cmath>
#include <vector>
#include <tuple>

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
    double y = std::get<1>(b) * std::get<1>(b);
    return x+y;
}

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
                }
            }
        }
        else {                        
            if (p2.y <= p.y) {     
                if (isLeft(p1, p2, p) < 0) {
                    wn--;
                }
            }
        }
    }
    return wn != 0;
}


bool inside(const Point2D& p1, const Point2D& p2, const Point2D& p){
    auto edge = Utils::substract(p1,p2);
    auto temp_edge = Utils::substract(p1,p);
    return (Utils::crossProduct(edge,temp_edge) >= 0);
}

Point2D computeIntersection(const Point2D& p1, const Point2D& p2, const Point2D& p3, const Point2D& p4){
    std::tuple<double,double> v12 = Utils::substract(p1,p2);
    std::tuple<double,double> v34 = Utils::substract(p3,p4);
    std::tuple<double,double> v13 = Utils::substract(p1,p3);

    double cp0 = Utils::crossProduct(v13,v12);
    double cp1 = Utils::crossProduct(v34,v12);

    //check parallel case
    if(std::abs(cp1) < Utils::THRESHOLD) return Point2D(-1,0,0);

    double t = cp0 / cp1;
    
    Point2D result(-1,
            (p3.x + t*(p4.x - p3.x)),
            (p3.y + t*(p4.y - p3.y))    
        );

    return result;
}

/**
 * 
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

    for(int i=0; i< poly2.size(); i++)
    {
        Point2D p1 = poly2[i];
        Point2D p2 = poly2[(i+1)%poly2.size()];
        
        std::vector<Point2D> inputlist = result;
        result.clear();

        if(inputlist.empty()){
            break;
        }

        Point2D starting_point = inputlist.back();

        for(Point2D ending_point: inputlist){
            bool is_inside_start = inside(p1,p2,starting_point);
            bool is_inside_end = inside(p1,p2,ending_point);

            if(is_inside_start && is_inside_end){
                result.push_back(ending_point);
            }
            else if(is_inside_start && (!is_inside_end) ){
                Point2D intersecting_point = computeIntersection(p1,p2,starting_point,ending_point);
                result.push_back(intersecting_point);
            }
            else if((!is_inside_start) && is_inside_end){
                Point2D intersecting_point = computeIntersection(p1,p2,starting_point,ending_point);
                result.push_back(intersecting_point);
            }

            starting_point = ending_point;
        }
    }
    return result;
}