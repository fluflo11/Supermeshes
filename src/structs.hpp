#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#include <vector>
#include <string>
#include <limits>
#include <iostream>

class Point2D{
public :
    const double x;
    const double y;
    int id;
    Point2D(const double x_param, const double y_param, int id_param):x(x_param),y(y_param),id(id_param){}
    /**
     * Returns a list of all the nodes of an input_nodes.dat file. 
     */
    static std::vector<Point2D> getInputNodes(const std::string& file_path);
    static void printInputNodes(std::vector<Point2D> vect);
    // """bad"""
    Point2D & operator=(Point2D const&) { return *this;}
};

struct CellTemp{
    int id;
    int boundary;
    int no_vertices;
    int no_neighbors;
};

class Cell{
public:
    int id;
    int boundary_id;
    std::vector<int> indices;
    std::vector<int> neighbors_indices;
    Cell(int id_param, int boudary_id_param, std::vector<int> indices_param, std::vector<int> neighbors_indices_param){
        id = id_param;
        boundary_id = boudary_id_param;
        indices = indices_param;
        neighbors_indices = neighbors_indices_param;
    }
    Cell(){
        id = -1;
        boundary_id = -1;
    }
};

class Topology{
public: 
    std::vector<Cell> cells;
    std::vector<int> boundaries_idxs;
    Topology(std::vector<Cell> cells_param,std::vector<int> boundaries_idxs_param){
        cells = cells_param;
        boundaries_idxs = boundaries_idxs_param;
    }
    Topology(){}

    /**
     * Parse a input_topo.dat file into a Topology object
     */
    static Topology getInputTopology(const std::string& file_path);
    void printTopology();
    bool consistencyCheck(); //Like a vibecheck but with consistency 
};

/**
 * 
 */
class AABB {
public: 
    double x_min;
    double x_max;
    double y_min;
    double y_max;

    AABB() {
        double inf = std::numeric_limits<double>::max();
        x_min = inf;
        x_max = -inf;
        y_min = inf;
        y_max = -inf;
    }

    AABB(const std::vector<Point2D>& points) {
        double inf = std::numeric_limits<double>::max();
        x_min = inf;
        x_max = -inf;
        y_min = inf;
        y_max = -inf;

        for (const auto& p : points) {
            if (p.x < x_min) x_min = p.x;
            if (p.x > x_max) x_max = p.x;
            if (p.y < y_min) y_min = p.y;
            if (p.y > y_max) y_max = p.y;
        }
    }

    //check if two bounding boxes intersect with eachoter
    bool intersects(const AABB& other) const;

    void print() const;
};


#endif