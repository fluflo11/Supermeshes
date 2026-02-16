#ifndef UTILS_HPP
#define UTILS_HPP
#include "structs.hpp"
#include <tuple>

//TODO : Comments 

/**
 * Just a toolbox with a lot of code borrowed and adapted from Numerical Recipes
 */

namespace Utils{

const double THRESHOLD = 1e-8;
/**
 * "If you wish to make an apple pie from scratch, you must first invent the universe"
 * TODO²
 */
double distance(const Point2D& a, const Point2D& b);
/**
 * Returns the vector between two points
 */
std::tuple<double,double> substract(const Point2D& a, const Point2D& b);
/**
 * 
 */
double norm(const std::tuple<double,double>& v);

/**
 * 
 */
double dotProduct(const std::tuple<double,double>& a, const std::tuple<double,double>& b);

/**
 * Cross product between two vectors of size 2
 */
double crossProduct(const std::tuple<double,double>& a, const std::tuple<double,double>& b);

/**
 * Stole this here : https://www.cnblogs.com/chriscai/archive/2009/12/10/1620932.html
 * I decided to use this method but I may just end up using raycasting
 */
bool winding(const Point2D& p, const std::vector<Point2D>& poly);

std::vector<Point2D> getPolygonIntersection(const std::vector<Point2D>& poly1, const std::vector<Point2D>& poly2);

double getPolygonArea(const std::vector<Point2D>& polygon);

/**
 * Convert a size a cell into a polygon
 */
std::vector<Point2D> getCellPolygon(const Cell& cell, const std::vector<Point2D>& nodes);

/**
 * 
 */
void computeSupermesh(const std::vector<std::vector<Point2D>>& polysA, 
                          const std::vector<AABB>& boxesA,
                          const std::vector<std::vector<Point2D>>& polysB, 
                          const std::vector<AABB>& boxesB,
                          Topology& result_topo,
                          std::vector<Point2D>& result_nodes,
                          bool debug = true);

}




#endif