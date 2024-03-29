#ifndef IOT_SFML_H
#define IOT_SFML_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "polygon.h"


class Picture{
private:
    std::vector<Point> vertices;
public:
    void draw_window(std::vector <Point> vertices, int x, int y);
    sf::ConvexShape draw_polygon(int width, int height, std::vector<Point> arbitraryPoints);
    float scale(int width, int height, std::vector<sf::Vector2f> arbitraryPoints);
    sf::Vector2f convertToPoint(const Point &p);
};
#endif
