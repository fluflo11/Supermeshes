#include <iostream>
#include <string>
#include "structs.hpp"

int main(){

    std::string input_file = "resources/meshes_for_FR/unitsqmeshes/unitsqmesh_hexreg_000094_midedge/input_nodes.dat";
    std::vector<Point2D> my_vector = Point2D::getInputNodes(input_file);
    Point2D::printInputNodes(my_vector);
   

    input_file = "resources/meshes_for_FR/unitsqmeshes/unitsqmesh_hexreg_000094_midedge/input_topo.dat";
    std::vector<Cell> my_cells = Topology::getInputTopology(input_file);
    Topology my_topology(my_cells);
    my_topology.printTopology();
    
    return 0;
}