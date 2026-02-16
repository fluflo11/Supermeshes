#ifndef STRUCTS_HPP
#define STRUCTS_HPP
#include <vector>
#include <string>
#include <limits>
#include <iostream>

class Point2D{
public :
    const double x;
    const double y;
    int id;
    Point2D(const double x_param, const double y_param, int id_param):x(x_param),y(y_param),id(id_param){}
    /**
     * Returns a list of all the nodes of an input_nodes.dat file. 
     */
    static std::vector<Point2D> getInputNodes(const std::string& file_path);
    static void printInputNodes(std::vector<Point2D> vect);
    // """bad"""
    Point2D & operator=(Point2D const&) { return *this;}
};

struct CellTemp{
    int id;
    int boundary;
    int no_vertices;
    int no_neighbors;
};

class Cell{
public:
    int id;
    int boundary_id;
    std::vector<int> indices;
    std::vector<int> neighbors_indices;
    Cell(int id_param, int boudary_id_param, std::vector<int> indices_param, std::vector<int> neighbors_indices_param){
        id = id_param;
        boundary_id = boudary_id_param;
        indices = indices_param;
        neighbors_indices = neighbors_indices_param;
    }
    Cell(){
        id = -1;
        boundary_id = -1;
    }
};

class Topology{
public: 
    std::vector<Cell> cells;
    std::vector<int> boundaries_idxs;
    Topology(std::vector<Cell> cells_param,std::vector<int> boundaries_idxs_param){
        cells = cells_param;
        boundaries_idxs = boundaries_idxs_param;
    }
    Topology(){}

    /**
     * Parse a input_topo.dat file into a Topology object
     */
    static Topology getInputTopology(const std::string& file_path);
    void printTopology();
    bool consistencyCheck(); //Like a vibecheck but with consistency 
};

//TODO : implémenter cette merde dans structs.cpp
class AABB {
public: 
    // TOUT EST PUBLIC : Accès direct (box.x_min)
    double x_min;
    double x_max;
    double y_min;
    double y_max;

    // Constructeur par défaut : Crée une boîte "invalide" (inversée)
    // Ainsi, le premier point ajouté va forcément initialiser les bornes correctement.
    AABB() {
        double inf = std::numeric_limits<double>::max();
        x_min = inf;
        x_max = -inf;
        y_min = inf;
        y_max = -inf;
    }

    // Constructeur principal : Calcule la boîte englobante d'un polygone
    AABB(const std::vector<Point2D>& points) {
        // On initialise avec les valeurs extrêmes inverses
        double inf = std::numeric_limits<double>::max();
        x_min = inf;
        x_max = -inf;
        y_min = inf;
        y_max = -inf;

        // On parcourt tous les points pour trouver les min/max
        for (const auto& p : points) {
            if (p.x < x_min) x_min = p.x;
            if (p.x > x_max) x_max = p.x;
            if (p.y < y_min) y_min = p.y;
            if (p.y > y_max) y_max = p.y;
        }
    }

    // Fonction d'intersection simple (AABB vs AABB)
    // Retourne vrai si les deux boîtes se touchent ou se chevauchent
    bool intersects(const AABB& other) const {
        // Si l'une est complètement à gauche, à droite, au-dessus ou en-dessous de l'autre -> Faux
        if (x_max < other.x_min || x_min > other.x_max) return false;
        if (y_max < other.y_min || y_min > other.y_max) return false;
        
        return true;
    }
    
    // Debug : Pour afficher les coordonnées facilement
    void print() const {
        std::cout << "AABB: [" << x_min << ", " << x_max << "] x [" 
                  << y_min << ", " << y_max << "]" << std::endl;
    }
};


#endif