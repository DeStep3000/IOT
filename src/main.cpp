#include "polygon.h"
#include "sfml.h"

int main() {
    const std::string path = "C:\\DeStep\\HSE\\C++\\IOT\\src\\test2.txt";//Absolute file path
    std::string input = read_file(path);
    input = edit_file(input);
    PolygonField pn_field;
    pn_field.input_polygons(input);
    pn_field.print_field();

    std::vector<Polygon> start_vertices = pn_field.get_field();

    Polygon res = pn_field.intersect_polygon_field_final();
    res.print_vertices();

    int width = 800;
    int height = 600;
    Picture picture(width, height);
    std::vector<Point> final_vertices = res.get_vertices();
    picture.draw_window(start_vertices, final_vertices);
    return 0;
}