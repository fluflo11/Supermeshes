#include "structs.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>
#include <stdexcept>

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


