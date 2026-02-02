#include <iostream>
#include <vector>
#include "utils.hpp"

//Tests automatically generated, not 

// Déclare la fonction (si elle n’est pas dans un header)
std::vector<Point2D> getPolygonIntersection(const std::vector<Point2D>& poly_1, const std::vector<Point2D>& poly_2);

int main() {

    std::vector<Point2D> poly_1 = {
        Point2D(0,0,0),
        Point2D(2,0,1),
        Point2D(2,2,3),
        Point2D(0,2,2)
        
    };

    std::vector<Point2D> poly_2 = {
        Point2D(1,1,4),
        Point2D(3,1,5),
        Point2D(3,3,6),
        Point2D(1,3,6)
    };


    std::cout << "=== Polygon 1 ===\n";
    for(const auto& p : poly_1)
        std::cout << "(" << p.x << ", " << p.y << ")\n";

    std::cout << "\n=== Polygon 2 ===\n";
    for(const auto& p : poly_2)
        std::cout << "(" << p.x << ", " << p.y << ")\n";

    // --- Calcul intersection ---
    std::vector<Point2D> inter = getPolygonIntersection(poly_1, poly_2);

    std::cout << "\n=== Intersection ===\n";

    if (inter.empty()) {
        std::cout << "Aucune intersection.\n";
    } else {
        for(const auto& p : inter)
            std::cout << "(" << p.x << ", " << p.y << ")\n";
    }

    

    return 0;
}
