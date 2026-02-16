#include <iostream>
#include <vector>
#include <chrono>
#include <filesystem>
#include "structs.hpp"
#include "utils.hpp"
#include "VTK_Tools.hpp"

int main(int argc, char *argv[]) {
    //checking if number of arguments is valid
    if(argc < 5 || argc > 6) {
        std::cerr << "Incorrect number of arguments" << std::endl << 
                    "Correct usage : supermesh {path_input_nodes_A} {path_input_topo_A}" << 
                    " {path_input_nodes_B} {path_input_topo_B} [-d]";
        return 1;
    }

    std::string path_input_nodes_A = argv[1];
    std::string path_input_topo_A = argv[2];
    std::string path_input_nodes_B = argv[3];
    std::string path_input_topo_B = argv[4];

    //Checking if all paths are valid or not
    if (!std::filesystem::exists(path_input_nodes_A)){
        std::cerr << "Path " << path_input_nodes_A << " is not valid" << std::endl;
    }
    if (!std::filesystem::exists(path_input_nodes_B)){
        std::cerr << "Path " << path_input_nodes_B << " is not valid" << std::endl;
    }
    if(!std::filesystem::exists(path_input_topo_A)){
        std::cerr << "Path " << path_input_topo_A << " is not valid" << std::endl;
    }
    if(!std::filesystem::exists(path_input_topo_B)){
        std::cerr << "Path " << path_input_topo_B << " is not valid" << std::endl;
    }
    
    auto nodesA = Point2D::getInputNodes(path_input_nodes_A);
    auto topoA = Topology::getInputTopology(path_input_topo_A);
    auto nodesB = Point2D::getInputNodes(path_input_nodes_B);
    auto topoB = Topology::getInputTopology(path_input_topo_B);

    bool debug = false;
    if(argc == 6){
        std::string arg = argv[5];
        if(arg=="-d") debug = true;
    }

    if(debug){
        std::cout << " -> Mesh A: " << topoA.cells.size() << " cells." << std::endl;
        std::cout << " -> Mesh B: " << topoB.cells.size() << " cells." << std::endl;
    }


    //Here I measure time but its only to get a small idea of how good this is performance wise
    auto start_time = std::chrono::high_resolution_clock::now();

    //AABB pre-computing

    std::vector<std::vector<Point2D>> polygons_A;
    std::vector<AABB> boxes_A;

    polygons_A.reserve(topoA.cells.size());
    boxes_A.reserve(topoA.cells.size());

    //For each cell we convert it to a vector of points and we store it as a polygon
    for (const auto& cell : topoA.cells) {
        auto poly = Utils::getCellPolygon(cell, nodesA);
        polygons_A.push_back(poly);
        boxes_A.emplace_back(poly);
    }

    std::vector<std::vector<Point2D>> polygons_B;
    std::vector<AABB> boxes_B;
    polygons_B.reserve(topoB.cells.size());
    boxes_B.reserve(topoB.cells.size());

    for (const auto& cell : topoB.cells) {
        auto poly = Utils::getCellPolygon(cell, nodesB);
        polygons_B.push_back(poly);
        boxes_B.emplace_back(poly);
    }

    // Intersections part

    Topology result_topo;
    std::vector<Point2D> result_nodes; 
    
    Utils::computeSupermesh(polygons_A, boxes_A, polygons_B, boxes_B, result_topo, result_nodes, true);
    
    if(debug){
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;

        std::cout << "Done in " << duration.count() << " seconds." << std::endl;
        
        std::cout << "Exporting to VTK" << std::endl;

        VTK::VTK_Exporter exporter(result_topo, result_nodes);
        
        if(exporter.exportVTK("supermesh.vtk", "Supermesh Result")) {
            std::cout << "[SUCCESS] File 'supermesh.vtk' created." << std::endl;
        } else {
            std::cerr << "[ERROR] Export failed." << std::endl;
        }
    }
    return 0;
}