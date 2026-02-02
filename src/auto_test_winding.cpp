#include <iostream>
#include <vector>
#include "structs.hpp"
#include "utils.hpp"

//GENERATED WITH COPILOT IM TIRED ITS 5AM ILL DO TRUE TESTS AFTER

// Petite fonction utilitaire pour afficher les résultats proprement
void runTest(const std::string& label, const Point2D& p, const std::vector<Point2D>& poly) {
    bool result = Utils::winding(p, poly);
    std::cout << "Test " << label << " (" << p.x << ", " << p.y << ") -> " 
              << (result ? "INSIDE" : "OUTSIDE") << std::endl;
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

        // ---------------------------------------------
    // POLYGONES PLUS COMPLEXES
    // ---------------------------------------------
    std::cout << "\n=== TESTS COMPLEXES ===\n";

    // 1. Polygone concave classique (forme de "U")
    std::vector<Point2D> polyU;
    polyU.emplace_back(1, 0, 0);
    polyU.emplace_back(2, 10, 0);
    polyU.emplace_back(3, 10, 10);
    polyU.emplace_back(4, 6, 10);
    polyU.emplace_back(5, 6, 4);
    polyU.emplace_back(6, 4, 4);
    polyU.emplace_back(7, 4, 10);
    polyU.emplace_back(8, 0, 10);

    std::cout << "\nPolygone en U (concave)\n";
    runTest("Dans le U", Point2D(50, 5, 2), polyU);
    runTest("Dans le trou du U", Point2D(51, 5, 7), polyU); // devrait être dehors
    runTest("Hors du U", Point2D(52, -1, 5), polyU);


    // 2. Polygone en étoile (concave fort)
    std::vector<Point2D> star;
    star.emplace_back(1, 0, 3);
    star.emplace_back(2, 4, 3);
    star.emplace_back(3, 5, 0);
    star.emplace_back(4, 6, 3);
    star.emplace_back(5, 10, 3);
    star.emplace_back(6, 7, 5);
    star.emplace_back(7, 8, 9);
    star.emplace_back(8, 5, 6);
    star.emplace_back(9, 2, 9);
    star.emplace_back(10, 3, 5);

    std::cout << "\nPolygone étoile (fortement concave)\n";
    runTest("Dans étoile", Point2D(60, 5, 4), star);
    runTest("Dehors étoile", Point2D(61, 5, -1), star);


    // 3. Polygone auto-croisé (bowtie) — NE DEVRAIT PAS ÊTRE VALIDE
    std::vector<Point2D> bowtie;
    bowtie.emplace_back(1, 0, 0);
    bowtie.emplace_back(2, 10, 10);
    bowtie.emplace_back(3, 0, 10);
    bowtie.emplace_back(4, 10, 0);

    std::cout << "\nPolygone auto-croisé (bowtie) — comportement dépend implementation\n";
    runTest("Centre (5,5)", Point2D(70, 5, 5), bowtie);
    runTest("Hors bowtie", Point2D(71, -1, 5), bowtie);

    // 4. Zigzag non convexe
    std::vector<Point2D> zigzag;
    zigzag.emplace_back(1, 0, 0);
    zigzag.emplace_back(2, 5, 2);
    zigzag.emplace_back(3, 0, 4);
    zigzag.emplace_back(4, 5, 6);
    zigzag.emplace_back(5, 0, 8);
    zigzag.emplace_back(6, 10, 8);
    zigzag.emplace_back(7, 10, 0);

    std::cout << "\nPolygone Zigzag (non convexe irrégulier)\n";
    runTest("Dans zigzag", Point2D(80, 3, 3), zigzag);
    runTest("Dehors zigzag", Point2D(81, 11, 4), zigzag);


    // 5. Cas limite : point sur une arête
    std::cout << "\nCas limite — Point sur une arête du carré\n";
    runTest("Sur arête", Point2D(90, 5, 0), square); // Bas du carré

    // 6. Cas limite : point très proche d'une arête
    std::cout << "\nCas limite — Point juste en dehors\n";
    runTest("Juste dehors", Point2D(91, 5, -0.0001), square);

    
    return 0;
}