#include <iostream>
#include <vector>
#include "structs.hpp"
#include "utils.hpp"

//GENERATED WITH COPILOT IM TIRED ITS 5AM ILL DO TRUE TESTS AFTER

// Petite fonction utilitaire pour afficher les résultats proprement
void runTest(const std::string& label, const Point2D& p, const std::vector<Point2D>& poly) {
    bool result = Utils::winding(p, poly);
    std::cout << "Test " << label << " (" << p.x << ", " << p.y << ") -> " 
              << (result ? "DEDANS [OK]" : "DEHORS [OK]") << std::endl;
}

int main() {
    // 1. Définition d'un Carré (0,0) à (10,10)
    // L'ordre des points est important (Sens anti-horaire ici : CCW)
    std::vector<Point2D> square;
    
    // Rappel constructeur Point2D(id, x, y). L'ID n'importe pas ici.
    square.emplace_back(1, 0.0, 0.0);   // Bas-Gauche
    square.emplace_back(2, 10.0, 0.0);  // Bas-Droite
    square.emplace_back(3, 10.0, 10.0); // Haut-Droite
    square.emplace_back(4, 0.0, 10.0);  // Haut-Gauche

    std::cout << "=== DEBUT DU TEST isPointInPolygon ===\n";
    std::cout << "Polygone : Carre (0,0) -> (10,10)\n\n";

    // CAS 1 : Point clairement à l'intérieur (5, 5)
    // On s'attend à TRUE
    Point2D p_in(10, 5.0, 5.0);
    runTest("Interieur", p_in, square);

    // CAS 2 : Point clairement à l'extérieur (15, 5)
    // On s'attend à FALSE
    Point2D p_out(11, 15.0, 5.0);
    runTest("Exterieur", p_out, square);

    // CAS 3 : Point sur un sommet (0, 0)
    // Avec la méthode Winding Number "Dan Sunday" (inégalités strictes/larges), 
    // les sommets "bas" ou "gauche" sont souvent inclus.
    Point2D p_vertex(12, 0.0, 0.0);
    runTest("Sommet (0,0)", p_vertex, square);

    // CAS 4 : Point complexe (concavité)
    // Créons un triangle "V" : (0,10) -> (5,0) -> (10,10) -> (0,10)
    std::vector<Point2D> triangleV;
    triangleV.emplace_back(1, 0.0, 10.0);
    triangleV.emplace_back(2, 5.0, 0.0);
    triangleV.emplace_back(3, 10.0, 10.0);

    std::cout << "\nTest Triangle en V :\n";
    // Point (5, 5) est DANS le V.
    // Point (5, 11) est DEHORS (au dessus).
    runTest("Dans le V (5,5)", Point2D(99, 5.0, 5.0), triangleV);
    
    return 0;
}