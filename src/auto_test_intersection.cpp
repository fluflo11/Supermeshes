#include <iostream>
#include <vector>
#include "utils.hpp"

//Tests automatically generated, not 

// Déclare la fonction (si elle n’est pas dans un header)
std::vector<Point2D> getPolygonIntersection(const std::vector<Point2D>& poly1, const std::vector<Point2D>& poly2);

int main() {

    // --- POLYGONE 1 : carré ---
    std::vector<Point2D> poly1 = {
        Point2D(0,0,0),
        Point2D(0,4,0),
        Point2D(0,4,4),
        Point2D(0,0,4)
    };

    // --- POLYGONE 2 : carré décalé ---
    std::vector<Point2D> poly2 = {
        Point2D(0,2,2),
        Point2D(0,6,2),
        Point2D(0,6,6),
        Point2D(0,2,6)
    };

    std::cout << "=== Polygon 1 ===\n";
    for(const auto& p : poly1)
        std::cout << "(" << p.x << ", " << p.y << ")\n";

    std::cout << "\n=== Polygon 2 ===\n";
    for(const auto& p : poly2)
        std::cout << "(" << p.x << ", " << p.y << ")\n";

    // --- Calcul intersection ---
    std::vector<Point2D> inter = getPolygonIntersection(poly1, poly2);

    std::cout << "\n=== Intersection ===\n";

    if (inter.empty()) {
        std::cout << "Aucune intersection.\n";
    } else {
        for(const auto& p : inter)
            std::cout << "(" << p.x << ", " << p.y << ")\n";
    }

    

    return 0;
}
