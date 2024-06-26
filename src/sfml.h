#ifndef IOT_SFML_H
#define IOT_SFML_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "polygon.h"

const double ScaleMove = 50;

class Picture{
private:
    std::vector<Point> vertices;
    int width, height;
    double all_scale;
public:
    Picture(int nwidth, int nheight){
        width = nwidth;
        height = nheight;
    }

    void draw_window(std::vector<Polygon> start_vertices, std::vector <Point> final_vertices);

    sf::ConvexShape draw_polygon(std::vector<Point> arbitraryPoints, sf::Color color_pol, sf::Color tick);
    float scale(std::vector<Polygon> start_vertices, std::vector<Point> final_vertices);
    sf::Vector2f convertToPoint(const Point &p);

    sf::VertexArray draw_gridlines(int step);

};
#endif
