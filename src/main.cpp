#include <iostream>
#include <vector>
#include <chrono> // Pour chronométrer la performance
#include "structs.hpp"
#include "utils.hpp"
#include "VTK_Tools.hpp"


int main(int argc, char *argv[]) {

    /**
    if(argc != 3) {
        std::cerr << "Incorrect number of arguments" << std::endl << "Correct usage : supermesh [path_mesh_A] [path_mesh_B]";
        return 1;
    }

    std::string path_mesh_A = argv[1];
    std::string path_mesh_B = argv[2];
     */


    std::string path = "resources/meshes_for_FR/unitsqmeshes/unitsqmesh_hexreg_000094_midedge/";
    std::string pathB = "resources/meshes_for_FR/unitsqmeshes/unitsqmesh_hexreg_000449_flipped_nobd/"; 

    std::cout << "[1/4] Loading meshes..." << std::endl;
    
    // Mesh A
    auto nodesA = Point2D::getInputNodes(path + "input_nodes.dat");
    auto topoA  = Topology::getInputTopology(path + "input_topo.dat");
    std::cout << " -> Mesh A: " << topoA.cells.size() << " cells." << std::endl;

    // Mesh B
    auto nodesB = Point2D::getInputNodes(pathB + "input_nodes.dat");
    auto topoB  = Topology::getInputTopology(pathB + "input_topo.dat");
    std::cout << " -> Mesh B: " << topoB.cells.size() << " cells." << std::endl;


    std::cout << "[2/4] Pre-computing AABBs..." << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<Point2D>> polysA;
    std::vector<AABB> boxesA;
    polysA.reserve(topoA.cells.size());
    boxesA.reserve(topoA.cells.size());

    for (const auto& cell : topoA.cells) {
        auto poly = Utils::getCellPolygon(cell, nodesA);
        polysA.push_back(poly);
        boxesA.emplace_back(poly);
    }

    std::vector<std::vector<Point2D>> polysB;
    std::vector<AABB> boxesB;
    polysB.reserve(topoB.cells.size());
    boxesB.reserve(topoB.cells.size());

    for (const auto& cell : topoB.cells) {
        auto poly = Utils::getCellPolygon(cell, nodesB);
        polysB.push_back(poly);
        boxesB.emplace_back(poly);
    }

    std::cout << "[3/4] Computing Intersections (Broad Phase + Narrow Phase)..." << std::endl;

    Topology superTopo;
    std::vector<Point2D> superNodes; 
    
    long long checks_broad = 0;
    long long checks_narrow = 0;
    long long intersections_found = 0;

    for (size_t i = 0; i < polysA.size(); ++i) {
        for (size_t j = 0; j < polysB.size(); ++j) {
            
            //Filtering potential overlaps with AABB method

            if (!boxesA[i].intersects(boxesB[j])) {
                continue; 
            }
            checks_broad++;

            checks_narrow++;
            std::vector<Point2D> intersection = Utils::getPolygonIntersection(polysA[i], polysB[j]);

            if (intersection.size() < 3) continue;

            double area = Utils::getPolygonArea(intersection);

            if (area < 1e-12) continue; // Maybe use Utils::Threshold but i wanted to have a lower epsilon here

            intersections_found++;
            Cell newCell;
            newCell.id = intersections_found; //Just generating ids
            newCell.boundary_id = 0;

            for (const auto& p : intersection) {
                Point2D newPoint(p.x, p.y, superNodes.size() + 1);
                
                superNodes.push_back(newPoint);
                newCell.indices.push_back(superNodes.size() - 1);
            }
            
            superTopo.cells.push_back(newCell);
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;

    std::cout << "Done in " << duration.count() << " seconds." << std::endl;
    std::cout << "Stats:" << std::endl;
    std::cout << "  - Potential Pairs (AABB): " << checks_narrow << " (vs " << polysA.size() * polysB.size() << " total)" << std::endl;
    std::cout << "  - Real Intersections:     " << intersections_found << std::endl;
    
    std::cout << "[4/4] Exporting to VTK..." << std::endl;
    VTK::VTK_Exporter exporter(superTopo, superNodes);
    
    if(exporter.exportVTK("supermesh.vtk", "Supermesh Result")) {
        std::cout << "[SUCCESS] File 'supermesh.vtk' created." << std::endl;
    } else {
        std::cerr << "[ERROR] Export failed." << std::endl;
    }

    return 0;
}