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

struct CellTemp{
    int id;
    int boundary;
    int no_vertices;
};

class Cell{
public:
    int id;
    int boundary_id;
    std::vector<int> indices;
    Cell(int id_param, int boudary_id_param, std::vector<int> indices_param){
        id = id_param;
        boundary_id = boudary_id_param;
        indices = indices_param;
    }
    Cell(){
        id = -1;
        boundary_id = -1;
    }
};

class Topology{
public: 
    std::vector<Cell> cells;
    Topology(std::vector<Cell> cells_param){
        cells = cells_param;
    }
    static std::vector<Cell> getInputTopology(const std::string& file_path);
    void printTopology();
};


#endif