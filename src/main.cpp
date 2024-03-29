#include "polygon.h"
#include "sfml.h"

int main() {
    const std::string path = "C:\\DeStep\\HSE\\C++\\IOT\\src\\test2.txt";//Absolute file path
    std::string input = read_file(path);
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);
    pn_field.print_field();
    Polygon res = pn_field.intersect_polygon_field_final();
    res.print_vertices();
    Picture picture;
    int width = 800, height = 600;
    std::vector<Point> vertices = res.get_vertices();
    picture.draw_window(vertices, width, height);
    return 0;
}