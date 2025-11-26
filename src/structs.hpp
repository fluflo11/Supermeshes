#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#include <vector>
#include <string>

class Point2D{
public :
    double x;
    double y;
    int id;
    Point2D(double x_param, double y_param, int id_param){
        x = x_param;
        y = y_param;
        id = id_param;
    }
    static std::vector<Point2D> getInputNodes(const std::string& file_path);
    static void printInputNodes(std::vector<Point2D> vect);
};
/** 
class Cell{
public:
    int id;
    int boundary_id;
    std::vector<int> indices;
};

class Topology{
public: 
    std::vector<Cell> cells;
    static Topology getInputTopology(const std::string& file_path);
    void printTopology();
};
*/
#endif