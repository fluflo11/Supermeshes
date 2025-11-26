#include "structs.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <stdexcept>

/**
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Point2D
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

/**
 * Parse a regex of the form [0-9]*\.[0-9]+E[+-][0-9]+ without using slow ahh regex
 * Generated with chatgpt, maybe need to correct it
 */
double parseScientificNotation(const std::string& s) {
    size_t ePos = s.find('E');
    if (ePos == std::string::npos)
        throw std::invalid_argument("Missing 'E'");

    std::string mantissaStr = s.substr(0, ePos);
    std::string exponentStr = s.substr(ePos + 1);

    double mantissa = std::stod(mantissaStr);
    int exponent = std::stoi(exponentStr);

    return mantissa * std::pow(10.0, exponent);
}

/**
 * Returns a list of all the nodes of an input_nodes.dat file. 
 */
std::vector<Point2D> Point2D::getInputNodes(const std::string& file_path){
    std::ifstream in(file_path);
    if(!in) std::cerr << file_path << " was not found";

    std::string line;
    std::string n_points_string;
    std::getline(in,n_points_string);
    std::vector<Point2D> result;
    int id = 0;

    while(std::getline(in,line)){
        std::istringstream iss(line);
        std::string a,b;
        if(iss>>a>>b){
            double a_parsed = parseScientificNotation(a);
            double b_parsed = parseScientificNotation(b);
            id++;
            Point2D new_point{a_parsed,b_parsed,id};
            result.push_back(new_point);
            
        }
    }
    return result;
}

void Point2D::printInputNodes(std::vector<Point2D> vect){
    for(Point2D point: vect){
        std::cout << point.x << " " << point.y << " " << point.id <<"\n";
    }
}

/**
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Topology
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------
 */

void ignoreLine(std::ifstream& in) {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/**
 * Parse a input_topo.dat file into a Topology object
 */
std::vector<Cell> Topology::getInputTopology(const std::string& file_path){
    std::ifstream in(file_path);
    if(!in) std::cerr << file_path << " was not found";

    std::vector<Cell> result;

    int no_cells, no_nodes, max_neighbors;

    in >> no_cells >> no_nodes >> max_neighbors;
    std::string trashbin = "";
    ignoreLine(in); //| nc, nn, ncnmax
    ignoreLine(in); // Nodes: ID, ID of boundary, no. of neighboring nodes, no. of attached cells

    /**
     * Jumping all lines that we dont need to use now
     */
    int id, boundary, no_neighboring_nodes, no_attached_cells;
    for(int i=0; i<no_nodes; i++){
        in >> id >> boundary >> no_neighboring_nodes >> no_attached_cells;
        ignoreLine(in);
    }
    ignoreLine(in);//Node-node and node-cell connectivity
    for(int i=0; i<no_nodes; i++){
        ignoreLine(in);
    }
    ignoreLine(in); // Cells: ID, ID of boundary, no. of vertices, no. of neighboring cells

    /**
     * Storing cells and producing result
     */
    std::vector<CellTemp> temp_cells;

    for(int i=0;i<no_cells; i++){
        int id, boundary, no_vertices, no_neighbors;
        in >> id >> boundary >> no_vertices >> no_neighbors;
        temp_cells.push_back({id,boundary,no_vertices});
        ignoreLine(in);
    }
    ignoreLine(in); //Cell-node and cell-cell connectivity

    for(int i=0; i<no_cells; i++){
        Cell new_cell;
        new_cell.id = temp_cells[i].id;
        new_cell.boundary_id = temp_cells[i].boundary;

        int no_vertices = temp_cells[i].no_vertices;
        int read_id;
        in >> read_id; 

        for(int j = 0; j<no_vertices; j++){
            int node_id;
            in >> node_id;
            new_cell.indices.push_back(node_id - 1); //"All IDs and lists start with 1 (Fortran-style, not C, sorry...)" :(
        }

        ignoreLine(in);
        result.push_back(new_cell);
    }

    //IDK what to do with "48  | number and list of boundary nodes" so I stop here, but it should be enough
    //TODO : ask professor why is there always an int before the "numberand list of boundary nodes"

    return result;
}

void Topology::printTopology(){
    if(!cells.empty()){
        for(Cell cell: cells){
            std::cout << cell.id << " " << cell.boundary_id << "\n" << 
            "indices : (size ="  << cell.indices.size() << ")" << "\n";
            for(int i: cell.indices){
                std::cout << i << " ";
            }
            std::cout << "\n";
        }
    }
}