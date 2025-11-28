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

std::tuple<double,double> Utils::subtract(const Point2D& a, const Point2D& b){
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
                std::tuple<double,double> edge = Utils::subtract(p1, p2);
                std::tuple<double,double> toPoint = Utils::subtract(p1, p);
                if (Utils::crossProduct(edge, toPoint) > 0) { 
                    wn++;
                }
            }
        }
        else {                        
            if (p2.y <= p.y) {     
                std::tuple<double,double> edge = Utils::subtract(p1, p2);
                std::tuple<double,double> toPoint = Utils::subtract(p1, p);
                if (Utils::crossProduct(edge, toPoint) < 0) { 
                    wn--;
                }
            }
        }
    }
    return wn != 0;
}

/**
 * TODOOOO
 */
std::vector<Point2D> getPolygonIntersection(const std::vector<Point2D>& p1, const std::vector<Point2D>& p2){
    return std::vector<Point2D>{};
}