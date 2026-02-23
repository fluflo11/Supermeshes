#include <iostream>
#include <vector>
#include <chrono>
#include <filesystem>
#include "structs.hpp"
#include "utils.hpp"
#include "VTK_Tools.hpp"

int main(int argc, char *argv[]) {

    //checking if number of arguments is valid
    if(argc < 5 || argc > 7) {
        std::cerr << "Incorrect number of arguments" << std::endl << 
                    "Correct usage : supermesh {path_input_nodes_A} {path_input_topo_A}" << 
                    " {path_input_nodes_B} {path_input_topo_B} " << 
                    "[output_path] [-d|--debug]";
        return 1;
    }

    std::string path_input_nodes_A = argv[1];
    std::string path_input_topo_A = argv[2];
    std::string path_input_nodes_B = argv[3];
    std::string path_input_topo_B = argv[4];

    //Checking if all paths are valid or not
    if (!std::filesystem::exists(path_input_nodes_A)){
        std::cerr << "Path " << path_input_nodes_A << " is not valid" << std::endl;
        return 1;
    }
    if (!std::filesystem::exists(path_input_nodes_B)){
        std::cerr << "Path " << path_input_nodes_B << " is not valid" << std::endl;
        return 1;
    }
    if(!std::filesystem::exists(path_input_topo_A)){
        std::cerr << "Path " << path_input_topo_A << " is not valid" << std::endl;
        return 1;
    }
    if(!std::filesystem::exists(path_input_topo_B)){
        std::cerr << "Path " << path_input_topo_B << " is not valid" << std::endl;
        return 1;
    }
    
    auto nodesA = Point2D::getInputNodes(path_input_nodes_A);
    auto topoA = Topology::getInputTopology(path_input_topo_A);
    auto nodesB = Point2D::getInputNodes(path_input_nodes_B);
    auto topoB = Topology::getInputTopology(path_input_topo_B);

    std::string output_path = "supermesh.vtk";
    std::string label = "Supermesh Result";

    bool has_output_path = false;

    if(argc>=6) { //Here I manage arguments manually but ill try to use cxxopts later
        std::string arg = argv[5];
        if(arg!="-d"){
            output_path = arg;
            has_output_path = true;
        }
    }

    bool debug = false;

    if((argc == 6 && !has_output_path) || argc == 7){
        std::string arg = argv[argc-1];
        if(arg=="-d" || arg == "--debug") debug = true;
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

    Utils::precomputesPolysAndAABBs(topoA,nodesA,polygons_A,boxes_A);

    std::vector<std::vector<Point2D>> polygons_B;
    std::vector<AABB> boxes_B;

    Utils::precomputesPolysAndAABBs(topoB,nodesB,polygons_B,boxes_B);

    
    // Intersections part

    Topology result_topo;
    std::vector<Point2D> result_nodes; 
    
    Utils::computeSupermesh(polygons_A, boxes_A, polygons_B, boxes_B, result_topo, result_nodes, debug);

    //performance measure for debug
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;
    //Exporting the final result as a vtk file
    VTK::VTK_Exporter exporter(result_topo, result_nodes);
    
    bool write_success = exporter.exportVTK(output_path, "Supermesh Result");

    if(debug){
        if(write_success) {
            std::cout << "[SUCCESS] File 'supermesh.vtk' created." << std::endl;
        } else {
            std::cerr << "[ERROR] Export failed." << std::endl;
        }
        std::cout << "Done in " << duration.count() << " seconds." << std::endl;
        
        std::cout << "Exporting to VTK" << std::endl;
    }
    
    return 0;
}